#include "screen_manager.h"
#include "screen_main.h"
#include "screen_davinci.h"
#include <Arduino.h>

ScreenManager* ScreenManager::instance = nullptr;

ScreenManager::ScreenManager() : currentScreen(SCREEN_MAIN), davinciScreen(nullptr) {
    Serial.println("[ScreenManager] Constructor called");
}

ScreenManager* ScreenManager::getInstance() {
    if (instance == nullptr) {
        instance = new ScreenManager();
    }
    return instance;
}

void ScreenManager::init() {
    Serial.println("[ScreenManager] Initializing...");
    currentScreen = SCREEN_MAIN;
    davinciScreen = nullptr;
}

void ScreenManager::switchToScreen(ScreenType screen) {
    Serial.print("[ScreenManager] Switching from ");
    Serial.print(currentScreen == SCREEN_MAIN ? "MAIN" : "DAVINCI");
    Serial.print(" to ");
    Serial.println(screen == SCREEN_MAIN ? "MAIN" : "DAVINCI");
    
    switch (screen) {
        case SCREEN_MAIN: {
            if (currentScreen == SCREEN_DAVINCI) {
                // Show main screen without deleting davinci (use false for auto_del)
                Serial.println("[ScreenManager] Switching to main screen");
                lv_scr_load_anim(objects.main, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);
                currentScreen = SCREEN_MAIN;
                
                // Delete davinci screen after switching to free memory
                if (davinciScreen != nullptr) {
                    Serial.println("[ScreenManager] Destroying Davinci screen");
                    lv_timer_t* cleanup_timer = lv_timer_create([](lv_timer_t* timer) {
                        lv_timer_del(timer);
                        if (objects.davinci != nullptr) {
                            delete_screen_davinci();
                        }
                    }, 100, NULL);
                    davinciScreen = nullptr;
                }
                
                // Re-setup main screen gestures after switching back
                Serial.println("[ScreenManager] Re-setting up main screen gestures");
                lv_timer_t* timer = lv_timer_create([](lv_timer_t* timer) {
                    lv_timer_del(timer);
                    ScreenMain::setupGestures();
                }, 200, NULL);
            }
            break;
        }
            
        case SCREEN_DAVINCI: {
            if (currentScreen == SCREEN_MAIN) {
                // Reset launcher to default position before switching
                if (objects.conainer_launcer != nullptr) {
                    Serial.println("[ScreenManager] Resetting launcher position to default");
                    lv_obj_set_y(objects.conainer_launcer, 300);
                    ScreenMain::resetState();  // Use public method to reset internal state
                    
                    // Also reset brightness arc state
                    if (objects.main_arc_brightness != nullptr) {
                        lv_obj_clear_state(objects.main_arc_brightness, LV_STATE_CHECKED);
                    }
                }
                
                Serial.println("[ScreenManager] Creating Davinci screen");
                createDavinciScreen();
                
                // Load davinci screen without deleting main screen
                if (davinciScreen != nullptr) {
                    Serial.println("[ScreenManager] Showing Davinci screen");
                    lv_scr_load_anim(davinciScreen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);
                    currentScreen = SCREEN_DAVINCI;
                }
            }
            break;
        }
    }
}

ScreenType ScreenManager::getCurrentScreen() {
    return currentScreen;
}

void ScreenManager::createDavinciScreen() {
    if (davinciScreen == nullptr) {
        Serial.println("[ScreenManager] Creating davinci screen object");
        create_screen_davinci();
        davinciScreen = objects.davinci;
        Serial.println("[ScreenManager] Setting up davinci gestures");
        ScreenDavinci::setupGestures();
    } else {
        Serial.println("[ScreenManager] Davinci screen already exists");
    }
}

void ScreenManager::destroyDavinciScreen() {
    if (davinciScreen != nullptr) {
        Serial.println("[ScreenManager] Deleting davinci screen object");
        delete_screen_davinci();
        davinciScreen = nullptr;
    } else {
        Serial.println("[ScreenManager] Davinci screen already null");
    }
}