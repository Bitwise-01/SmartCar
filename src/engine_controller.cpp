#include "distance.hpp"
#include "engine_controller.hpp"
using namespace engineController;

EngineController::EngineController(
    engine::Engine *t_e1, engine::Engine *t_e2,
    engine::Engine *t_e3, engine::Engine *t_e4)
    : m_engine1(t_e1),
      m_engine2(t_e2),
      m_engine3(t_e3),
      m_engine4(t_e4),
      m_currentSpeed(EngineControllerConsts::MAX_SPEED),

      // Directions
      m_fullTurns(0),
      m_rights(0),
      m_lefts(0),
      m_rev(0),

      m_rightDistance(-1),
      m_leftDistance(-1),

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
    return m_engine1->isMovingForward() && m_engine2->isMovingForward() &&
           m_engine3->isMovingForward() && m_engine4->isMovingForward();
}

void EngineController::brake()
{
    m_engine1->stop();
    m_engine2->stop();

    m_engine3->stop();
    m_engine4->stop();
}

void EngineController::m_drive(engine::Engine *t_e1, engine::Engine *t_e2, unsigned int t_speed1, bool t_goForward1,
                               engine::Engine *t_e3, engine::Engine *t_e4, unsigned int t_speed2, bool t_goForward2)
{
    t_e1->drive(t_speed1, t_goForward1);
    t_e2->drive(t_speed1, t_goForward1);

    if (m_lastForward1 != t_goForward1 || m_lastForward2 != t_goForward2)
    {
        m_lastForward1 = t_goForward1;
        m_lastForward2 = t_goForward2;
        m_turnsCounter = 0;
    }

    if (m_turnsCounter >= 1)
    {
        t_e3->drive(t_speed2, t_goForward2);
        t_e4->drive(t_speed2, t_goForward2);
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

bool EngineController::isCheckingDirection()
{
    if (m_rights != 0 || m_lefts != 0 || m_fullTurns != 0 || m_rev > 0)
    {
        return true;
    }
    return false;
}

bool EngineController::checkRight()
{
    if (m_rights < EngineControllerConsts::MAX_TURNS)
    {
        rightTurnForward();
        m_rights += 1;
        return false;
    }
    return true;
}

bool EngineController::checkLeft()
{
    if (m_lefts < EngineControllerConsts::MAX_TURNS)
    {
        leftTurnForward();
        m_lefts += 1;
        return false;
    }
    return true;
}

void EngineController::chooseDirection(distance::Distance *distanceManager)
{
    unsigned int distance = -1;

    if (m_rightDistance <= -1)
    {
        if (checkRight())
        {
            m_rightDistance = distanceManager->getDistance();
            brake();
        }
    }

    if (m_rights > 0 && m_rightDistance > -1)
    {
        leftTurnForward();
        m_rights--;

        if (m_rights <= 0)
        {
            brake();
        }
    }

    if (m_rightDistance > -1 && m_rights <= 0 && m_leftDistance <= -1)
    {
        if (m_leftDistance <= -1)
        {
            if (checkLeft())
            {
                m_leftDistance = distanceManager->getDistance();
                brake();
            }
        }
    }

    if (m_leftDistance > -1 && m_leftDistance == m_rightDistance && m_lefts > 0)
    {
        rightTurnForward();
        m_lefts--;
    }

    if (m_leftDistance > -1 && m_rightDistance > m_leftDistance)
    {
        if (m_lefts > 0)
        {
            rightTurnForward();
            m_lefts--;
        }
        else if (m_fullTurns < EngineControllerConsts::MAX_TURNS)
        {
            rightTurnForward();
            m_fullTurns += 1;
        }
    }

    if (m_leftDistance > -1 && m_rightDistance < m_leftDistance)
    {
        if (m_fullTurns < EngineControllerConsts::MAX_TURNS)
        {
            m_fullTurns = EngineControllerConsts::MAX_TURNS;
        }
    }

    if (m_leftDistance > -1 && m_fullTurns >= EngineControllerConsts::MAX_TURNS)
    {
        distance = (m_rightDistance > m_leftDistance) ? m_rightDistance : m_leftDistance;

        if (distance >= distance::Constants::MIN_DIST)
        {
            m_rev = EngineControllerConsts::MAX_TURNS;
        }
    }

    if (m_fullTurns >= EngineControllerConsts::MAX_TURNS && m_rev < EngineControllerConsts::MAX_TURNS)
    {
        driveBackward();
        m_rev += 1;

        if (m_rev >= EngineControllerConsts::MAX_TURNS)
        {
            brake();
        }
    }

    if (m_fullTurns >= EngineControllerConsts::MAX_TURNS && m_rev >= EngineControllerConsts::MAX_TURNS)
    {
        m_rev = 0;
        m_lefts = 0;
        m_rights = 0;
        m_fullTurns = 0;
        m_leftDistance = -1;
        m_rightDistance = -1;
    }
}