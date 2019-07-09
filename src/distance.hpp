#pragma once
#include <Arduino.h>
namespace distance
{
class Constants
{
public:
    // Intervals (millis)
    static const unsigned long TRIG_PIN_LOW_INTERVAL = 2UL;
    static const unsigned long TRIG_PIN_HIGH_INTERVAL = 1UL;
    static const unsigned long MEASURE_DISTANCE_INTERVAL = 35UL;

    // Limits
    static constexpr double MIN_DIST = 15.0;  // 18.5; // cm
    static const unsigned int SAFE_DIST = 3U; // Go slow when inder this distance

    // Counts
    static const unsigned int TRIG_PIN_LOW_MAX_COUNTS = 2U;
    static const unsigned int TRIG_PIN_HIGH_MAX_COUNTS = 10U;
};
class Distance
{
public:
    Distance(unsigned char t_trigPin, unsigned char t_echoPin);
    double getDistance() const;
    double getSpeed() const;
    void measureDistance();
    void trigPinHigh();
    void trigPinLow();

private:
    double m_getDistance();

    double m_currentDistance;
    const unsigned char m_echoPin;
    const unsigned char m_trigPin;
    unsigned int m_trigPinLowCounter;
    unsigned int m_trigPinHighCounter;
};
} // namespace distance