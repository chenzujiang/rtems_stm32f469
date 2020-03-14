#ifndef __BSP_FT6206_H
#define __BSP_FT6206_H

#include <bsp/library/stm32f4xx.h>
#include "BSP_I2C.h"
extern uint16_t touch_x;
extern uint16_t touch_y;
extern uint16_t touch_w;
extern uint8_t is_touch;
/* FT6206 Chip identification register */
#define FT6206_CHIP_ID_REG 0xA8

/*  Possible values of FT6206_CHIP_ID_REG */
#define FT6206_ID_VALUE    0x11

/* Interrupt mode register (used when in interrupt mode) */
#define FT6206_GMODE_REG  0xA4

/* Touch Data Status register : gives number of active touch points (0..2) */
#define FT6206_TD_STAT_REG 0x02

#define FT6206_MSB_MASK                 0x0F
#define FT6206_MSB_SHIFT                0

  /* Values Pn_XL and Pn_YL related */
#define FT6206_LSB_MASK                 0xFF
#define FT6206_LSB_SHIFT                0
//��һ��������ļĴ���
#define FT6206_P1_XH_REG 0x03
#define FT6206_P1_XL_REG 0x04
#define FT6206_P1_YH_REG 0x05
#define FT6206_P1_YL_REG 0x06

#define FT6206_P1_WEIGHT_REG 0x07
#define FT6206_P1_MISC_REG 0x08
//�ڶ���������ļĴ���
#define FT6206_P2_XH_REG 0x09
#define FT6206_P2_XL_REG 0x0A
#define FT6206_P2_YH_REG 0x0B
#define FT6206_P2_YL_REG 0x0C

#define FT6206_P2_WEIGHT_REG 0x0D
#define FT6206_P2_MISC_REG 0x0E

int BSP_FT6206_Init(void);
int BSP_FT6206_ReadID(void);
int BSP_FT6205_Detect(void);
int BSP_FT6205_GetXY(uint16_t *pTouchX,uint16_t *pTouchY);
void FT6206_INT_conf(void);
void Goodix_TS_Work_Func(void);
#endif
