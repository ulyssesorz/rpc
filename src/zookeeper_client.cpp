#include<iostream>
#include"zookeeper_client.h"
#include"rpc_application.h"
#include"rpc_logger.h"

using namespace std;

// zk会话状态发生变化（建立连接）的回调
void globalWatcher(zhandle_t* handler, int type, int state, const char* path, void* watcher_context)
{
    if(type == ZOO_SESSION_EVENT)
    {
        if(state == ZOO_CONNECTED_STATE)
        {
            sem_t* sem = (sem_t*)zoo_get_context(handler);
            sem_post(sem);
        }
    }
}

ZookeeperClient::ZookeeperClient() : m_zhandle(nullptr) {}

ZookeeperClient::~ZookeeperClient()
{
    if(m_zhandle != nullptr)
    {
        zookeeper_close(m_zhandle);
    }
}

void ZookeeperClient::start()
{
    string host = RpcApplication::instance().getConfigure().findLoad("zookeeper_ip");
    string port = RpcApplication::instance().getConfigure().findLoad("zookeeper_port");
    string str = host + ":" + port;
    // 初始化与zk服务器的连接
    m_zhandle = zookeeper_init(str.c_str(), globalWatcher, 30000, nullptr, nullptr, 0);
    if(m_zhandle == nullptr)
    {
        RPC_LOG_FATAL("zookeeper init error");
    }
    sem_t sem;
    sem_init(&sem, 0, 0);
    zoo_set_context(m_zhandle, &sem);
    sem_wait(&sem);
    RPC_LOG_DEBUG("zookeeper init success");
}

void ZookeeperClient::create(const char* path, const char* data, int datalen, int state)
{
    char buf[128] = {0};
    int buf_len = sizeof(buf);
    int flag;
    flag = zoo_exists(m_zhandle, path, 0, nullptr);
    if(flag == ZNONODE)
    {
        flag = zoo_create(m_zhandle, path, data, datalen, &ZOO_OPEN_ACL_UNSAFE, state, buf, buf_len);
        if(flag == ZOK)
        {
            RPC_LOG_DEBUG("znode create success...path: %s", path);
        }
        else
        {
            RPC_LOG_FATAL("flag: %d, znode create error...path: %s", flag, path);
        }
    }
}

string ZookeeperClient::getData(const char* path)
{
    char buf[64] = {0};
    int buf_len = sizeof(buf);
    int flag = zoo_get(m_zhandle, path, 0, buf, &buf_len, nullptr);
    if(flag != ZOK)
    {
        RPC_LOG_ERROR("can't get znode...path: %s", path);
        return "";
    }
    else
    {
        return buf;
    }
}