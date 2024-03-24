#include <iostream>
#include <string>
#include "User.pb.h"
#include "rpc_application.h"
#include "rpc_provider.h"
#include "rpc_logger.h"

using namespace std;

class UserService : public ulysses::UserServiceRpc
{
public:
    bool Login(string name, string password)
    {
        cout << "doing local service:login: ";
        cout << "name: " << name << " password: " << password << endl;
        return true;
    }

    bool Register(uint32_t id, string name, string password)
    {
        cout << "doing local service:register: ";
        cout << "id:" << id << "name: " << name << " password: " << password << endl;
        return true;
    }

    //重写基类UserServiceRpc的虚函数，供框架调用
    void Login(::google::protobuf::RpcController *controller,
               const ::ulysses::LoginRequest *request,
               ::ulysses::LoginResponse *response,
               ::google::protobuf::Closure *done)
    {
        //框架给业务上报了请求参数 request，业务获取相应数据做本地业务
        string name = request->name();
        string password = request->password();

        //本地业务
        bool login_result = Login(name, password);

        //把响应给调用方返回
        ulysses::ErrorMsg *errmsg = response->mutable_errmsg();
        errmsg->set_error(0);
        errmsg->set_error_msg("");
        response->set_success(login_result);

        //执行回调操作
        done->Run();
    }

    void Register(::google::protobuf::RpcController *controller,
                  const ::ulysses::RegisterRequest *request,
                  ::ulysses::RegisterResponse *response,
                  ::google::protobuf::Closure *done)
    {
        //框架给业务上报了请求参数 request，业务获取相应数据做本地业务
        uint32_t id = request->id();
        string name = request->name();
        string password = request->password();

        //本地业务
        bool login_result = Register(id, name, password);

        //把响应给调用方返回
        ulysses::ErrorMsg *errmsg = response->mutable_error();
        errmsg->set_error(0);
        errmsg->set_error_msg("");
        response->set_success(login_result);

        //执行回调操作
        done->Run();
    }
};

int main(int argc, char **argv)
{
    cout << "eddie_test: callee" << endl;
    RPC_LOG_DEBUG("HELLO");
    RPC_LOG_ERROR("%s,%s,%d", __FILE__, __FUNCTION__, __LINE__);
    //调用框架的初始化操作
    RpcApplication::init(argc, argv);

    //框架服务提供provider
    RpcProvider provider;
    provider.notifyService(new UserService());
    provider.run();
    return 0;
}