#include "screen_davinci.h"
#include "screen_manager.h"
#include <Arduino.h>
#include "lcd_config.h"
#include "haptic_feedback.h"
#include <USBHIDKeyboard.h>
#include "USB.h"

// Create an instance of USBHIDKeyboard
extern USBHIDKeyboard usbKeyboard;

void ScreenDavinci::setupGestures() {
    Serial.println("[ScreenDavinci] Setting up gestures...");
    
    // Use timer to ensure objects are initialized
    lv_timer_t* timer = lv_timer_create([](lv_timer_t* timer) {
        lv_timer_del(timer);
        
        if (objects.davinci == nullptr) {
            Serial.println("[ScreenDavinci] ERROR: davinci object is null!");
            return;
        }
        
        Serial.println("[ScreenDavinci] Adding gesture event callback");
        
        // Ensure the screen is not scrollable for better gesture detection
        lv_obj_clear_flag(objects.davinci, LV_OBJ_FLAG_SCROLLABLE);
        
        // Add swipe gesture event
        lv_obj_add_event_cb(objects.davinci, onSwipeLeft, LV_EVENT_GESTURE, NULL);
        
        // Setup button event handlers
        setupButtonHandlers();
        
        Serial.println("[ScreenDavinci] Gesture setup complete");
    }, 100, NULL);
}

void ScreenDavinci::setupButtonHandlers() {
    Serial.println("[ScreenDavinci] Setting up button handlers...");
    
    // Attach event handlers to the UI buttons
    if (objects.button_cut != nullptr) {
        lv_obj_add_event_cb(objects.button_cut, onButtonCut, LV_EVENT_CLICKED, NULL);
    }
    
    if (objects.button_delete != nullptr) {
        lv_obj_add_event_cb(objects.button_delete, onButtonDelete, LV_EVENT_CLICKED, NULL);
    }
    
    if (objects.button_ripple_delete != nullptr) {
        lv_obj_add_event_cb(objects.button_ripple_delete, onButtonRippleDelete, LV_EVENT_CLICKED, NULL);
    }
    
    if (objects.button_next != nullptr) {
        lv_obj_add_event_cb(objects.button_next, onButtonNext, LV_EVENT_CLICKED, NULL);
    }
    
    if (objects.button_previous != nullptr) {
        lv_obj_add_event_cb(objects.button_previous, onButtonPrevious, LV_EVENT_CLICKED, NULL);
    }
    
    Serial.println("[ScreenDavinci] Button handlers setup complete");
}

void ScreenDavinci::sendKeyPress(uint8_t modifier, uint8_t key) {
    Serial.printf("[ScreenDavinci] Sending KeyPress: Modifier=0x%02X, Key=0x%02X\n", modifier, key);
    usbKeyboard.press(modifier);
    usbKeyboard.press(key);
    usbKeyboard.releaseAll();
    Serial.println("[ScreenDavinci] Key sent successfully");
}

void ScreenDavinci::onSwipeLeft(lv_event_t* e) {
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    
    Serial.print("[ScreenDavinci] Gesture detected: ");
    switch(dir) {
        case LV_DIR_LEFT:
            Serial.println("LEFT");
            break;
        case LV_DIR_RIGHT:
            Serial.println("RIGHT - Switching to main screen");
            HapticFeedback::playSwipeGesture();
            ScreenManager::getInstance()->switchToScreen(SCREEN_MAIN);
            break;
        case LV_DIR_TOP:
            Serial.println("UP");
            break;
        case LV_DIR_BOTTOM:
            Serial.println("DOWN");
            break;
        default:
            Serial.println("UNKNOWN");
            break;
    }
}

// Button event handlers
void ScreenDavinci::onButtonCut(lv_event_t* e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        Serial.println("[ScreenDavinci] Cut button pressed");
        HapticFeedback::playButtonPress();
        sendKeyPress(KEY_LEFT_GUI, 'b'); // CMD + B for cut timeline
    }
}

void ScreenDavinci::onButtonDelete(lv_event_t* e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        Serial.println("[ScreenDavinci] Delete button pressed");
        HapticFeedback::playButtonPress();
        usbKeyboard.press(KEY_BACKSPACE);
        usbKeyboard.release(KEY_BACKSPACE);
    }
}

void ScreenDavinci::onButtonRippleDelete(lv_event_t* e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        Serial.println("[ScreenDavinci] Ripple delete button pressed");
        HapticFeedback::playButtonPress();
        sendKeyPress(KEY_LEFT_SHIFT, KEY_BACKSPACE); // Shift + Backspace
    }
}

void ScreenDavinci::onButtonNext(lv_event_t* e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        Serial.println("[ScreenDavinci] Next button pressed");
        HapticFeedback::playButtonPress();
        sendKeyPress(KEY_LEFT_GUI, KEY_RIGHT_ARROW); // CMD + Right Arrow
    }
}

void ScreenDavinci::onButtonPrevious(lv_event_t* e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        Serial.println("[ScreenDavinci] Previous button pressed");
        HapticFeedback::playButtonPress();
        sendKeyPress(KEY_LEFT_GUI, KEY_LEFT_ARROW); // CMD + Left Arrow
    }
}