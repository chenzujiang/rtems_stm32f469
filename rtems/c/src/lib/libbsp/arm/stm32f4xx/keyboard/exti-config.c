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
#include <bsp/irq.h>
#include <bsp/hal_exti.h>
#include <bsp/keyboard.h>

static const key_config key_info[] = {
#ifdef STM32F4XX_ENABLE_EXTI0
  {            /* PA0 */
      .port = (uint32_t)GPIOA,
	  .line = EXTI_Line0,
	  .irq = EXTI0_IRQn,
	  .trig = EXTI_Trigger_Falling,
	  .val = "pa00_EXTI",
	  .proc = key_irq_pa0
  },
#endif
#ifdef STM32F4XX_ENABLE_EXTI13
  {            /* PC13 */
      .port =(uint32_t) GPIOC,
	  .line = EXTI_Line13,
	  .irq = EXTI15_10_IRQn,
	  .trig = EXTI_Trigger_Falling,
	  .val = "pc13_EXTI",
	  .proc = key_irq_pc13
  }
#endif
};
#define KEY_PORT_COUNT \
  (sizeof(key_info) \
    / sizeof(key_info [0]))

unsigned long KEY_Configuration_Count = KEY_PORT_COUNT;

hal_exti_tbl HAL_EXTI_Configuration_Ports = {
      .sDeviceName = "/dev/keyboard",
      .deviceType = HAL_EXTI_CUSTOM,
      .pDeviceFns = &stm32f4xx_exti_fns,
	  .key = key_info,
	  .clearIT = EXTI_ClearITPendingBit,
	  .getStatusIT = EXTI_GetITStatus
};

