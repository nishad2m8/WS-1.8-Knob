#ifndef HAPTIC_FEEDBACK_H
#define HAPTIC_FEEDBACK_H

#include <Arduino.h>
#include "SensorDRV2605.hpp"
#include "driver/i2c.h"

enum HapticEffect {
    HAPTIC_STRONG_CLICK = 1,
    HAPTIC_STRONG_CLICK_60 = 2,
    HAPTIC_STRONG_CLICK_30 = 3,
    HAPTIC_SHARP_CLICK = 4,
    HAPTIC_SHARP_CLICK_60 = 5,
    HAPTIC_SHARP_CLICK_30 = 6,
    HAPTIC_SOFT_BUMP = 7,
    HAPTIC_SOFT_BUMP_60 = 8,
    HAPTIC_SOFT_BUMP_30 = 9,
    HAPTIC_DOUBLE_CLICK = 10,
    HAPTIC_DOUBLE_CLICK_60 = 11,
    HAPTIC_TRIPLE_CLICK = 12,
    HAPTIC_SOFT_FUZZ = 13,
    HAPTIC_STRONG_BUZZ = 14,
    HAPTIC_MEDIUM_CLICK = 21,
    HAPTIC_SHARP_TICK = 24,
    HAPTIC_TRANSITION_CLICK = 58,
    HAPTIC_TRANSITION_HUM = 64
};

class HapticFeedback {
public:
    static bool init();
    static void playEffect(HapticEffect effect);
    static void playButtonPress();
    static void playSwipeGesture();
    static void playRotaryTick();
    static void playError();
    static void playSuccess();
    
private:
    static SensorDRV2605 drv;
    static bool initialized;
    static const int SENSOR_SDA = 11;
    static const int SENSOR_SCL = 12;
};

#endif