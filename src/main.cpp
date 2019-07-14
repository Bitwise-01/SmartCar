#include <Arduino.h>
#include "thread.hpp"
#include "engine.hpp"
#include "distance.hpp"
#include "engine_controller.hpp"

// Distance
namespace distanceController
{
class Constants
{
public:
    static const unsigned char TRIG_PIN = 22;
    static const unsigned char ECHO_PIN = 24;
};
} // namespace distanceController

namespace motors
{
class Constants
{
public:
    static const unsigned long ENGINE_CHECK_INTERVAL = 150UL;

    // Motors : Driver 1
    static const unsigned char MOTOR_1 = 13;          // EnA
    static const unsigned char MOTOR_1_FORWARD = 12;  // in1
    static const unsigned char MOTOR_1_BACKWARD = 11; // in2

    static const unsigned char MOTOR_2 = 10;         // EnB
    static const unsigned char MOTOR_2_FORWARD = 9;  // in3
    static const unsigned char MOTOR_2_BACKWARD = 8; // in4

    // Motors : Driver 2
    static const unsigned char MOTOR_3 = 7;          // EnA
    static const unsigned char MOTOR_3_FORWARD = 6;  // in1
    static const unsigned char MOTOR_3_BACKWARD = 5; // in2

    static const unsigned char MOTOR_4 = 4;          // EnB
    static const unsigned char MOTOR_4_FORWARD = 3;  // in3
    static const unsigned char MOTOR_4_BACKWARD = 2; // in4
};
} // namespace motors

// Engines
engine::Engine
    engine1(motors::Constants::MOTOR_1, motors::Constants::MOTOR_1_FORWARD, motors::Constants::MOTOR_1_BACKWARD),
    engine2(motors::Constants::MOTOR_2, motors::Constants::MOTOR_2_FORWARD, motors::Constants::MOTOR_2_BACKWARD),
    engine3(motors::Constants::MOTOR_3, motors::Constants::MOTOR_3_FORWARD, motors::Constants::MOTOR_3_BACKWARD),
    engine4(motors::Constants::MOTOR_4, motors::Constants::MOTOR_4_FORWARD, motors::Constants::MOTOR_4_BACKWARD);

// Engine controller
engineController::EngineController engineDriver(engine1, engine2, engine3, engine4);

// Distance
distance::Distance *distanceManager = new distance::Distance(distanceController::Constants::TRIG_PIN,
                                                             distanceController::Constants::ECHO_PIN);

// Func decs
void trigPinLow();
void trigPinHigh();
void measureDistance();

// Temp loop
void nothin();

thread::Thread nothinThread(nothin, motors::Constants::ENGINE_CHECK_INTERVAL);

// Threads
thread::Thread trigPinLowThread(trigPinLow, distance::Constants::TRIG_PIN_LOW_INTERVAL);
thread::Thread trigPinHighThread(trigPinHigh, distance::Constants::TRIG_PIN_HIGH_INTERVAL);
thread::Thread measureDistanceThread(measureDistance, distance::Constants::MEASURE_DISTANCE_INTERVAL);

void setup()
{
    struct _pinMode
    {
        _pinMode(const unsigned char mode) : m_mode(mode){};

        void operator()(const unsigned char pin)
        {
            pinMode(pin, m_mode);
        }

        const unsigned char m_mode;
    } output(OUTPUT);

    // Motor 1
    output(motors::Constants::MOTOR_1);
    output(motors::Constants::MOTOR_1_FORWARD);
    output(motors::Constants::MOTOR_1_BACKWARD);

    // Motor 2
    output(motors::Constants::MOTOR_2);
    output(motors::Constants::MOTOR_2_FORWARD);
    output(motors::Constants::MOTOR_2_BACKWARD);

    // Motor 3
    output(motors::Constants::MOTOR_3);
    output(motors::Constants::MOTOR_3_FORWARD);
    output(motors::Constants::MOTOR_3_BACKWARD);

    // Motor 4
    output(motors::Constants::MOTOR_4);
    output(motors::Constants::MOTOR_4_FORWARD);
    output(motors::Constants::MOTOR_4_BACKWARD);

    // Distance
    pinMode(distanceController::Constants::ECHO_PIN, INPUT);
    pinMode(distanceController::Constants::TRIG_PIN, OUTPUT);

    Serial.begin(9600);
}

void loop()
{

    // Distance
    trigPinLowThread.run();
    trigPinHighThread.run();
    measureDistanceThread.run();

    // Driver
    nothinThread.run();
}

void nothin()
{
    double distance = distanceManager->getDistance();

    // if (distance > distance::Constants::MIN_DIST)
    // {
    //     engineDriver.driveForward();
    // }
    // else
    // {
    //     engineDriver.driveBackward();
    // }

    if (distance > distance::Constants::MIN_DIST)
    {
        if (abs(distance - distance::Constants::MIN_DIST) >= distance::Constants::SAFE_DIST * 2)
        {
            engineDriver.driveForward();
        }
        else
        {
            engineDriver.driveForward(engineController::EngineControllerConsts::HALF_SPEED);
        }
    }
    else
    {
        if (abs(distance - distance::Constants::MIN_DIST) >= distance::Constants::SAFE_DIST)
        {
            engineDriver.driveBackward(engineController::EngineControllerConsts::HALF_SPEED);
        }
        else
        {
            engineDriver.driveBackward();
        }
    }
}

void trigPinLow()
{
    distanceManager->trigPinLow();
}

void trigPinHigh()
{
    distanceManager->trigPinHigh();
}

void measureDistance()
{
    distanceManager->measureDistance();
}