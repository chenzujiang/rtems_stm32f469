/*
 * Copyright (c) 2012 Sebastian Huber.  All rights reserved.
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
#include <libchip/gpio_led.h>
#include <bspopts.h>
#include <bsp/irq.h>
//export gpio_fns
#include <bsp/gpio.h>

gpio_tbl GPIO_Configuration_Ports [] = {
  #ifdef STM32F4XX_ENABLE_LED_1
    {
      .sDeviceName = "/dev/led1",
      .deviceType = GPIO_CUSTOM,
      .pDeviceFns = &stm32f4xx_gpio_fns,
      .ulCtrlPort1 = (uint32_t) GPIOG_BASE,
      .ulCtrlPort2 = GPIO_Pin_6,
      .ulClock = GPIO_Speed_100MHz
    },
  #endif
  #ifdef STM32F4XX_ENABLE_LED_2
    {
      .sDeviceName = "/dev/led2",
      .deviceType = GPIO_CUSTOM,
      .pDeviceFns = &stm32f4xx_gpio_fns,
      .ulCtrlPort1 = (uint32_t) GPIOD_BASE,
      .ulCtrlPort2 = GPIO_Pin_4,
      .ulClock = GPIO_Speed_100MHz
    },
  #endif
  #ifdef STM32F4XX_ENABLE_LED_3
    {
      .sDeviceName = "/dev/led3",
      .deviceType = GPIO_CUSTOM,
      .pDeviceFns = &stm32f4xx_gpio_fns,
      .ulCtrlPort1 = (uint32_t) GPIOD_BASE,
      .ulCtrlPort2 = GPIO_Pin_5,
      .ulClock = GPIO_Speed_100MHz
    },
  #endif
  #ifdef STM32F4XX_ENABLE_LED_4
  {
    .sDeviceName = "/dev/led4",
    .deviceType = GPIO_CUSTOM,
    .pDeviceFns = &stm32f4xx_gpio_fns,
    .ulCtrlPort1 = (uint32_t) GPIOK_BASE,
    .ulCtrlPort2 = GPIO_Pin_3,
    .ulClock = GPIO_Speed_100MHz
  }
  #endif
};

#define GPIO_PORT_COUNT \
  (sizeof(GPIO_Configuration_Ports) \
    / sizeof(GPIO_Configuration_Ports [0]))

unsigned long GPIO_Configuration_Count = GPIO_PORT_COUNT;


