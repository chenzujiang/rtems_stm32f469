#ifndef __LV_TFT_H
#define __LV_TFT_H

#include "../lvgl-5.1/lvgl.h"
#include "../lv_conf.h"

void lv_tft_init(void);
void lv_tft_flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p);
void lv_tft_fill(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t color);
void lv_tft_map(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p);

#if USE_LV_GPU != 0
static void gpu_mem_blend(lv_color_t * dest, const lv_color_t * src, uint32_t length, lv_opa_t opa);
static void gpu_mem_fill(lv_color_t * dest, uint32_t length, lv_color_t color);
#endif

#endif

