#ifndef __LV_TOUCHPAD_H
#define __LV_TOUCHPAD_H

#include "../lvgl-5.1/lvgl.h"
#include "../lv_conf.h"

void lv_touchpad_init(void);
bool lv_touchpad_read(lv_indev_data_t *data);

#endif


