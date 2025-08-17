#include "ui_haptic_handler.h"
#include "haptic_feedback.h"
#include "ui.h"
#include <Arduino.h>

void UIHapticHandler::init() {
    Serial.println("[UIHapticHandler] Initializing haptic handlers");
    
    // Setup haptics after a short delay to ensure UI is fully initialized
    lv_timer_t* timer = lv_timer_create([](lv_timer_t* timer) {
        lv_timer_del(timer);
        setupButtonHaptics();
    }, 200, NULL);
}

void UIHapticHandler::setupButtonHaptics() {
    Serial.println("[UIHapticHandler] Setting up button haptics");
    
    // Add haptic feedback to all buttons in the UI
    if (objects.button_task != nullptr) {
        lv_obj_add_event_cb(objects.button_task, onButtonClicked, LV_EVENT_CLICKED, NULL);
    }
    
    if (objects.button_pomodoro != nullptr) {
        lv_obj_add_event_cb(objects.button_pomodoro, onButtonClicked, LV_EVENT_CLICKED, NULL);
    }
    
    if (objects.button_bluetooth != nullptr) {
        lv_obj_add_event_cb(objects.button_bluetooth, onButtonClicked, LV_EVENT_CLICKED, NULL);
    }
    
    if (objects.button_lightroom != nullptr) {
        lv_obj_add_event_cb(objects.button_lightroom, onButtonClicked, LV_EVENT_CLICKED, NULL);
    }
    
    if (objects.button_next != nullptr) {
        lv_obj_add_event_cb(objects.button_next, onButtonClicked, LV_EVENT_CLICKED, NULL);
    }
    
    if (objects.button_previous != nullptr) {
        lv_obj_add_event_cb(objects.button_previous, onButtonClicked, LV_EVENT_CLICKED, NULL);
    }
    
    if (objects.button_delete != nullptr) {
        lv_obj_add_event_cb(objects.button_delete, onButtonClicked, LV_EVENT_CLICKED, NULL);
    }
    
    if (objects.button_ripple_delete != nullptr) {
        lv_obj_add_event_cb(objects.button_ripple_delete, onButtonClicked, LV_EVENT_CLICKED, NULL);
    }
    
    if (objects.button_cut != nullptr) {
        lv_obj_add_event_cb(objects.button_cut, onButtonClicked, LV_EVENT_CLICKED, NULL);
    }
    
    Serial.println("[UIHapticHandler] Button haptics setup complete");
}

void UIHapticHandler::onButtonClicked(lv_event_t* e) {
    // Play haptic feedback for any button click
    HapticFeedback::playButtonPress();
}