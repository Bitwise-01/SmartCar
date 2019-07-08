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