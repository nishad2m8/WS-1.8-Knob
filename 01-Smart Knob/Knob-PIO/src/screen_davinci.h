#ifndef SCREEN_DAVINCI_H
#define SCREEN_DAVINCI_H

#include "ui.h"

class ScreenDavinci {
public:
    static void setupGestures();
    
private:
    static void setupButtonHandlers();
    static void sendKeyPress(uint8_t modifier, uint8_t key);
    static void onSwipeLeft(lv_event_t* e);
    
    // Button event handlers
    static void onButtonCut(lv_event_t* e);
    static void onButtonDelete(lv_event_t* e);
    static void onButtonRippleDelete(lv_event_t* e);
    static void onButtonNext(lv_event_t* e);
    static void onButtonPrevious(lv_event_t* e);
};

#endif