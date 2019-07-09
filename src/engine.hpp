#pragma once
#include <Arduino.h>

namespace engine
{
class Engine
{
public:
    Engine(const unsigned char t_motor, const unsigned char t_forward, const unsigned char t_backward);
    void drive(unsigned int t_speed, bool t_isForward = true);
    bool isMovingForward() const;
    void stop();

private:
    const unsigned char m_motor;
    const unsigned char m_forward;
    const unsigned char m_backward;

    // Movemovents
    bool m_isActive;
    bool m_isForward;
    unsigned int m_loops; // When motor changes directions it should loop once before applying power to it
    unsigned int m_speed;
};
} // namespace engine