#include "haptic_feedback.h"
#include <esp_log.h>

static const char *TAG = "HapticFeedback";

SensorDRV2605 HapticFeedback::drv;
bool HapticFeedback::initialized = false;

bool HapticFeedback::init() {
    ESP_LOGI(TAG, "Initializing DRV2605 haptic driver");
    
    // Use the same I2C port as the touch controller (I2C_NUM_0)
    if (!drv.begin(I2C_NUM_0, DRV2605_SLAVE_ADDRESS)) {
        ESP_LOGE(TAG, "Failed to initialize DRV2605 - check your wiring!");
        return false;
    }
    
    ESP_LOGI(TAG, "DRV2605 initialized successfully");
    
    initialized = true;
    return true;
}

void HapticFeedback::playEffect(HapticEffect effect) {
    if (!initialized) {
        ESP_LOGW(TAG, "Haptic not initialized, skipping effect %d", effect);
        return;
    }
    
    ESP_LOGI(TAG, "Playing haptic effect: %d", effect);
    drv.setWaveform(0, effect);
    drv.setWaveform(1, 0);
    drv.run();
}

void HapticFeedback::playButtonPress() {
    ESP_LOGD(TAG, "Playing button press haptic");
    playEffect(HAPTIC_STRONG_CLICK);
}

void HapticFeedback::playSwipeGesture() {
    ESP_LOGD(TAG, "Playing swipe gesture haptic");
    playEffect(HAPTIC_SOFT_BUMP_60);
}

void HapticFeedback::playRotaryTick() {
    ESP_LOGD(TAG, "Playing rotary tick haptic");
    playEffect(HAPTIC_SHARP_TICK);
}

void HapticFeedback::playError() {
    ESP_LOGD(TAG, "Playing error haptic");
    playEffect(HAPTIC_STRONG_BUZZ);
}

void HapticFeedback::playSuccess() {
    ESP_LOGD(TAG, "Playing success haptic");
    playEffect(HAPTIC_DOUBLE_CLICK);
}