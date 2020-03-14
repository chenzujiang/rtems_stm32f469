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

#ifndef LIBBSP_ARM_STM32F4XX_BSP_H
#define LIBBSP_ARM_STM32F4XX_BSP_H

#include <bspopts.h>
#include <bsp/default-initial-extension.h>

#include <rtems.h>
#include <rtems/console.h>
#include <rtems/clockdrv.h>
#include <bsp/keyboard.h>
#include <bsp/spi.h>
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define BSP_FEATURE_IRQ_EXTENSION
/**
 * Default PRIGROUP = [7:1], and STM32 implement highest 4bits
 */
#define BSP_ARMV7M_IRQ_PRIORITY_DEFAULT (14 << 4)

#define BSP_ARMV7M_SYSTICK_PRIORITY (15 << 4)

extern uint32_t SystemCoreClock;
#define BSP_ARMV7M_SYSTICK_FREQUENCY SystemCoreClock

#define CONFIGURE_APPLICATION_EXTRA_DRIVERS_ENTRY \
		KEYBOARD_DRIVER_TABLE_ENTRY

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBBSP_ARM_STM32F4XX_BSP_H */
