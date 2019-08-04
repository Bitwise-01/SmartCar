#include "stuck.hpp"
using namespace stuck;

Stuck::Stuck(engineController::EngineController *t_engineDriver)
    : m_engineDriver(t_engineDriver),
      m_lastDistance(-1),
      m_right(0),
      m_left(0),
      m_full(0),

      m_rightBack(0),
      m_leftBack(0),
      m_ranEvade(false)
{
}

bool Stuck::isStuck(double t_currentDistance)
{
    bool _isStuck = false;

    if (m_lastDistance != -1)
    {
        if (abs(t_currentDistance - m_lastDistance) <= Constants::MIN_STUCK_DISTANCE)
        {
            _isStuck = true;
            m_right = 1;
            m_left = 1;
        }
    }

    m_lastDistance = t_currentDistance;
    return _isStuck;
}

bool Stuck::isProcessing()
{
    if (m_right != 0)
    {
        return true;
    }
    return false;
}

void Stuck::leftPower()
{
    m_engineDriver->leftTurnBackward();
    m_left += 1;
}

void Stuck::rightPower()
{
    m_engineDriver->rightTurnBackward();
    m_right += 1;
}

void Stuck::evade()
{
    if (m_right < engineController::EngineControllerConsts::MAX_TURNS)
    {
        rightPower();
    }

    if (m_right >= engineController::EngineControllerConsts::MAX_TURNS && m_rightBack < Constants::MAX_LOOPS)
    {
        m_engineDriver->driveBackward();
        m_rightBack += 1;
    }

    if (m_right >= engineController::EngineControllerConsts::MAX_TURNS && m_rightBack >= Constants::MAX_LOOPS && m_left < engineController::EngineControllerConsts::MAX_TURNS)
    {
        leftPower();
    }

    if (m_left >= engineController::EngineControllerConsts::MAX_TURNS && m_leftBack < Constants::MAX_LOOPS)
    {
        m_engineDriver->driveBackward();
        m_leftBack += 1;
    }

    if (
        m_right >= engineController::EngineControllerConsts::MAX_TURNS && m_rightBack >= Constants::MAX_LOOPS &&
        m_left >= engineController::EngineControllerConsts::MAX_TURNS && m_leftBack >= Constants::MAX_LOOPS &&
        m_full < Constants::MAX_LOOPS)
    {
        m_engineDriver->driveBackward();
        m_full += 1;
    }

    if (m_full >= Constants::MAX_LOOPS)
    {
        reset();
        m_ranEvade = true;
    }
}

void Stuck::reset()
{
    m_right = 0;
    m_left = 0;
    m_full = 0;

    m_rightBack = 0;
    m_leftBack = 0;
    m_lastDistance = -1;
}

bool Stuck::ranEvade()
{

    bool oldState = m_ranEvade;

    if (m_ranEvade)
    {
        m_ranEvade = false;
    }

    return oldState;
}