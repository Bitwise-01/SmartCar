#include <Arduino.h>

#include "list.hpp"
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

distance::Distance *distanceManager = new distance::Distance(distanceController::Constants::TRIG_PIN,
                                                             distanceController::Constants::ECHO_PIN);

void trigPinLow();
void trigPinHigh();
void measureSpeed();
void measureDistance();

// Threads
thread::Thread trigPinLowThread(trigPinLow, distance::Constants::TRIG_PIN_LOW_INTERVAL);
thread::Thread trigPinHighThread(trigPinHigh, distance::Constants::TRIG_PIN_HIGH_INTERVAL);
thread::Thread measureSpeedThread(measureSpeed, distance::Constants::SPEED_UPDATE_INTERVAL);
thread::Thread measureDistanceThread(measureDistance, distance::Constants::MEASURE_DISTANCE_INTERVAL);

void setup()
{
    Serial.begin(9600);
    pinMode(distanceController::Constants::ECHO_PIN, INPUT);
    pinMode(distanceController::Constants::TRIG_PIN, OUTPUT);
}

void loop()
{
    trigPinLowThread.run();
    trigPinHighThread.run();
    measureSpeedThread.run();
    measureDistanceThread.run();
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

void measureSpeed()
{
    distanceManager->measureSpeed();
    Serial.print("Speed: ");
    Serial.print(distanceManager->getSpeed());
    Serial.println(" (cm/s)");
}

/*
namespace motors
{
class Constants
{
public:
    static const unsigned int ENGINE_CHECK_INTERVAL = 150U;

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

// Function declarations
void driver();

// Threads
thread::Thread engineDriverThread(driver, motors::Constants::ENGINE_CHECK_INTERVAL);

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

    Serial.begin(9600);
}

void loop()
{
    engineDriverThread.run();
}

void driver()
{
    engineDriver.accelerate();

    if (engineDriver.slowDown())
    {
        Serial.print("Rev ");
        Serial.println(engineDriver.getSpeed());
        engineDriver.decelerate(false);
    }

    if (engineDriver.speedUp())
    {
        Serial.print("Str ");
        Serial.println(engineDriver.getSpeed());
        engineDriver.accelerate();
    }
}
*/

/*
void drive(int motor, int forward, int backward, int direction, int power = CRUISING_SPEED)
{

    // Turn off
    digitalWrite(forward, LOW);
    digitalWrite(backward, LOW);
    delay(MOTOR_DELAY);

    // Set direction
    if (direction == FORWARD)
    {
        digitalWrite(forward, HIGH);
        digitalWrite(backward, LOW);
    }
    else
    {
        digitalWrite(forward, LOW);
        digitalWrite(backward, HIGH);
    }

    // Apply power
    analogWrite(motor, power);
}

// Turns

void softLeftTurn()
{
    drive(MOTOR_1, MOTOR_1_FORWARD, MOTOR_1_BACKWARD, BACKWARD, 0);
    drive(MOTOR_3, MOTOR_3_FORWARD, MOTOR_3_BACKWARD, BACKWARD, CRUISING_SPEED - 50);

    drive(MOTOR_2, MOTOR_2_FORWARD, MOTOR_2_BACKWARD, FORWARD);
    drive(MOTOR_4, MOTOR_4_FORWARD, MOTOR_4_BACKWARD, FORWARD);
}

void hardLeftTurn()
{
}

void softRightTurn()
{
    drive(MOTOR_1, MOTOR_1_FORWARD, MOTOR_1_BACKWARD, FORWARD);
    drive(MOTOR_3, MOTOR_3_FORWARD, MOTOR_3_BACKWARD, FORWARD);

    drive(MOTOR_2, MOTOR_2_FORWARD, MOTOR_2_BACKWARD, BACKWARD, 0);
    drive(MOTOR_4, MOTOR_4_FORWARD, MOTOR_4_BACKWARD, BACKWARD, CRUISING_SPEED - 50);
}

void hardRightTurn()
{
}

void loop()
{
    // drive(MOTOR_1, MOTOR_1_FORWARD, MOTOR_1_BACKWARD, FORWARD);
    // drive(MOTOR_2, MOTOR_2_FORWARD, MOTOR_2_BACKWARD, FORWARD);
    // drive(MOTOR_3, MOTOR_3_FORWARD, MOTOR_3_BACKWARD, FORWARD);
    // drive(MOTOR_4, MOTOR_4_FORWARD, MOTOR_4_BACKWARD, FORWARD);
    // delay(8000);

    // drive(MOTOR_1, MOTOR_1_FORWARD, MOTOR_1_BACKWARD, BACKWARD);
    // drive(MOTOR_2, MOTOR_2_FORWARD, MOTOR_2_BACKWARD, BACKWARD);
    // drive(MOTOR_3, MOTOR_3_FORWARD, MOTOR_3_BACKWARD, BACKWARD);
    // drive(MOTOR_4, MOTOR_4_FORWARD, MOTOR_4_BACKWARD, BACKWARD);
    // delay(8000);

    softLeftTurn();
    delay(2000);

    softRightTurn();
    delay(2000);
}
*/