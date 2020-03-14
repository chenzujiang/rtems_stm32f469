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
#include <bsp/spi.h>
#include <bsp/hal_spi.h>

hal_spi_tbl HAL_SPI_Configuration_Ports [] = {
  #ifdef STM32F4XX_ENABLE_SPI1
    {
      .sDeviceName = "/dev/spi1",
	  .pDeviceFns = &stm32f4xx_spi_fns,
      .ulCtrlPort1 = (uint32_t) SPI1_BASE,
	  .device_id = 0XEF4018,//spi slave addr
	  .page_size =0,//no size
	  .Per_WR_PageSize=0,//no
	  .irq=SPI1_IRQn,
	  .proc=spi_isr,
	  .write_addr=0,
      .read_addr=0
    },
  #endif
  #ifdef STM32F4XX_ENABLE_SPI2
    {
      .sDeviceName = "/dev/spi2",
	  .pDeviceFns = &stm32f4xx_spi_fns,
      .ulCtrlPort1 = (uint32_t) SPI2_BASE,
	  .device_id = 0XEF4018,//spi slave addr
	  .page_size =0,//no size
	  .Per_WR_PageSize=0,//no
	  .irq=SPI2_IRQn,
	  .proc=spi_isr,
	  .write_addr=0,
      .read_addr=0
    },
  #endif
#ifdef STM32F4XX_ENABLE_SPI5
  {
	  .sDeviceName = "/dev/spi5",
	  .pDeviceFns = &stm32f4xx_spi_fns,
	  .ulCtrlPort1 = (uint32_t) SPI5_BASE,
	  .device_id = 0XEF4018,//spi slave addr
	  .page_size =256,//no size
	  .Per_WR_PageSize=256,//no
	  .irq=SPI5_IRQn,
	  .proc=spi_isr,
	  .write_addr=0,
      .read_addr=0
  }
#endif
};

#define SPI_PORT_COUNT \
  (sizeof(HAL_SPI_Configuration_Ports) \
    / sizeof(HAL_SPI_Configuration_Ports [0]))

unsigned long SPI_Configuration_Count = SPI_PORT_COUNT;
