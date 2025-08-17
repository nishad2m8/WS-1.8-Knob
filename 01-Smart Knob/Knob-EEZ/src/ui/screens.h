#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *davinci;
    lv_obj_t *image_bg;
    lv_obj_t *label_time;
    lv_obj_t *image_fg;
    lv_obj_t *arc_temp;
    lv_obj_t *arc_hum;
    lv_obj_t *arc_battery;
    lv_obj_t *obj0;
    lv_obj_t *conainer_launcer;
    lv_obj_t *main_arc_brightness;
    lv_obj_t *button_task;
    lv_obj_t *button_pomodoro;
    lv_obj_t *button_bluetooth;
    lv_obj_t *button_davinci;
    lv_obj_t *button_lightroom;
    lv_obj_t *button_next;
    lv_obj_t *button_previous;
    lv_obj_t *button_delete;
    lv_obj_t *button_ripple_delete;
    lv_obj_t *button_cut;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_DAVINCI = 2,
};

void create_screen_main();
void delete_screen_main();
void tick_screen_main();

void create_screen_davinci();
void delete_screen_davinci();
void tick_screen_davinci();

void create_screen_by_id(enum ScreensEnum screenId);
void delete_screen_by_id(enum ScreensEnum screenId);
void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/