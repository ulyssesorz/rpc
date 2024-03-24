#include"rpc_channel.h"
#include"rpc_application.h"
#include"rpc_control.h"
#include"rpcheader.pb.h"
#include"rpc_logger.h"
#include"zookeeper_client.h"
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<unistd.h>
#include<error.h>
using namespace std;
#define BUFF_SIZE 1024

void RpcChannel::CallMethod(const google::protobuf::MethodDescriptor* method,
                google::protobuf::RpcController* controller,
                const google::protobuf::Message* request,
                google::protobuf::Message* reponse,
                google::protobuf::Closure* done)
{
    const google::protobuf::ServiceDescriptor* service_des = method->service();
    string service_name = service_des->name();
    string method_name = method->name();
    int args_size = 0;
    string args_str;
    if(request->SerializeToString(&args_str))
    {
        args_size = args_str.size();
    }
    else
    {
        controller->SetFailed("serialize request error");
        return;
    }

    ulysses::RpcHeader rpc_header;
    rpc_header.set_service_name(service_name);
    rpc_header.set_method_name(method_name);
    rpc_header.set_args_size(args_size);

    uint32_t header_size = 0;
    string rpc_header_str;
    if(rpc_header.SerializeToString(&rpc_header_str))
    {
        header_size = rpc_header_str.size();
    }
    else
    {
        controller->SetFailed("serialize rpc_header error");
    }

    string send_rpc_str;
    send_rpc_str.insert(0, string((char*)&header_size, 4));
    send_rpc_str += rpc_header_str;
    send_rpc_str += args_str;

    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client_fd == -1)
    {
        close(client_fd);
        RPC_LOG_FATAL("create socket error errno: %d", errno);
    }
    ZookeeperClient zk_client;
    zk_client.start();
    string method_path = "/" + service_name + "/" + method_name;
    string host_data = zk_client.getData(method_path.c_str());
    if(host_data == "")
    {
        controller->SetFailed(method_path + " is not exist");
    }
    int host_index = host_data.find(":");
    if(host_index == -1)
    {
        controller->SetFailed(method_path + " address is invalid");
        return;
    }
    string ip = host_data.substr(0, host_index);
    uint16_t port = atoi(host_data.substr(host_index + 1, host_data.size() - host_index).c_str());
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

    if(connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        close(client_fd);
        RPC_LOG_FATAL("connect error, errno: %d", errno);
    }
    if(send(client_fd, send_rpc_str.c_str(), send_rpc_str.size(), 0) == -1)
    {
        controller->SetFailed("send error, errno: " + errno);
        close(client_fd);
        return;
    }

    char buff[BUFF_SIZE] = {0};
    ssize_t buff_size = recv(client_fd, buff, BUFF_SIZE, 0);
    if(buff_size == -1)
    {
        controller->SetFailed("recv error, errno: " + errno);
        close(client_fd);
        return;
    }
    if(!reponse->ParseFromArray(buff, buff_size))
    {
        string recv = buff;
        controller->SetFailed("parse error, response_str: " + recv);
        close(client_fd);
        return;
    }
    close(client_fd);
}