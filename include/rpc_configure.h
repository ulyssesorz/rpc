#pragma once

#include<string>
#include<unordered_map>
using namespace std;

class RpcConfigure
{
public:
    void loadConfigure(const char* config_file);
    string findLoad(const string& key);
    void trim(string& str_buffer);

private:
    unordered_map<string, string> m_configure_map;
};