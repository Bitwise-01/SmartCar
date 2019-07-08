#pragma once
#include "engine.hpp"

namespace engineController
{
class EngineControllerConsts
{
public:
    static const unsigned int m_MIN_SPEED = 0U;
    static const unsigned int m_MAX_SPEED = 255U;
    static const unsigned int m_ACCEL_RATE = 20U;
    static const unsigned int m_HALF_SPEED = 127U;
};

class EngineController
{
public:
    EngineController(engine::Engine &t_e1, engine::Engine &t_e2, engine::Engine &t_e3, engine::Engine &t_e4);
    void accelerate(bool t_goForward = true);
    void decelerate(bool t_goForward = true);
    unsigned int getSpeed() const;
    bool isMovingForward();
    void brake();

    // Turns: Forward
    void softLeftTurnForward();
    void softRightTurnForward();

    // Turns: Backward
    void softLeftTurnBackward();
    void softRightTurnBackward();

private:
    engine::Engine
        m_engine1,
        m_engine2,
        m_engine3,
        m_engine4;

    bool
        m_minSpeedReached,
        m_maxSpeedReached;

    unsigned int m_currentSpeed;
    const unsigned int m_ACCEL_RATE;

    void m_drive(bool t_goForward);
    void m_accelerate(bool t_goForward);
    void m_decelerate(bool t_goForward);
};
} // namespace engineController
