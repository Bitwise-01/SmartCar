#include "distance.hpp"
using namespace distance;

Distance::Distance(unsigned char t_trigPin, unsigned char t_echoPin)
    : m_currentDistance(0.0),

      m_echoPin(t_echoPin),
      m_trigPin(t_trigPin),

      m_trigPinLowCounter(0U),
      m_trigPinHighCounter(0U)
{
}

void Distance::trigPinLow()
{
    if (m_trigPinLowCounter == 0)
    {
        digitalWrite(m_trigPin, LOW);
    }

    if (m_trigPinLowCounter < Constants::TRIG_PIN_LOW_MAX_COUNTS)
    {
        m_trigPinLowCounter++;
    }
}

void Distance::trigPinHigh()
{
    if (m_trigPinLowCounter == Constants::TRIG_PIN_LOW_MAX_COUNTS)
    {
        if (m_trigPinHighCounter == 0)
        {
            digitalWrite(m_trigPin, HIGH);
        }

        if (m_trigPinHighCounter < Constants::TRIG_PIN_HIGH_MAX_COUNTS)
        {
            m_trigPinHighCounter++;
        }
    }
}

void Distance::measureDistance()
{
    if (m_trigPinLowCounter == Constants::TRIG_PIN_LOW_MAX_COUNTS &&
        m_trigPinHighCounter == Constants::TRIG_PIN_HIGH_MAX_COUNTS)
    {
        digitalWrite(m_trigPin, LOW);
        unsigned long duration = pulseIn(m_echoPin, HIGH);

        m_currentDistance = ((duration / 2) / 29.1); // cm

        m_trigPinHighCounter = 0U;
        m_trigPinLowCounter = 0U;
    }
}

double Distance::getDistance() const
{
    return m_currentDistance;
}