#include "engine.hpp"
using namespace engine;

Engine::Engine(const unsigned char t_motor, const unsigned char t_forward, const unsigned char t_backward)
    : m_motor(t_motor),
      m_forward(t_forward),
      m_backward(t_backward),
      m_isActive(false),
      m_isForward(true),
      m_loops(0U),
      m_speed(0U) {}

void Engine::drive(unsigned int t_speed, bool t_isForward)
{
    if (!m_isActive || m_isForward != t_isForward)
    {
        // Turn off
        digitalWrite(m_forward, LOW);
        digitalWrite(m_backward, LOW);
        m_loops = 0;

        // Set direction
        if (t_isForward)
        {
            digitalWrite(m_forward, HIGH);
            digitalWrite(m_backward, LOW);
        }
        else
        {
            digitalWrite(m_forward, LOW);
            digitalWrite(m_backward, HIGH);
        }

        m_isActive = true;
        m_isForward = t_isForward;
    }

    if (m_loops > 1)
    {
        if (m_speed != t_speed)
        {
            m_speed = t_speed;
            analogWrite(m_motor, t_speed);
        }
    }
    else
    {
        m_loops++;
    }
}

void Engine::stop()
{
    if (m_isActive)
    {
        digitalWrite(m_forward, LOW);
        digitalWrite(m_backward, LOW);

        m_speed = 0;
        m_isActive = false;
    }
}

bool Engine::isMovingForward() const
{
    return m_isForward && m_speed;
}