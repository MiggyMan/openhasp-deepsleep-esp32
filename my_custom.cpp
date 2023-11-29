/* MIT License - Copyright (c) 2019-2022 Francis Van Roie
   For full license information read the LICENSE file in the project folder */

// USAGE: - Copy this file and rename it to my_custom.cpp
//        - Change false to true on line 9

#include "hasplib.h"

#if defined(HASP_USE_CUSTOM) && true // <-- set this to true in your code

#include "hasp_debug.h"
uint8_t last_hasp_sleep_state=0;

void check_for_powerdown() {

    esp_sleep_wakeup_cause_t wakeup_reason;

    wakeup_reason = esp_sleep_get_wakeup_cause();

    if(wakeup_reason == ESP_SLEEP_WAKEUP_TIMER) {
        dispatch_state_subtopic("sleep_state","I should be powering off about now");
        digitalWrite(GPIO_NUM_18, HIGH);
    }

}

void custom_setup() {

    check_for_powerdown();
    uint16_t sleep_timer=360;
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_17, 1);
    esp_sleep_enable_timer_wakeup(sleep_timer*1000000);
}


void custom_every_5seconds() {

}


void custom_loop() {
    // Non-blocking code here, this should execute very fast!
    uint8_t hasp_sleep_state = hasp_get_sleep_state();
    if(last_hasp_sleep_state != hasp_sleep_state) {
        itoa(hasp_sleep_state,numberArray,10);
        dispatch_state_subtopic("sleep_state",numberArray);
        switch (hasp_sleep_state) {
            case 0:
                haspDevice.set_backlight_level(255);
            break;
            case 1:
                haspDevice.set_backlight_level(32);
            break;
            case 2:
                //haspDevice.set_backlight_power(false);
                //delay(500);
                //esp_deep_sleep_start();
            break;
        }

        last_hasp_sleep_state = hasp_sleep_state;

    }
}

void custom_every_second() {
}

bool custom_pin_in_use(uint8_t pin) {
    return false;
}

void custom_get_sensors(JsonDocument& doc) {
}

void custom_topic_payload(const char* topic, const char* payload, uint8_t source){
}

#endif // HASP_USE_CUSTOM