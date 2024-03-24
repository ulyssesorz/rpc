#pragma once
#include<google/protobuf/service.h>
#include<string>

using namespace std;

class RpcControl : public google::protobuf::RpcController
{
public:
    RpcControl();
    void Reset();
    bool Failed() const;
    string ErrorText() const;
    void SetFailed(const string& msg);

    void StartCancel();
    bool IsCanceled() const;
    void NotifyOnCancel(google::protobuf::Closure* callback);

private:
    bool m_failed;
    string m_error_msg;
};