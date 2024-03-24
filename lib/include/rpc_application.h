#pragma once
#include "rpc_configure.h"

class RpcApplication
{
public:
    static void init(int argc, char** argv);
    static RpcApplication& instance();
    static RpcConfigure& getConfigure();
private:
    RpcApplication() = default;
    ~RpcApplication() = default;
    RpcApplication(const RpcApplication&) = delete;
    RpcApplication& operator=(const RpcApplication&) = delete;
private:
    static RpcConfigure m_configure;
};