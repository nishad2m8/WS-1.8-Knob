#include "brightness_control.h"
#include "lcd_bl_pwm_bsp.h"
#include "screen_main.h"
#include <esp_log.h>

static const char *TAG = "BrightnessControl";

uint8_t BrightnessControl::currentBrightness = 50;

void BrightnessControl::init() {
    ESP_LOGI(TAG, "Initializing brightness control");
    setBrightness(currentBrightness);
    updateArc();
}

void BrightnessControl::setBrightness(uint8_t value) {
    // Clamp value between min and max
    if (value < MIN_BRIGHTNESS) value = MIN_BRIGHTNESS;
    if (value > MAX_BRIGHTNESS) value = MAX_BRIGHTNESS;
    
    currentBrightness = value;
    
    // Set actual hardware brightness
    // Convert percentage (0-100) to PWM duty (0-255)
    uint16_t pwmDuty = (value * 255) / 100;
    setUpdutySubdivide(pwmDuty);
    
    ESP_LOGI(TAG, "Brightness set to: %d%% (PWM: %d)", value, pwmDuty);
}

uint8_t BrightnessControl::getBrightness() {
    return currentBrightness;
}

void BrightnessControl::updateArc() {
    if (objects.main_arc_brightness != nullptr) {
        // Arc range is 0-100
        lv_arc_set_value(objects.main_arc_brightness, currentBrightness);
    }
}

void BrightnessControl::handleRotaryLeft() {
    if (isActive()) {
        uint8_t newBrightness = currentBrightness - BRIGHTNESS_STEP;
        setBrightness(newBrightness);
        updateArc();
        ESP_LOGI(TAG, "Rotary left - brightness: %d", currentBrightness);
    }
}

void BrightnessControl::handleRotaryRight() {
    if (isActive()) {
        uint8_t newBrightness = currentBrightness + BRIGHTNESS_STEP;
        setBrightness(newBrightness);
        updateArc();
        ESP_LOGI(TAG, "Rotary right - brightness: %d", currentBrightness);
    }
}

bool BrightnessControl::isActive() {
    // Brightness control is active when the launcher is expanded
    // and we're on the main screen
    if (objects.main_arc_brightness != nullptr) {
        return lv_obj_has_state(objects.main_arc_brightness, LV_STATE_CHECKED);
    }
    return false;
}