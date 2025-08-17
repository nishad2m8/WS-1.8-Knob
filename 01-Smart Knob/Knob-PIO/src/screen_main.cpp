#include "screen_main.h"
#include "screen_manager.h"
#include <Arduino.h>
#include "lcd_config.h"
#include "haptic_feedback.h"

bool ScreenMain::launcherExpanded = false;

void ScreenMain::resetState() {
    Serial.println("[ScreenMain] Resetting state");
    launcherExpanded = false;
}

void ScreenMain::setupGestures() {
    Serial.println("[ScreenMain] Setting up gestures...");
    
    // Reset state first
    resetState();
    
    // Wait a bit for UI to be fully initialized
    lv_timer_t* timer = lv_timer_create([](lv_timer_t* timer) {
        lv_timer_del(timer);
        
        // Check if objects are initialized
        if (objects.main == nullptr) {
            Serial.println("[ScreenMain] ERROR: main object is null!");
            return;
        }
        
        if (objects.conainer_launcer == nullptr) {
            Serial.println("[ScreenMain] ERROR: container launcher object is null!");
            return;
        }
        
        Serial.println("[ScreenMain] Objects initialized, setting up events");
        
        // Clear any existing event callbacks first
        lv_obj_remove_event_cb(objects.main, onSwipeUp);
        if (objects.button_davinci != nullptr) {
            lv_obj_remove_event_cb(objects.button_davinci, onDavinciButtonPressed);
        }
        
        // Add swipe gesture to main screen
        lv_obj_add_event_cb(objects.main, onSwipeUp, LV_EVENT_GESTURE, NULL);
        
        // Add button press event for davinci button
        if (objects.button_davinci != nullptr) {
            lv_obj_add_event_cb(objects.button_davinci, onDavinciButtonPressed, LV_EVENT_CLICKED, NULL);
            Serial.println("[ScreenMain] Davinci button event added");
        } else {
            Serial.println("[ScreenMain] WARNING: Davinci button is null!");
        }
        
        // Set initial launcher position
        lv_obj_set_y(objects.conainer_launcer, 300);
        launcherExpanded = false;
        Serial.println("[ScreenMain] Launcher positioned at y=300");
        
        // Set initial brightness arc state
        if (objects.main_arc_brightness != nullptr) {
            lv_obj_clear_state(objects.main_arc_brightness, LV_STATE_CHECKED);
        }
        
        Serial.println("[ScreenMain] Setup complete");
    }, 100, NULL);
}

void ScreenMain::onSwipeUp(lv_event_t* e) {
    if (objects.conainer_launcer == nullptr) return;
    
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    
    Serial.print("[ScreenMain] Gesture detected: ");
    switch(dir) {
        case LV_DIR_TOP:
            Serial.print("UP");
            break;
        case LV_DIR_BOTTOM:
            Serial.print("DOWN");
            break;
        case LV_DIR_LEFT:
            Serial.print("LEFT");
            break;
        case LV_DIR_RIGHT:
            Serial.print("RIGHT");
            break;
        default:
            Serial.print("UNKNOWN");
            break;
    }
    Serial.print(", Launcher expanded: ");
    Serial.println(launcherExpanded ? "true" : "false");
    
    // Simple approach - just use the gesture as detected by LVGL
    // LVGL already handles the rotation internally
    if (dir == LV_DIR_TOP && !launcherExpanded) {
        // Swipe up - expand launcher
        Serial.println("[ScreenMain] Expanding launcher to y=0");
        HapticFeedback::playSwipeGesture();
        setLauncherPosition(0, true);
        launcherExpanded = true;
        
        if (objects.main_arc_brightness != nullptr) {
            lv_obj_add_state(objects.main_arc_brightness, LV_STATE_CHECKED);
        }
    }
    else if (dir == LV_DIR_BOTTOM && launcherExpanded) {
        // Swipe down - collapse launcher
        Serial.println("[ScreenMain] Collapsing launcher to y=300");
        HapticFeedback::playSwipeGesture();
        setLauncherPosition(300, true);
        launcherExpanded = false;
        
        if (objects.main_arc_brightness != nullptr) {
            lv_obj_clear_state(objects.main_arc_brightness, LV_STATE_CHECKED);
        }
    }
}

void ScreenMain::setLauncherPosition(int16_t y, bool animate) {
    if (objects.conainer_launcer == nullptr) return;
    
    if (animate) {
        lv_anim_t anim;
        lv_anim_init(&anim);
        lv_anim_set_var(&anim, objects.conainer_launcer);
        lv_anim_set_values(&anim, lv_obj_get_y(objects.conainer_launcer), y);
        lv_anim_set_time(&anim, 300);
        lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)lv_obj_set_y);
        lv_anim_set_path_cb(&anim, lv_anim_path_ease_in_out);
        lv_anim_start(&anim);
    } else {
        lv_obj_set_y(objects.conainer_launcer, y);
    }
}

void ScreenMain::onDavinciButtonPressed(lv_event_t* e) {
    Serial.println("[ScreenMain] Davinci button pressed - switching to Davinci screen");
    HapticFeedback::playButtonPress();
    ScreenManager::getInstance()->switchToScreen(SCREEN_DAVINCI);
}