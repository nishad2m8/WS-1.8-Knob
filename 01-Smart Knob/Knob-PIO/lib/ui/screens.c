#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 360, 360);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // Image BG
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.image_bg = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_bg);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 0, 104);
            lv_obj_set_size(obj, 360, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_bre_150, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffd1db), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "10:10");
        }
        {
            // Image FG
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.image_fg = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_fg);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 79, 61);
            lv_obj_set_size(obj, 93, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_bre_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "T-25°");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 178, 61);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_bre_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffab6a71), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "|");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 188, 61);
            lv_obj_set_size(obj, 97, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_bre_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "H-55%");
        }
        {
            // arc temp
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.arc_temp = obj;
            lv_obj_set_pos(obj, 5, 5);
            lv_obj_set_size(obj, 350, 350);
            lv_arc_set_range(obj, 0, 50);
            lv_arc_set_value(obj, 30);
            lv_arc_set_bg_start_angle(obj, 210);
            lv_arc_set_bg_end_angle(obj, 250);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffbc8689), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffe9dede), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // arc hum
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.arc_hum = obj;
            lv_obj_set_pos(obj, 5, 5);
            lv_obj_set_size(obj, 350, 350);
            lv_arc_set_value(obj, 55);
            lv_arc_set_bg_start_angle(obj, 290);
            lv_arc_set_bg_end_angle(obj, 330);
            lv_arc_set_mode(obj, LV_ARC_MODE_REVERSE);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffbc8689), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffe9dede), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // arc battery
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.arc_battery = obj;
            lv_obj_set_pos(obj, 5, 5);
            lv_obj_set_size(obj, 350, 350);
            lv_arc_set_range(obj, 0, 50);
            lv_arc_set_value(obj, 30);
            lv_arc_set_bg_start_angle(obj, 255);
            lv_arc_set_bg_end_angle(obj, 285);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffbc8689), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xffe6ffaa), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // Conainer Launcer
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.conainer_launcer = obj;
            lv_obj_set_pos(obj, 0, 300);
            lv_obj_set_size(obj, 330, 330);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_radius(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW_WRAP, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_row(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_column(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_cross_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_track_place(obj, LV_FLEX_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 180, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // main arc brightness
                    lv_obj_t *obj = lv_arc_create(parent_obj);
                    objects.main_arc_brightness = obj;
                    lv_obj_set_pos(obj, -20, -20);
                    lv_obj_set_size(obj, 320, 320);
                    lv_arc_set_range(obj, 10, 100);
                    lv_arc_set_value(obj, 50);
                    lv_arc_set_bg_start_angle(obj, 91);
                    lv_arc_set_bg_end_angle(obj, 90);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_IGNORE_LAYOUT|LV_OBJ_FLAG_CHECKABLE);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_arc_width(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_width(obj, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(0xffffcc75), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_opa(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_arc_color(obj, lv_color_hex(0xffd079d3), LV_PART_INDICATOR | LV_STATE_CHECKED);
                    lv_obj_set_style_arc_opa(obj, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                }
                {
                    // Button Task
                    lv_obj_t *obj = lv_imgbtn_create(parent_obj);
                    objects.button_task = obj;
                    lv_obj_set_pos(obj, 156, 149);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, 64);
                    lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_icon_task, NULL);
                    lv_obj_set_style_opa(obj, 200, LV_PART_MAIN | LV_STATE_PRESSED);
                }
                {
                    // Button Pomodoro
                    lv_obj_t *obj = lv_imgbtn_create(parent_obj);
                    objects.button_pomodoro = obj;
                    lv_obj_set_pos(obj, 156, 149);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, 64);
                    lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_icon_pomodoro, NULL);
                    lv_obj_set_style_opa(obj, 200, LV_PART_MAIN | LV_STATE_PRESSED);
                }
                {
                    // Button bluetooth
                    lv_obj_t *obj = lv_imgbtn_create(parent_obj);
                    objects.button_bluetooth = obj;
                    lv_obj_set_pos(obj, 156, 149);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, 64);
                    lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_icon_bleplayer, NULL);
                    lv_obj_set_style_opa(obj, 200, LV_PART_MAIN | LV_STATE_PRESSED);
                }
                {
                    // Button Davinci
                    lv_obj_t *obj = lv_imgbtn_create(parent_obj);
                    objects.button_davinci = obj;
                    lv_obj_set_pos(obj, 156, 149);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, 64);
                    lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_icon_davinci, NULL);
                    lv_obj_set_style_opa(obj, 200, LV_PART_MAIN | LV_STATE_PRESSED);
                }
                {
                    // Button Lightroom
                    lv_obj_t *obj = lv_imgbtn_create(parent_obj);
                    objects.button_lightroom = obj;
                    lv_obj_set_pos(obj, 156, 149);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, 64);
                    lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_icon_lightroom, NULL);
                    lv_obj_set_style_opa(obj, 200, LV_PART_MAIN | LV_STATE_PRESSED);
                }
            }
        }
    }
    
    tick_screen_main();
}

void delete_screen_main() {
    lv_obj_del(objects.main);
    objects.main = 0;
    objects.image_bg = 0;
    objects.obj0 = 0;
    objects.image_fg = 0;
    objects.obj1 = 0;
    objects.arc_temp = 0;
    objects.arc_hum = 0;
    objects.arc_battery = 0;
    objects.conainer_launcer = 0;
    objects.main_arc_brightness = 0;
    objects.button_task = 0;
    objects.button_pomodoro = 0;
    objects.button_bluetooth = 0;
    objects.button_davinci = 0;
    objects.button_lightroom = 0;
}

void tick_screen_main() {
}

void create_screen_davinci() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.davinci = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 360, 360);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // button next
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.button_next = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn_next, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_PRESSED, NULL, &img_btn_next, NULL);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_clip_corner(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 100, LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_clip_corner(obj, true, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // button previous
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.button_previous = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn_previous, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_PRESSED, NULL, &img_btn_previous, NULL);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_clip_corner(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 100, LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_clip_corner(obj, true, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // button delete
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.button_delete = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn_delete, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_PRESSED, NULL, &img_btn_delete, NULL);
            lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_clip_corner(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 100, LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_clip_corner(obj, true, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // button ripple delete
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.button_ripple_delete = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn_ripple_delete, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_PRESSED, NULL, &img_btn_ripple_delete, NULL);
            lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_clip_corner(obj, true, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 100, LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_clip_corner(obj, true, LV_PART_MAIN | LV_STATE_PRESSED);
        }
        {
            // button cut
            lv_obj_t *obj = lv_imgbtn_create(parent_obj);
            objects.button_cut = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_btn_cut, NULL);
            lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_PRESSED, NULL, &img_btn_cut, NULL);
            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 100, LV_PART_MAIN | LV_STATE_PRESSED);
            lv_obj_set_style_clip_corner(obj, true, LV_PART_MAIN | LV_STATE_PRESSED);
        }
    }
    
    tick_screen_davinci();
}

void delete_screen_davinci() {
    lv_obj_del(objects.davinci);
    objects.davinci = 0;
    objects.button_next = 0;
    objects.button_previous = 0;
    objects.button_delete = 0;
    objects.button_ripple_delete = 0;
    objects.button_cut = 0;
}

void tick_screen_davinci() {
}



typedef void (*create_screen_func_t)();
create_screen_func_t create_screen_funcs[] = {
    create_screen_main,
    create_screen_davinci,
};
void create_screen(int screen_index) {
    create_screen_funcs[screen_index]();
}
void create_screen_by_id(enum ScreensEnum screenId) {
    create_screen_funcs[screenId - 1]();
}

typedef void (*delete_screen_func_t)();
delete_screen_func_t delete_screen_funcs[] = {
    delete_screen_main,
    delete_screen_davinci,
};
void delete_screen(int screen_index) {
    delete_screen_funcs[screen_index]();
}
void delete_screen_by_id(enum ScreensEnum screenId) {
    delete_screen_funcs[screenId - 1]();
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_davinci,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
}
