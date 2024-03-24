#pragma once
#include <google/protobuf/service.h>
#include <google/protobuf/descriptor.h>
#include <netlib/eventloop.h>
#include <netlib/inetaddress.h>
#include <netlib/tcpconnection.h>
#include <netlib/buffer.h>
#include <netlib/tcpserver.h>

#include <unordered_map>
#include <string>
#include <iostream>
#include <functional>

using namespace std;

class RpcProvider
{
public:
    void notifyService(google::protobuf::Service* service);
    void run();

private:
    void onConnection(const TcpConnectionPtr& conn);
    void onMessage(const TcpConnectionPtr& conn, Buffer* buffer, TimeStamp stamp);
    void sendRpcResponse(const TcpConnectionPtr& conn, google::protobuf::Message* reponse);

private:
    struct ServiceInfo
    {
        google::protobuf::Service* m_service;
        // method_name : method_desc
        unordered_map<string, const google::protobuf::MethodDescriptor*> m_method_map;
    };

private:
    EventLoop m_eventloop;
    // service_name : service_info
    unordered_map<string, ServiceInfo> m_service_map;
};