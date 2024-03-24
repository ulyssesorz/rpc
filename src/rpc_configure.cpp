#include"rpc_configure.h"
#include"rpc_logger.h"
#include<string>
#include<iostream>

#define BUFFER_SIZE 128

void RpcConfigure::loadConfigure(const char* config_file)
{
    FILE* fp = fopen(config_file, "r");
    if(fp == nullptr)
    {
        RPC_LOG_FATAL("%s is not exist", config_file);
    }
    while(!feof(fp))
    {
        char buf[BUFFER_SIZE] = {0};
        fgets(buf, BUFFER_SIZE, fp);

        string str_buf(buf);
        trim(str_buf);

        if(str_buf[0] == '#' || str_buf[0] == '\n' || str_buf.empty())
        {
            continue;
        }
        int index = str_buf.find('=');
        if(index == -1)
        {
            RPC_LOG_FATAL("configure file illegal");
            continue;
        }
        string key = str_buf.substr(0, index);
        trim(key);

        string value = str_buf.substr(index + 1, str_buf.size() - index);
        value[value.size() - 1] = ' ';
        trim(value);

        m_configure_map[key] = value;
    }
}

void RpcConfigure::trim(string& str_buf)
{
    int index;
    //去除前面的空格
    index = str_buf.find_first_not_of(' ');
    if(index != -1)
    {
        str_buf = str_buf.substr(index, str_buf.size() - index);
    }
    //去除后面的空格
    index = str_buf.find_last_not_of(' ');
    if(index != -1)
    {
        str_buf = str_buf.substr(0, index + 1);
    }
}

string RpcConfigure::findLoad(const string& key)
{
    auto iter = m_configure_map.find(key);
    if(iter == m_configure_map.end())
    {
        return "";
    }
    else
    {
        return iter->second;
    }
}