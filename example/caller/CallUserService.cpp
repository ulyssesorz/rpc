#include <iostream>
#include "User.pb.h"
#include "rpc_application.h"
#include "rpc_control.h"
#include "rpc_channel.h"
#include "rpc_logger.h"

int main(int argc, char **argv)
{
    cout << "eddie_test: caller" << endl;
    RPC_LOG_DEBUG("HI");
    //初始化ip地址和端口号
    RpcApplication::init(argc, argv);

    //演示调用远程发布的rpc方法login
    ulysses::UserServiceRpc_Stub stub(new RpcChannel());

    //请求参数和响应
    ulysses::LoginRequest request;
    request.set_name("zhang san");
    request.set_password("123456");

    ulysses::LoginResponse response;

    //发起rpc调用，等待响应返回
    stub.Login(nullptr, &request, &response, nullptr);

    //rpc调用完成，读调用的结果
    if (response.errmsg().error() == 0)
    {
        //没错误
        cout << "rpc login response: " << response.success() << endl;
    }
    else
    {
        //有错误
        cout << "rpc login response errer: " << response.errmsg().error_msg() << endl;
    }

    ulysses::RegisterRequest reg_request;
    reg_request.set_id(2000);
    reg_request.set_name("rpc");
    reg_request.set_password("123456");
    ulysses::RegisterResponse reg_response;

    RpcControl control;

    stub.Register(&control, &reg_request, &reg_response, nullptr);

    //rpc调用完成，读调用的结果
    if (reg_response.error().error() == 0)
    {
        //没错误
        cout << "rpc login response: " << reg_response.success() << endl;
    }
    else
    {
        //有错误
        cout << "rpc login response errer: " << reg_response.error().error_msg() << endl;
    }


    return 0;
}