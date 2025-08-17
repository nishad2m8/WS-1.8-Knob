#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_bg;
extern const lv_img_dsc_t img_fg;
extern const lv_img_dsc_t img_btn_cut;
extern const lv_img_dsc_t img_btn_delete;
extern const lv_img_dsc_t img_btn_next;
extern const lv_img_dsc_t img_btn_previous;
extern const lv_img_dsc_t img_btn_ripple_delete;
extern const lv_img_dsc_t img_icon_bleplayer;
extern const lv_img_dsc_t img_icon_davinci;
extern const lv_img_dsc_t img_icon_lightroom;
extern const lv_img_dsc_t img_icon_pomodoro;
extern const lv_img_dsc_t img_icon_task;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[12];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/