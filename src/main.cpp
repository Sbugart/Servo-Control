#include "../lib/esp_pwm.hpp"
#include "../lib/configs.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"



void test_task(void *pvParameters)
{
    Pins* pin = (Pins*) pvParameters;

    ESP_PWM servo(LEDC_CHANNEL_0);
    servo.attach(pin->servo_motor);
    servo.start();

    while(true)
    {
        servo.set_angle(0);
        vTaskDelay(pdMS_TO_TICKS(2000));
        servo.set_angle(90);
        vTaskDelay(pdMS_TO_TICKS(2000));
        servo.set_angle(-90);
        vTaskDelay(pdMS_TO_TICKS(2000));   
    }
}

extern "C" void app_main()
{
    static Pins pin;
    pin.servo_motor = 35;

    xTaskCreatePinnedToCore(test_task,"test_task",2048, &pin,5,NULL,0);
}