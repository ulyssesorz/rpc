#pragma once

#include<queue>
#include<mutex>
#include<condition_variable>
#include<thread>

using namespace std;

template<class T>
class LoggerQueue
{
public:
    void push(const T& data)
    {
        lock_guard<mutex> locker(m_mutex);
        m_queue.push(data);
        m_condition.notify_one();
    }
    T pop()
    {
        unique_lock<mutex> locker(m_mutex);
        while(m_queue.empty())
        {
            m_condition.wait(locker);
        }
        T ret = m_queue.front();
        m_queue.pop();
        return ret;
    }
private:
    mutex m_mutex;
    condition_variable m_condition;
    queue<T> m_queue;
};