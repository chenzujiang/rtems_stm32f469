/**
 * @file
 * @ingroup arm_stm34f4
 * @brief Global BSP definitions.
 */

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

/**
 * @defgroup arm_stm32f4 STM32F4 Support
 * @ingroup bsp_arm
 * @brief STM32f4 Support Package
 * @{
 */

#ifndef LIBBSP_ARM_STM32F4_BSP_H
#define LIBBSP_ARM_STM32F4_BSP_H

#include <bspopts.h>
#include <bsp/default-initial-extension.h>

#include <rtems.h>
#include <rtems/console.h>
#include <rtems/clockdrv.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define BSP_FEATURE_IRQ_EXTENSION

#define BSP_ARMV7M_IRQ_PRIORITY_DEFAULT (13 << 4)

#define BSP_ARMV7M_SYSTICK_PRIORITY (14 << 4)

#define BSP_ARMV7M_SYSTICK_FREQUENCY STM32F4_HCLK



/* Ethernet */
struct rtems_bsdnet_ifconfig;

int eth_attach(struct rtems_bsdnet_ifconfig *config, int enable);

#define RTEMS_BSP_NETWORK_DRIVER_ATTACH  eth_attach
#define RTEMS_BSP_NETWORK_DRIVER_NAME    "eth0"



/** @} */

/* Device driver table */
#ifdef CONFIGURE_ENABLE_BSP_DRIVER
#include <bsp/led-drv.h>
#include <rtems/ramdisk.h>
#include <bsp/i2c-drv.h>
#include <bsp/keyboard.h>
//	BSP_LED_DRIVER_HANDLE,
//	RAMDISK_DRIVER_TABLE_ENTRY,
#define CONFIGURE_APPLICATION_EXTRA_DRIVERS \
    	I2C_DEVICE_DRIVER_ENTRY


#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBBSP_ARM_STM32F4_BSP_H */
