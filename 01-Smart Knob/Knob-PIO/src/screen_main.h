#ifndef SCREEN_MAIN_H
#define SCREEN_MAIN_H

#include "ui.h"

class ScreenMain {
public:
    static void setupGestures();
    static void resetState();
    static void onDavinciButtonPressed(lv_event_t* e);
    
private:
    static void onSwipeUp(lv_event_t* e);
    static void setLauncherPosition(int16_t y, bool animate = true);
    static bool launcherExpanded;
};

#endif