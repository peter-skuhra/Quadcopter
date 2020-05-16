#ifndef PWM_PIN_LISTENER_HPP
#define PWM_PIN_LISTENER_HPP

#include <Arduino.h>


namespace command
{

class PWMPinListener
{
public:

    PWMPinListener(uint8_t pin);

    ~PWMPinListener();

    uint16_t ReadChannel() const;

    inline void HandleInterrupt();


private:

    const uint8_t pin_;

    uint16_t value_;

    bool update_started_;

    uint32_t time_start_;

};

}

#endif
