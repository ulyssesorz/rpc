#include"rpc_application.h"
#include"rpc_logger.h"
#include<unistd.h>
#include<string>

using namespace std;

RpcConfigure RpcApplication::m_configure;

RpcApplication& RpcApplication::instance()
{
    static RpcApplication application;
    return application;
}

RpcConfigure& RpcApplication::getConfigure()
{
    return m_configure;
}

void RpcApplication::init(int argc, char** argv)
{
    if(argc < 2)
    {
        RPC_LOG_FATAL("fomat: command -i <configure>");
    }
    int choose = 0;
    string config_file;
    while((choose = getopt(argc, argv, "i:")) != -1)
    {
        switch(choose)
        {
            case 'i':
                config_file = optarg;
                break;
            case '?': 
                RPC_LOG_FATAL("fomat: command -i <configure>");
                break;
            case ':':
                RPC_LOG_FATAL("fomat: command -i <configure>");
                break;
            default:
                break;
        }
    }
    m_configure.loadConfigure(config_file.c_str());
}