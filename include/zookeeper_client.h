#pragma once
#include<semaphore.h>
#include<zookeeper/zookeeper.h>

#include<string>

using namespace std;
class ZookeeperClient
{
public:
    ZookeeperClient();
    ~ZookeeperClient();

    void start();
    void create(const char* path, const char* data, int datalen, int state = 0);
    string getData(const char* path);

private:
    zhandle_t *m_zhandle;
};