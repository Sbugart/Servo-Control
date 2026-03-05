#ifndef ESC_PWM_HPP
#define ESC_PWM_HPP

#include "driver/ledc.h"

class ESC_PWM
{
private:

    int pin;

    ledc_channel_t channel;
    ledc_timer_t timer;

    ledc_mode_t speed_mode;

    int resolution;
    uint32_t freq;

    uint32_t max_duty;

public:

    ESC_PWM(ledc_channel_t channel,
            ledc_timer_t timer = LEDC_TIMER_0,
            ledc_mode_t speed_mode = LEDC_LOW_SPEED_MODE);


    bool attach(int pin, uint32_t freq = 50, int resolution = LEDC_TIMER_14_BIT);

    bool set_pulse_width(uint32_t pulse_us);

    bool set_angle(float angle);
};

#endif