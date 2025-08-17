#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "ui.h"

enum ScreenType {
    SCREEN_MAIN = 0,
    SCREEN_DAVINCI = 1
};

class ScreenManager {
private:
    static ScreenManager* instance;
    ScreenType currentScreen;
    lv_obj_t* davinciScreen;
    
public:
    static ScreenManager* getInstance();
    
    void init();
    void switchToScreen(ScreenType screen);
    ScreenType getCurrentScreen();
    
private:
    ScreenManager();
    void createDavinciScreen();
    void destroyDavinciScreen();
};

#endif