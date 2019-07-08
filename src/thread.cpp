#include "Thread.hpp"
using namespace thread;

Thread::Thread(void (*t_callback)(), unsigned long t_interval)
    : m_callback(t_callback),
      m_lastRun(0UL),
      m_interval(t_interval) {}

void Thread::run()
{

    unsigned long currentTime = millis();

    if (currentTime - m_lastRun >= m_interval)
    {
        m_callback();
        m_lastRun = currentTime;
    }
}
