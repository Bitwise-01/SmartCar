#pragma once
#include "engine_controller.hpp"
namespace stuck
{
class Constants
{
public:
    static constexpr double MIN_STUCK_DISTANCE = 0.2;
    static const unsigned int MAX_LOOPS = 3;
};
class Stuck
{
public:
    Stuck(engineController::EngineController *t_engineDriver);
    bool isStuck(double currentDistance);
    bool isProcessing();
    void evade();
    void reset();
    bool ranEvade();

private:
    engineController::EngineController *m_engineDriver;
    double m_lastDistance;
    unsigned int m_right;
    unsigned int m_left;
    unsigned int m_full;

    unsigned int m_rightBack;
    unsigned int m_leftBack;
    bool m_ranEvade;

    void leftPower();
    void rightPower();
};
} // namespace stuck
