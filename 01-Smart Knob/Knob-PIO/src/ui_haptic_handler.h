#ifndef UI_HAPTIC_HANDLER_H
#define UI_HAPTIC_HANDLER_H

#include <lvgl.h>

class UIHapticHandler {
public:
    static void init();
    static void setupButtonHaptics();
    
private:
    static void onButtonClicked(lv_event_t* e);
};

#endif