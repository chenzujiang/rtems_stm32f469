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
#include <bsp.h>
#include <bsp/io.h>
#include <bsp/irq.h>
#include <bsp/hal_exti.h>
#include <bsp/keyboard.h>
#include <stdio.h>

__attribute__ ((weak)) void NVIC_EXTI_Configuration(uint32_t EXTI_Linex)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  switch(EXTI_Linex)
  {
  case EXTI_Line0:
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
	  break;
  case EXTI_Line13:
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
	  break;
  default:
	  break;
  }
}
/**
 * Default config, could override by user.
 */
__attribute__ ((weak)) void exti_gpio_initialize (uint32_t EXTI_Linex)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  switch(EXTI_Linex)
  {
  case EXTI_Line0:
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
    break;
  case EXTI_Line13:
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);
    break;
  default:
    break;
    }
}

static void exti_initialize(int count)
{
  const hal_exti_tbl *ct = &HAL_EXTI_Configuration_Ports;

  EXTI_InitTypeDef EXTI_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  NVIC_EXTI_Configuration(ct->key[count].line);
  /* Configure EXTI GPIO */
  exti_gpio_initialize(ct->key[count].line);

  switch(ct->key[count].line)
  {
  case EXTI_Line0:
		/* link interrupt to key1 port*/
	  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);
    break;
  case EXTI_Line13:
		/* link interrupt to key2 port*/
	  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource13);
    break;
  default:
    break;
  }
 // EXTI_DeInit();we can call stm32f4 init exti
  EXTI_InitStructure.EXTI_Line = ct->key[count].line;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

static int exti_first_open(int minor)
{
  return 0;
}

static int exti_last_close(int minor)
{
  return 0;
}

static int exti_read_byte(int minor,
						  uint32_t port,
					      uint32_t line,
						  uint8_t *s)
{
	return 0;
}

static int exti_write_byte(int minor,
						  uint32_t port,
					      uint32_t line,
						  uint8_t *s)
{
	return 0;
}

const hal_exti_fns stm32f4xx_exti_fns = {
  .deviceFirstOpen = exti_first_open,
  .deviceLastClose = exti_last_close,
  .deviceRead = exti_read_byte,
  .deviceWrite = exti_write_byte,
  .deviceInitialize = exti_initialize,
};
