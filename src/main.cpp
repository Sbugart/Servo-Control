#include "../lib/esc_pwm.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C" void app_main()
{
    ESC_PWM servo(LEDC_CHANNEL_0);

    servo.attach(35);

    while(true)
    {
        servo.set_angle(0);
        vTaskDelay(pdMS_TO_TICKS(3000));

        servo.set_angle(90);
        vTaskDelay(pdMS_TO_TICKS(3000));

        servo.set_angle(-90);
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}