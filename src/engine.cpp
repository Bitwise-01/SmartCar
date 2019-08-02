#include "engine.hpp"
using namespace engine;

Engine::Engine(const unsigned char t_motor, const unsigned char t_forward, const unsigned char t_backward)
    : m_motor(t_motor),
      m_forward(t_forward),
      m_backward(t_backward),
      m_isActive(false),
      m_isForward(true),
      m_speed(0U)
{
}

void Engine::drive(unsigned int t_speed, bool t_isForward)
{

    if (!m_isActive || m_isForward != t_isForward)
    {
        stop();

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

    if (m_speed != t_speed)
    {
        m_speed = t_speed;
        analogWrite(m_motor, t_speed);
    }
}

void Engine::stop()
{
    m_speed = 0;
    m_isActive = false;

    digitalWrite(m_forward, LOW);
    digitalWrite(m_backward, LOW);

    analogWrite(m_motor, m_speed);
}

bool Engine::isMovingForward() const
{
    return m_isForward && m_speed > 0;
}