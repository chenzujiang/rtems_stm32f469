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
#include <libchip/gpio_led_supp.h>
#include <bsp.h>
#include <bsp/io.h>
#include <bsp/irq.h>
#include <libchip/gpio_led.h>
#include <rtems/led-drv.h>
#include <libchip/gpio_led.h>
/**
 * Default config, could override by user.
 */
__attribute__ ((weak)) void led_gpio_init (uint32_t gpio)
{
  /* Private typedef -----------------------------------------------------------*/
  GPIO_InitTypeDef  GPIO_InitStructure;
  switch(gpio)
  {
  case GPIOG_BASE:
    /* GPIOG Peripheral clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
    /* Configure PG6 and PG8 in output pushpull mode */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
    break;
  case GPIOD_BASE:
    /* GPIOG Peripheral clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    /* Configure PG6 and PG8 in output pushpull mode */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    break;
  case GPIOK_BASE:
    /* GPIOG Peripheral clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOK, ENABLE);
    /* Configure PG6 and PG8 in output pushpull mode */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOK, &GPIO_InitStructure);
    break;
  }
}
static void led_initialize(int minor)
{
  const gpio_tbl *ct = gpio_Port_Tbl [minor];
  /* Configure GPIO */
  led_gpio_init(ct->ulCtrlPort1);
}
static int led_get_status(int minor,uint32_t* cmmand,void* buffer)
{

	return 0;
}
static int led_set_status(int minor,uint32_t command,void* buffer)
{
	//printk("set led %d,buffer data %s\r\n",command,buffer);
	if(command == LED_DEVICE_OPEN)
		GPIO_WriteBit((GPIO_TypeDef*)GPIO_Configuration_Ports[minor].ulCtrlPort1, GPIO_Configuration_Ports[minor].ulCtrlPort2,Bit_RESET);
	else if(command == LED_DEVICE_CLOSE)
		GPIO_WriteBit((GPIO_TypeDef*)GPIO_Configuration_Ports[minor].ulCtrlPort1, GPIO_Configuration_Ports[minor].ulCtrlPort2,Bit_SET);
	return 0;
}
const gpio_fns stm32f4xx_gpio_fns = {
  .deviceProbe = libchip_gpio_led_probe,
  .deviceInitialize = led_initialize,
  .deviceGetgpioStatus = led_get_status,
  .deviceSetgpioStatus = led_set_status,
};
