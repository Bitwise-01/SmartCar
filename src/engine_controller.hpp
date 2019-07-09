#pragma once
#include "engine.hpp"

namespace engineController
{
class EngineControllerConsts
{
public:
    static const unsigned int MAX_SPEED = 254U;
    static const unsigned int HALF_SPEED = 140U; // I know it's not half the speed
};

class EngineController
{
public:
    EngineController(engine::Engine &t_e1, engine::Engine &t_e2, engine::Engine &t_e3, engine::Engine &t_e4);
    unsigned int getSpeed() const;
    bool isMovingForward();
    void brake();

    void driveForward(unsigned int speed = 0);
    void driveBackward(unsigned int speed = 0);

    // Turns: Forward
    void leftTurnForward();
    void rightTurnForward();
    void softLeftTurnForward();
    void softRightTurnForward();

    // Turns: Backward
    void leftTurnBackward();
    void rightTurnBackward();
    void softLeftTurnBackward();
    void softRightTurnBackward();

private:
    engine::Engine
        m_engine1,
        m_engine2,
        m_engine3,
        m_engine4;

    unsigned int m_currentSpeed;

    void m_drive(bool t_goForward = true);
};
} // namespace engineController
