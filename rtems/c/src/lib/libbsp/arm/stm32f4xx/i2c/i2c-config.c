/*
 * Copyright (c) 2013 Christian Mauderer.  All rights reserved.
 *
 *  embedded brains GmbH
 *  Obere Lagerstr. 30
 *  82178 Puchheim
 *  Germany
 *  <rtems@embedded-brains.de>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */
#include <bsp/library/stm32f4xx.h>
#include <rtems/bspIo.h>
#include <bspopts.h>
#include <libchip/hal_i2c.h>
#include <bsp/irq.h>
//export hal_i2c_fns
#include <bsp/i2c.h>
hal_i2c_tbl HAL_I2C_Configuration_Ports [] = {
  #ifdef STM32F4XX_ENABLE_I2C1
    {
      .sDeviceName = "/dev/i2c1",
      .deviceType = HAL_I2C_CUSTOM,
      .pDeviceFns = &stm32f4xx_i2c_fns,
      .ulCtrlPort1 = (uint32_t) I2C1_BASE,
      .ulCtrlPort2 = 0,
	  .addr = 0xA0,//i2c slave addr
      .ulClock = 400000
    },
  #endif
  #ifdef STM32F4XX_ENABLE_I2C2
    {
      .sDeviceName = "/dev/i2c2",
      .deviceType = HAL_I2C_CUSTOM,
      .pDeviceFns = &stm32f4xx_i2c_fns,
      .ulCtrlPort1 = (uint32_t) I2C2_BASE,
      .ulCtrlPort2 = 1,
	  .addr = 0x0B,
      .ulClock = 400000
    },
  #endif
#ifdef STM32F4XX_ENABLE_I2C3
  {
    .sDeviceName = "/dev/i2c3",
    .deviceType = HAL_I2C_CUSTOM,
    .pDeviceFns = &stm32f4xx_i2c_fns,
    .ulCtrlPort1 = (uint32_t) I2C3_BASE,
    .ulCtrlPort2 = 1,
	.addr = 0x0C,
    .ulClock = 400000
  }
#endif
};

#define I2C_PORT_COUNT \
  (sizeof(HAL_I2C_Configuration_Ports) \
    / sizeof(HAL_I2C_Configuration_Ports [0]))

unsigned long HAL_I2C_Configuration_Count = I2C_PORT_COUNT;
