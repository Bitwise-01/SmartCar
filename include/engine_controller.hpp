#pragma once
#include "engine.hpp"
#include "distance.hpp"

namespace engineController
{
class EngineControllerConsts
{
public:
    static const unsigned int MAX_TURNS = 6U; // Max turns
    static const unsigned int MAX_SPEED = 254U;
    static const unsigned int HALF_SPEED = 140U; // I know it's not half the speed
};

class EngineController
{
public:
    EngineController(engine::Engine *t_e1, engine::Engine *t_e2, engine::Engine *t_e3, engine::Engine *t_e4);
    unsigned int getSpeed() const;
    bool isCheckingDirection();
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

    // Directions
    void chooseDirection(distance::Distance *distanceManager);

private:
    engine::Engine
        *m_engine1,
        *m_engine2,
        *m_engine3,
        *m_engine4;

    unsigned int m_currentSpeed;

    // checking directions
    unsigned int m_fullTurns;
    unsigned int m_rights;
    unsigned int m_lefts;
    unsigned int m_rev;

    int m_rightDistance;
    int m_leftDistance;

    // Forward & Backward
    bool m_lastForward;
    unsigned int m_counter;

    // Turns
    bool m_lastForward1;
    bool m_lastForward2;
    unsigned int m_turnsCounter;

    // Directions
    bool checkRight();
    bool checkLeft();

    void m_drive(engine::Engine *t_e1, engine::Engine *t_e2, unsigned int t_speed1, bool t_goForward1,
                 engine::Engine *t_e3, engine::Engine *t_e4, unsigned int t_speed2, bool t_goForward2);
};
} // namespace engineController
