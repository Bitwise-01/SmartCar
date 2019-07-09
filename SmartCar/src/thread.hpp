#pragma once
#include <Arduino.h>

namespace thread
{
class Thread
{
public:
    Thread(void (*t_callback)(), unsigned long t_interval);
    void run();

private:
    void (*m_callback)();
    unsigned long m_lastRun;
    unsigned long m_interval;
};
} // namespace thread
