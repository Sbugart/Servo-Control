#include "../lib/esc_pwm.hpp"

ESC_PWM::ESC_PWM(ledc_channel_t channel,ledc_timer_t timer,ledc_mode_t speed_mode)
{
    this->channel = channel;
    this->timer = timer;
    this->speed_mode = speed_mode;
}


bool ESC_PWM::attach(int pin, uint32_t freq, int resolution)
{
    this->pin = pin;
    this->freq = freq;
    this->resolution = resolution;

    max_duty = (1 << resolution) - 1;

    ledc_timer_config_t pwm_timer = {
        .speed_mode = speed_mode,
        .duty_resolution = (ledc_timer_bit_t) resolution,
        .timer_num = timer,
        .freq_hz = freq,
        .clk_cfg = LEDC_AUTO_CLK
    };

    ledc_timer_config(&pwm_timer);

    ledc_channel_config_t pwm_channel = {
        .gpio_num = pin,
        .speed_mode = speed_mode,
        .channel = channel,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = timer,
        .duty = 0,
        .hpoint = 0
    };

    ledc_channel_config(&pwm_channel);

    return true;
}

bool ESC_PWM::set_pulse_width(uint32_t pulse_us)
{   
    uint32_t period_us = 1000000 / freq;

    uint32_t duty = (pulse_us * max_duty) / period_us;

    ledc_set_duty(speed_mode, channel, duty);
    ledc_update_duty(speed_mode, channel);

    return true;
}


/*
min_pulse = 500
max_pulse = 2500
center = 1500
*/
bool ESC_PWM::set_angle(float angle)
{
    if(angle < -90) angle = -90;
    if(angle > 90) angle = 90;

    uint32_t pulse = 1500 + angle * (2000.0 / 180.0);

    return set_pulse_width(pulse);
}