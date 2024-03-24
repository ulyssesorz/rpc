#include"rpc_logger.h"
#include<unistd.h>
#include<iostream>

#define FILENAME_SIZE 128
#define TIMEBUFFER_SIZE 128

void RpcLogger::log(const string& msg)
{
    string begin_msg;
    switch(m_log_level)
    {
        case RPC_DEBUG:
            begin_msg = "[DEBUG]: ";
            break;
        case RPC_ERROR:
            begin_msg = "[ERROR]: ";
            break;
        case RPC_FATAL:
            begin_msg = "[FATAL]: ";
            break;
        default:
            break;
    }
    begin_msg += msg;
    m_log_queue.push(begin_msg);
}

void RpcLogger::log_debug(const string& msg)
{
    set_level(RPC_DEBUG);
    log(msg);
}

void RpcLogger::log_error(const string& msg)
{
    set_level(RPC_ERROR);
    log(msg);
}

void RpcLogger::log_fatal(const string& msg)
{
    set_level(RPC_FATAL);
    log(msg);
    exit(0);
}

RpcLogger::RpcLogger()
{
    thread sync_write([&]()
    { 
        while(1)
        {
            time_t now = time(0);
            tm* now_time = localtime(&now);
            char file_name[FILENAME_SIZE] = {0};
            sprintf(file_name, "%d-%d-%d.log", now_time->tm_year + 1900, now_time->tm_mon + 1, now_time->tm_mday);
            FILE* fp = fopen(file_name, "a+");
            if(fp == nullptr)
            {
                exit(0);
            }
            string msg;
            char time_buf[TIMEBUFFER_SIZE] = {0};
            sprintf(time_buf, "%2d:%2d:%2d=>", now_time->tm_hour, now_time->tm_min, now_time->tm_sec);
            msg = m_log_queue.pop();
            msg.insert(0, time_buf);
            msg += '\n';
            fputs(msg.c_str(), fp);
            fclose(fp);
        }
    });
    sync_write.detach();
}