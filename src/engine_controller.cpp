#include "engine_controller.hpp"
using namespace engineController;

EngineController::EngineController(
    engine::Engine &t_e1, engine::Engine &t_e2,
    engine::Engine &t_e3, engine::Engine &t_e4)
    : m_engine1(t_e1),
      m_engine2(t_e2),
      m_engine3(t_e3),
      m_engine4(t_e4),
      m_currentSpeed(EngineControllerConsts::MAX_SPEED),

      m_lastForward(true),
      m_counter(0),

      m_lastForward1(true),
      m_lastForward2(true),
      m_turnsCounter(0)

{
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

void EngineController::m_drive(engine::Engine t_e1, engine::Engine t_e2, unsigned int t_speed1, bool t_goForward1,
                               engine::Engine t_e3, engine::Engine t_e4, unsigned int t_speed2, bool t_goForward2)
{
    t_e1.drive(t_speed1, t_goForward1);
    t_e2.drive(t_speed1, t_goForward1);

    if (m_lastForward1 != t_goForward1 || m_lastForward2 != t_goForward2)
    {
        m_lastForward1 = t_goForward1;
        m_lastForward2 = t_goForward2;
        m_turnsCounter = 0;
    }

    if (m_turnsCounter >= 1)
    {
        t_e3.drive(t_speed2, t_goForward2);
        t_e4.drive(t_speed2, t_goForward2);
    }
    else
    {
        m_turnsCounter += 1;
    }
}

void EngineController::driveForward(unsigned int speed)
{
    if (speed == 0)
    {
        m_currentSpeed = EngineControllerConsts::MAX_SPEED;
    }
    else
    {
        m_currentSpeed = speed;
    }

    m_drive(m_engine1, m_engine2, m_currentSpeed, true,
            m_engine3, m_engine4, m_currentSpeed, true);
}

void EngineController::driveBackward(unsigned int speed)
{
    if (speed == 0)
    {
        m_currentSpeed = EngineControllerConsts::MAX_SPEED;
    }
    else
    {
        m_currentSpeed = speed;
    }

    m_drive(m_engine1, m_engine2, m_currentSpeed, false,
            m_engine3, m_engine4, m_currentSpeed, false);
}

void EngineController::softLeftTurnForward()
{
    m_drive(m_engine1, m_engine3, EngineControllerConsts::HALF_SPEED, true,
            m_engine2, m_engine4, EngineControllerConsts::MAX_SPEED, false);
}

void EngineController::softRightTurnForward()
{
    m_drive(m_engine1, m_engine3, EngineControllerConsts::MAX_SPEED, true,
            m_engine2, m_engine4, EngineControllerConsts::HALF_SPEED, false);
}

void EngineController::softLeftTurnBackward()
{
    m_drive(m_engine2, m_engine4, EngineControllerConsts::MAX_SPEED, false,
            m_engine1, m_engine3, EngineControllerConsts::HALF_SPEED, true);
}

void EngineController::softRightTurnBackward()
{
    m_drive(m_engine1, m_engine3, EngineControllerConsts::MAX_SPEED, false,
            m_engine2, m_engine4, EngineControllerConsts::HALF_SPEED, true);
}

void EngineController::leftTurnForward()
{
    m_drive(m_engine2, m_engine4, EngineControllerConsts::MAX_SPEED, true,
            m_engine1, m_engine3, EngineControllerConsts::MAX_SPEED, false);
}

void EngineController::rightTurnForward()
{
    m_drive(m_engine1, m_engine3, EngineControllerConsts::MAX_SPEED, true,
            m_engine2, m_engine4, EngineControllerConsts::MAX_SPEED, false);
}

void EngineController::leftTurnBackward()
{
    m_drive(m_engine2, m_engine4, EngineControllerConsts::MAX_SPEED, false,
            m_engine1, m_engine3, EngineControllerConsts::MAX_SPEED, true);
}

void EngineController::rightTurnBackward()
{
    m_drive(m_engine1, m_engine3, EngineControllerConsts::MAX_SPEED, false,
            m_engine2, m_engine4, EngineControllerConsts::MAX_SPEED, true);
}