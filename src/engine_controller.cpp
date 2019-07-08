#include "engine_controller.hpp"
using namespace engineController;

EngineController::EngineController(
    engine::Engine &t_e1, engine::Engine &t_e2,
    engine::Engine &t_e3, engine::Engine &t_e4)
    : m_engine1(t_e1),
      m_engine2(t_e2),
      m_engine3(t_e3),
      m_engine4(t_e4),
      m_minSpeedReached(true),
      m_maxSpeedReached(false),
      m_currentSpeed(EngineControllerConsts::m_MIN_SPEED),
      m_ACCEL_RATE(EngineControllerConsts::m_ACCEL_RATE) {}

void EngineController::accelerate(bool t_goForward)
{
    if (m_currentSpeed >= engineController::EngineControllerConsts::m_MAX_SPEED)
    {
        m_maxSpeedReached = true;
        m_minSpeedReached = false;
    }

    if (!m_maxSpeedReached)
    {
        m_accelerate(t_goForward);
    }
}

void EngineController::m_accelerate(bool t_goForward)
{
    unsigned int currentSpeed = m_currentSpeed;

    if (currentSpeed + m_ACCEL_RATE <= EngineControllerConsts::m_MAX_SPEED)
    {
        m_currentSpeed += m_ACCEL_RATE;
    }
    else if (currentSpeed + 1 <= EngineControllerConsts::m_MAX_SPEED)
    {
        m_currentSpeed += 1;
    }

    if (currentSpeed != m_currentSpeed)
    {
        m_drive(t_goForward);
    }
}

void EngineController::decelerate(bool t_goForward)
{
    if (m_currentSpeed == engineController::EngineControllerConsts::m_MIN_SPEED)
    {
        m_minSpeedReached = true;
        m_maxSpeedReached = false;
    }

    if (!m_minSpeedReached)
    {
        m_decelerate(t_goForward);
    }
}

void EngineController::m_decelerate(bool t_goForward)
{
    int currentSpeed = m_currentSpeed;

    if (currentSpeed - static_cast<int>(m_ACCEL_RATE) >= static_cast<int>(EngineControllerConsts::m_MIN_SPEED))
    {
        m_currentSpeed -= m_ACCEL_RATE;
    }
    else if (currentSpeed - 1 >= static_cast<int>(EngineControllerConsts::m_MIN_SPEED))
    {
        m_currentSpeed -= 1;
    }

    if (static_cast<unsigned int>(currentSpeed) != m_currentSpeed)
    {
        m_drive(t_goForward);
    }
}

unsigned int EngineController::getSpeed() const
{
    return m_currentSpeed;
}

bool EngineController::isMovingForward()
{
    return m_engine1.isMovingForward() && m_engine2.isMovingForward() &&
           m_engine3.isMovingForward() && m_engine4.isMovingForward();
}

void EngineController::brake()
{
    m_engine1.stop();
    m_engine2.stop();

    m_engine3.stop();
    m_engine4.stop();
}

void EngineController::m_drive(bool t_goForward)
{
    m_engine1.drive(m_currentSpeed, t_goForward);
    m_engine2.drive(m_currentSpeed, t_goForward);

    m_engine3.drive(m_currentSpeed, t_goForward);
    m_engine4.drive(m_currentSpeed, t_goForward);
}

void EngineController::softLeftTurnForward()
{
    m_engine1.drive(EngineControllerConsts::m_HALF_SPEED, false);
    m_engine3.drive(EngineControllerConsts::m_HALF_SPEED, false);

    m_engine2.drive(EngineControllerConsts::m_MAX_SPEED);
    m_engine4.drive(EngineControllerConsts::m_MAX_SPEED);
}

void EngineController::softRightTurnForward()
{
    m_engine1.drive(EngineControllerConsts::m_HALF_SPEED);
    m_engine3.drive(EngineControllerConsts::m_HALF_SPEED);

    m_engine2.drive(EngineControllerConsts::m_MAX_SPEED, false);
    m_engine4.drive(EngineControllerConsts::m_MAX_SPEED, false);
}

void EngineController::softLeftTurnBackward()
{
    m_engine1.drive(EngineControllerConsts::m_HALF_SPEED, false);
    m_engine3.drive(EngineControllerConsts::m_HALF_SPEED, false);

    m_engine2.drive(EngineControllerConsts::m_MAX_SPEED, false);
    m_engine4.drive(EngineControllerConsts::m_MAX_SPEED, false);
}

void EngineController::softRightTurnBackward()
{
    m_engine2.drive(EngineControllerConsts::m_HALF_SPEED, false);
    m_engine4.drive(EngineControllerConsts::m_HALF_SPEED, false);

    m_engine1.drive(EngineControllerConsts::m_MAX_SPEED, false);
    m_engine3.drive(EngineControllerConsts::m_MAX_SPEED, false);
}