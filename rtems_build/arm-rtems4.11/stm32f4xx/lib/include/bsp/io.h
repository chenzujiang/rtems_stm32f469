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

#ifndef LIBBSP_ARM_STM32F4XX_IO_H
#define LIBBSP_ARM_STM32F4XX_IO_H

#include <stdbool.h>
#include <stdint.h>
#include <bspopts.h>
//#include <bsp/library/stm32f4xx.h>
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Default config, could override by user if unmatch.
 */
void uart_gpio_initialize (uint32_t uart);
void led_gpio_init (uint32_t gpio);
void i2c_gpio_initialize (uint32_t I2Cx);
void exti_gpio_initialize (uint32_t EXTI_Linex);
void NVIC_EXTI_Configuration(uint32_t EXTI_Linex);
void spi_gpio_initialize (uint32_t SPIx);
void NVIC_SPI_Configuration(uint32_t SPIx);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBBSP_ARM_STM32F4XX_IO_H */
