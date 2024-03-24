#include"rpc_control.h"

RpcControl::RpcControl() : m_failed(false), m_error_msg("") {}

void RpcControl::Reset()
{
    m_failed = false;
    m_error_msg = "";
}

bool RpcControl::Failed() const
{
    return m_failed;
}

string RpcControl::ErrorText() const
{
    return m_error_msg;
}

void RpcControl::SetFailed(const string& msg)
{
    m_failed = true;
    m_error_msg = msg;
}

void RpcControl::StartCancel() {}
bool RpcControl::IsCanceled() const {return false;}
void RpcControl::NotifyOnCancel(google::protobuf::Closure* callback) {}