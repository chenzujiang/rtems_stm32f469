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

#include <rtems/bspIo.h>
#include <bsp.h>
//#include <bsp/io.h>
#include <bsp/irq.h>
#include <bsp/bootcard.h>
#include <bsp/irq-generic.h>
#include <bsp/stm32f4.h>


void bsp_start(void)
{
  //stm32f4_gpio_set_config_array(&stm32f4_start_config_gpio [0]);
  stm32f4_rcc_config_mco(STM32F4_RCC_CFGR_MCO1, 0);
  stm32f4_syscfg_mii_sel(STM32F4_SYSCFG_MII_ENABLE);

  bsp_interrupt_initialize();
  printk("Board initialize successful.\n\r"); 
}
