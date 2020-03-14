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
//???hal_i2c_sersupp.h
#include <libchip/hal_i2c_supp.h>
#include <bsp.h>
#include <bsp/io.h>
#include <bsp/irq.h>
#include <bsp/i2c.h>
#include <libchip/hal_i2c.h>
#include <bsp/bsp_i2c_ee.h>
#include <stdio.h>
/**
 * Default config, could override by user.
 */
__attribute__ ((weak)) void i2c_gpio_initialize (uint32_t I2Cx)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  switch(I2Cx)
  {
  case I2C1_BASE:
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	  /*!< GPIO configuration */
	  /* Connect PXx to I2C_SCL*/
	  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
	  /* Connect PXx to I2C_SDA*/
	  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);

	  /*!< Configure EEPROM_I2C pins: SCL */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);
	  /*!< Configure EEPROM_I2C pins: SDA */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);
    break;
  case I2C2_BASE:
    break;
    }
}

static void i2c_initialize(int minor)
{
  const hal_i2c_tbl *ct = hal_i2c_Port_Tbl [minor];
  I2C_InitTypeDef  I2C_InitStructure;
  /* Configure I2C GPIO */
  i2c_gpio_initialize(ct->ulCtrlPort1);
  /* Enable i2c Clock */
  switch(ct->ulCtrlPort1)
  {
  case I2C1_BASE:
	  /*!< EEPROM_I2C Periph clock enable */
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    break;
  case I2C2_BASE:
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    break;
  case I2C3_BASE:
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C3, ENABLE);
    break;
  default:
    break;
  }

  I2C_DeInit((I2C_TypeDef *)ct->ulCtrlPort1);

  /* I2C conf */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;		                    /* ¸ßµçÆ½Êý¾ÝÎÈ¶¨£¬µÍµçÆ½Êý¾Ý±ä»¯ SCL Ê±ÖÓÏßµÄÕ¼¿Õ±È */
  I2C_InitStructure.I2C_OwnAddress1 = 0x55;//stm32 i2c addr
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;	/* I2CµÄÑ°Ö·Ä£Ê½ */
  I2C_InitStructure.I2C_ClockSpeed = ct->ulClock;	                            /* Í¨ÐÅËÙÂÊ */
  I2C_Init((I2C_TypeDef*)ct->ulCtrlPort1, &I2C_InitStructure);	                                      /* I2C1 ³õÊ¼»¯ */
  I2C_Cmd((I2C_TypeDef*)ct->ulCtrlPort1, ENABLE);  	                                                /* Ê¹ÄÜ I2C1 */

  I2C_AcknowledgeConfig((I2C_TypeDef*)ct->ulCtrlPort1, ENABLE);
}

static int i2c_first_open(int minor)
{
  return 0;
}

static int i2c_last_close(int minor)
{
  return 0;
}

static int i2c_read_polled(int minor,
						  uint16_t slave_addr,
					      uint16_t regaddr,
						   uint8_t *s,
						   uint16_t n)
{
	int status = I2C_EE_BufferRead(s,regaddr,n);
	printf("s = %s",s);
	if(1 == status)
	{
		return n;
	}
	else{

	}
  return 0;
}

static ssize_t i2c_write_support_polled(
  int minor,
  uint16_t slave_addr,
  uint16_t regaddr,
  uint8_t *s,
  uint16_t n
)
{
	int status = I2C_EE_BufferWrite(s,regaddr,n);
	if(0 == status)
	{
		return n;
	}
	else{
		return 0;
	}
}
//stm32f4 have 3 i2c interface
static int i2c_read_byte(int minor,
						  uint16_t slave_addr,
					      uint16_t regaddr,
						  uint8_t *s)
{
	return 0;
}

static int i2c_write_byte(int minor,
							uint16_t slave_addr,
					      uint16_t regaddr,
						  uint8_t *s)
{
	return 0;
}

const hal_i2c_fns stm32f4xx_i2c_fns = {
  .deviceProbe = libchip_hal_i2c_probe,
  .deviceFirstOpen = i2c_first_open,
  .deviceLastClose = i2c_last_close,
  .deviceRead = i2c_read_byte,
  .deviceRead = i2c_write_byte,
  .deviceMoreRead = i2c_read_polled,
  .deviceMoreWrite = i2c_write_support_polled,
  .deviceInitialize = i2c_initialize,
};
