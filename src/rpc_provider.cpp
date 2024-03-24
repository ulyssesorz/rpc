#include"rpcheader.pb.h"
#include"rpc_application.h"
#include"rpc_logger.h"
#include"rpc_provider.h"
#include"zookeeper_client.h"

using namespace std;
using namespace placeholders;

void RpcProvider::notifyService(google::protobuf::Service* service)
{
    // 记录服务和各服务下提供的方法
    ServiceInfo service_info;
    const google::protobuf::ServiceDescriptor *service_desc = service->GetDescriptor();

    string service_name = service_desc->name();
    int method_nums = service_desc->method_count();

    for (int i = 0; i < method_nums; ++i)
    {
        const google::protobuf::MethodDescriptor* method_desc = service_desc->method(i);
        string method_name = method_desc->name();
        service_info.m_method_map.insert({method_name, method_desc});
    }
    service_info.m_service = service;
    m_service_map.insert({service_name, service_info});
}

void RpcProvider::run()
{
    // 获取ip和port
    string ip = RpcApplication::instance().getConfigure().findLoad("rpcserver_ip");
    uint16_t port = atoi(RpcApplication::instance().getConfigure().findLoad("rpcserver_port").c_str());
    cout << ip << ":" << port << endl;
    InetAddress address(port, ip);

    TcpServer server(&m_eventloop, address, "RpcProvider");
    // 绑定建立连接和IO的回调方法
    server.setConnectionCallback(bind(&RpcProvider::onConnection, this, _1));
    server.setMessageCallback(bind(&RpcProvider::onMessage, this, _1, _2, _3));
    server.setThreadNum(4);

    // 把当前服务注册到zk节点上
    ZookeeperClient zk_client;
    zk_client.start();

    // 在配置中心中创建节点
    for (auto &sp : m_service_map)
    {
        string service_path = "/" + sp.first;
        zk_client.create(service_path.c_str(), nullptr, 0);
        for (auto &mp : sp.second.m_method_map)
        {
            string method_path = service_path + "/" + mp.first;
            char method_path_data[128] = {0};
            sprintf(method_path_data, "%s:%d", ip.c_str(), port);
            // ZOO_EPHEMERAL 表示znode时候临时性节点
            zk_client.create(method_path.c_str(), method_path_data, strlen(method_path_data), ZOO_EPHEMERAL);
        }
    }

    LOG_INFO("server RpcProvider [ip: %s][port: %d]", ip.c_str(), port);
    //启动
    server.start();
    m_eventloop.loop();
}

void RpcProvider::onConnection(const TcpConnectionPtr &conn)
{
    if (!conn->connected())
    {
        conn->shutdown();
    }
}

void RpcProvider::onMessage(const TcpConnectionPtr &conn, Buffer *buffer, TimeStamp stamp)
{
    string recv_buf = buffer->retrieveAllAsString();

    // 读取4字节数据，即header的长度
    uint32_t header_size = 0;
    recv_buf.copy((char *)&header_size, 4, 0);

    RPC_LOG_DEBUG("header size: %d", header_size);

    string rpc_header_str = recv_buf.substr(4, header_size);

    //反序列化
    ulysses::RpcHeader rpc_header;
    string service_name;
    string method_name;
    uint32_t args_size = 0;
    if (rpc_header.ParseFromString(rpc_header_str))
    {
        service_name = rpc_header.service_name();
        method_name = rpc_header.method_name();
        args_size = rpc_header.args_size();
    }
    else
    {
        RPC_LOG_ERROR("rpc header str:%s parse error!", rpc_header_str.c_str());
        return;
    }

    // 读取参数信息
    string args_str = recv_buf.substr(4 + header_size, args_size);

    //打印调试信息
    RPC_LOG_DEBUG("<------------------------------------------------>");
    RPC_LOG_DEBUG("rpc header str: %s", rpc_header_str.c_str());
    RPC_LOG_DEBUG("service name: %s", service_name.c_str());
    RPC_LOG_DEBUG("method name: %s", method_name.c_str());
    RPC_LOG_DEBUG("args: %s", args_str.c_str());
    RPC_LOG_DEBUG("<------------------------------------------------>");

    // 获取service对象和method对象
    auto service_it = m_service_map.find(service_name);
    if (service_it == m_service_map.end())
    {
        RPC_LOG_ERROR("%s is not exist", service_name.c_str());
        return;
    }

    auto method_it = service_it->second.m_method_map.find(method_name);
    if (method_it == service_it->second.m_method_map.end())
    {
        RPC_LOG_ERROR("%s::%s is not exist", service_name.c_str(), method_name.c_str());
        return;
    }

    google::protobuf::Service *service = service_it->second.m_service;
    const google::protobuf::MethodDescriptor *method = method_it->second;

    // 生成req和resp
    google::protobuf::Message *request = service->GetRequestPrototype(method).New();
    if (!request->ParseFromString(args_str))
    {
        RPC_LOG_ERROR("request parse error!");
        return;
    }
    google::protobuf::Message *response = service->GetResponsePrototype(method).New();

    // 回调
    google::protobuf::Closure *done = google::protobuf::NewCallback<RpcProvider, const TcpConnectionPtr &, google::protobuf::Message *>(this, &RpcProvider::sendRpcResponse, conn, response);

    // 调用rpc请求的方法
    service->CallMethod(method, nullptr, request, response, done);
}

void RpcProvider::sendRpcResponse(const TcpConnectionPtr &conn, google::protobuf::Message *response)
{
    // rpc调用完成的回调，序列化resp返回即可
    string response_str;
    if (response->SerializeToString(&response_str))
    {
        conn->send(response_str);
    }
    else
    {
        RPC_LOG_ERROR("serialize reponse error");
    }
    conn->shutdown();
}