#include "rotary_encoder.h"
#include "brightness_control.h"
#include "screen_manager.h"
#include "screen_davinci.h"
#include "bidi_switch_knob.h"
#include <esp_log.h>
#include <esp_err.h>
#include <USBHIDKeyboard.h>

static const char *TAG = "RotaryEncoder";

EventGroupHandle_t RotaryEncoder::knobEventGroup = NULL;
void* RotaryEncoder::knobHandle = NULL;

// External reference to global USB keyboard
extern USBHIDKeyboard usbKeyboard;

void RotaryEncoder::init() {
    ESP_LOGI(TAG, "Initializing rotary encoder");
    
    knobEventGroup = xEventGroupCreate();
    if (knobEventGroup == NULL) {
        ESP_LOGE(TAG, "Failed to create event group");
        return;
    }
    
    // Configure knob
    knob_config_t cfg = {
        .gpio_encoder_a = ENCODER_PIN_A,
        .gpio_encoder_b = ENCODER_PIN_B,
    };
    
    knobHandle = iot_knob_create(&cfg);
    if (knobHandle == NULL) {
        ESP_LOGE(TAG, "Failed to create knob");
        return;
    }
    
    // Register callbacks
    ESP_ERROR_CHECK(iot_knob_register_cb(knobHandle, KNOB_LEFT, knobLeftCallback, NULL));
    ESP_ERROR_CHECK(iot_knob_register_cb(knobHandle, KNOB_RIGHT, knobRightCallback, NULL));
    
    // Create encoder task
    xTaskCreate(encoderTask, "encoder_task", 3000, NULL, 2, NULL);
    
    ESP_LOGI(TAG, "Rotary encoder initialized");
}

void RotaryEncoder::knobLeftCallback(void *arg, void *data) {
    xEventGroupSetBits(knobEventGroup, EVENT_LEFT);
}

void RotaryEncoder::knobRightCallback(void *arg, void *data) {
    xEventGroupSetBits(knobEventGroup, EVENT_RIGHT);
}

void RotaryEncoder::handleDavinciRotary(bool clockwise) {
    ESP_LOGI(TAG, "DaVinci rotary: %s", clockwise ? "RIGHT" : "LEFT");
    
    if (clockwise) {
        // Right rotation - Right arrow key
        usbKeyboard.press(KEY_RIGHT_ARROW);
        usbKeyboard.release(KEY_RIGHT_ARROW);
    } else {
        // Left rotation - Left arrow key  
        usbKeyboard.press(KEY_LEFT_ARROW);
        usbKeyboard.release(KEY_LEFT_ARROW);
    }
}

void RotaryEncoder::encoderTask(void *arg) {
    ESP_LOGI(TAG, "Encoder task started");
    
    for (;;) {
        EventBits_t bits = xEventGroupWaitBits(
            knobEventGroup,
            EVENT_ALL,
            pdTRUE,  // Clear bits after reading
            pdFALSE, // Don't wait for all bits
            pdMS_TO_TICKS(100)
        );
        
        ScreenType currentScreen = ScreenManager::getInstance()->getCurrentScreen();
        
        if (bits & EVENT_LEFT) {
            if (currentScreen == SCREEN_MAIN) {
                BrightnessControl::handleRotaryLeft();
            } else if (currentScreen == SCREEN_DAVINCI) {
                handleDavinciRotary(false); // Counter-clockwise
            }
        }
        
        if (bits & EVENT_RIGHT) {
            if (currentScreen == SCREEN_MAIN) {
                BrightnessControl::handleRotaryRight();
            } else if (currentScreen == SCREEN_DAVINCI) {
                handleDavinciRotary(true); // Clockwise
            }
        }
    }
}