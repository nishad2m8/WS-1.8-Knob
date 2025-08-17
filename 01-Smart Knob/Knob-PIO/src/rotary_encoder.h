#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

class RotaryEncoder {
public:
    static void init();
    static void registerHandler();
    
private:
    static void encoderTask(void *arg);
    static void knobLeftCallback(void *arg, void *data);
    static void knobRightCallback(void *arg, void *data);
    static void handleDavinciRotary(bool clockwise);
    
    static EventGroupHandle_t knobEventGroup;
    static void* knobHandle;
    
    static const uint8_t ENCODER_PIN_A = 8;
    static const uint8_t ENCODER_PIN_B = 7;
    static const uint32_t EVENT_LEFT = (1 << 0);
    static const uint32_t EVENT_RIGHT = (1 << 1);
    static const uint32_t EVENT_ALL = 0x00FFFFFF;
};

#endif