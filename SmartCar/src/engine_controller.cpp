#include "engine_controller.hpp"
using namespace engineController;

EngineController::EngineController(
    engine::Engine &t_e1, engine::Engine &t_e2,
    engine::Engine &t_e3, engine::Engine &t_e4)
    : m_engine1(t_e1),
      m_engine2(t_e2),
      m_engine3(t_e3),
      m_engine4(t_e4),
      m_currentSpeed(EngineControllerConsts::MAX_SPEED)
{
}

unsigned int EngineController::getSpeed() const
{
    return m_currentSpeed;
}

bool EngineController::isMovingForward()
{
    return m_engine1.isMovingForward() && m_engine3.isMovingForward();
    // return m_engine1.isMovingForward() && m_engine2.isMovingForward() &&
    //        m_engine3.isMovingForward() && m_engine4.isMovingForward();
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
    // Uncomment isMovingForward function

    m_engine1.drive(m_currentSpeed, t_goForward);
    // m_engine2.drive(m_currentSpeed, t_goForward);

    m_engine3.drive(m_currentSpeed, t_goForward);
    // m_engine4.drive(m_currentSpeed, t_goForward);
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

    m_drive();
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

    m_drive(false);
}

void EngineController::softLeftTurnForward()
{
    m_engine1.drive(EngineControllerConsts::HALF_SPEED);
    m_engine3.drive(EngineControllerConsts::HALF_SPEED);

    m_engine2.drive(EngineControllerConsts::MAX_SPEED);
    m_engine4.drive(EngineControllerConsts::MAX_SPEED);
}

void EngineController::softRightTurnForward()
{
    m_engine1.drive(EngineControllerConsts::HALF_SPEED);
    m_engine3.drive(EngineControllerConsts::HALF_SPEED);

    m_engine2.drive(EngineControllerConsts::MAX_SPEED);
    m_engine4.drive(EngineControllerConsts::MAX_SPEED);
}

void EngineController::softLeftTurnBackward()
{
    m_engine1.drive(EngineControllerConsts::HALF_SPEED, false);
    m_engine3.drive(EngineControllerConsts::HALF_SPEED, false);

    m_engine2.drive(EngineControllerConsts::MAX_SPEED, false);
    m_engine4.drive(EngineControllerConsts::MAX_SPEED, false);
}

void EngineController::softRightTurnBackward()
{
    m_engine2.drive(EngineControllerConsts::HALF_SPEED, false);
    m_engine4.drive(EngineControllerConsts::HALF_SPEED, false);

    m_engine1.drive(EngineControllerConsts::MAX_SPEED, false);
    m_engine3.drive(EngineControllerConsts::MAX_SPEED, false);
}

void EngineController::leftTurnForward()
{
    m_engine1.drive(EngineControllerConsts::HALF_SPEED, false);
    m_engine3.drive(EngineControllerConsts::HALF_SPEED, false);

    m_engine2.drive(EngineControllerConsts::MAX_SPEED);
    m_engine4.drive(EngineControllerConsts::MAX_SPEED);
}

void EngineController::rightTurnForward()
{
    m_engine1.drive(EngineControllerConsts::MAX_SPEED);
    m_engine3.drive(EngineControllerConsts::MAX_SPEED);

    m_engine2.drive(EngineControllerConsts::HALF_SPEED, false);
    m_engine4.drive(EngineControllerConsts::HALF_SPEED, false);
}

void EngineController::leftTurnBackward()
{
    m_engine1.drive(EngineControllerConsts::HALF_SPEED, false);
    m_engine3.drive(EngineControllerConsts::HALF_SPEED, false);

    m_engine2.drive(EngineControllerConsts::MAX_SPEED, false);
    m_engine4.drive(EngineControllerConsts::MAX_SPEED, false);
}

void EngineController::rightTurnBackward()
{
    m_engine1.drive(EngineControllerConsts::MAX_SPEED, false);
    m_engine3.drive(EngineControllerConsts::MAX_SPEED, false);

    m_engine2.drive(EngineControllerConsts::HALF_SPEED, false);
    m_engine4.drive(EngineControllerConsts::HALF_SPEED, false);
}