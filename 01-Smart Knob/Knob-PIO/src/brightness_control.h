#ifndef BRIGHTNESS_CONTROL_H
#define BRIGHTNESS_CONTROL_H

#include <Arduino.h>
#include "ui.h"
#include "lcd_config.h"

class BrightnessControl {
public:
    static void init();
    static void setBrightness(uint8_t value);
    static uint8_t getBrightness();
    static void updateArc();
    static void handleRotaryLeft();
    static void handleRotaryRight();
    static bool isActive();
    
private:
    static uint8_t currentBrightness;
    static const uint8_t MIN_BRIGHTNESS = 10;
    static const uint8_t MAX_BRIGHTNESS = 100;
    static const uint8_t BRIGHTNESS_STEP = 1;
};

#endif