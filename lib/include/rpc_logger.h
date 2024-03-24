#pragma once

#include<string>
#include<time.h>
#include"loggerqueue.h"

using namespace std;

#define STR_SIZE 1024

#define RPC_LOG_DEBUG(logmsgformat, ...)                        \
    do                                                         \
    {                                                           \
        RpcLogger& logger = RpcLogger::instance();              \
        char msg[STR_SIZE] = {0};                               \
        snprintf(msg, STR_SIZE, logmsgformat, ##__VA_ARGS__);   \
        logger.log_debug(msg);                                   \
    }                                                           \
    while(false);                                               \

#define RPC_LOG_ERROR(logmsgformat, ...)                        \
    do                                                         \
    {                                                           \
        RpcLogger& logger = RpcLogger::instance();              \
        char msg[STR_SIZE] = {0};                               \
        snprintf(msg, STR_SIZE, logmsgformat, ##__VA_ARGS__);   \
        logger.log_error(msg);                                   \
    }                                                           \
    while(false);                                               \

#define RPC_LOG_FATAL(logmsgformat, ...)                        \
    do                                                         \
    {                                                           \
        RpcLogger& logger = RpcLogger::instance();              \
        char msg[STR_SIZE] = {0};                               \
        snprintf(msg, STR_SIZE, logmsgformat, ##__VA_ARGS__);   \
        logger.log_fatal(msg);                                   \
    }                                                           \
    while(false);                                               \

enum LogLevel
{
    RPC_DEBUG,
    RPC_ERROR,
    RPC_FATAL,
};

class RpcLogger
{
public:
    static RpcLogger& instance()
    {
        static RpcLogger instance;
        return instance;
    }

    void log_debug(const string& msg);
    void log_error(const string& msg);
    void log_fatal(const string& msg);
private:
    void set_level(LogLevel level) {m_log_level = level;}
    void log(const string& msg);

    RpcLogger();
    RpcLogger(const RpcLogger&) = delete;
    RpcLogger& operator=(const RpcLogger&) = delete;

private:
    LogLevel m_log_level;
    LoggerQueue<string> m_log_queue;
};

