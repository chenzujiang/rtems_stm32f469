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
#include <bsp/hal_spi.h>
#include <bsp/spi.h>
#include <stdio.h>
#include <bsp/bsp_spi_flash.h>
__attribute__ ((weak)) void NVIC_SPI_Configuration(uint32_t SPIx)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  switch(SPIx)
  {
  case SPI1_BASE:
	  break;
  case SPI5_BASE:
	  NVIC_InitStructure.NVIC_IRQChannel = SPI5_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
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
__attribute__ ((weak)) void spi_gpio_initialize (uint32_t SPIx)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  switch(SPIx)
  {
  case SPI1_BASE:
	  break;
  case SPI5_BASE:
	  /*!< SPI_FLASH_SPI_CS_GPIO, SPI_FLASH_SPI_MOSI_GPIO,
	       SPI_FLASH_SPI_MISO_GPIO,SPI_FLASH_SPI_SCK_GPIO Ê±ÖÓÊ¹ÄÜ */
	  RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOF, ENABLE);
	  GPIO_PinAFConfig(GPIOF,GPIO_PinSource7,GPIO_AF_SPI5);
	  GPIO_PinAFConfig(GPIOF,GPIO_PinSource8,GPIO_AF_SPI5);
	  GPIO_PinAFConfig(GPIOF,GPIO_PinSource9,GPIO_AF_SPI5);
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; /*! SPI_FLASH_SPI : SCK */
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_Init(GPIOF, &GPIO_InitStructure);
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;/* MISO */
	  GPIO_Init(GPIOF, &GPIO_InitStructure);
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;/* MOSI */
	  GPIO_Init(GPIOF, &GPIO_InitStructure);
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;/* CS */
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	  GPIO_Init(GPIOF, &GPIO_InitStructure);
	  /* stop signal FLASH CS high*/
	  SPI_FLASH_CS_HIGH();
    break;
  default:
    break;
    }
}

static void spi_initialize(int minor)
{

  const hal_spi_tbl *ct = &HAL_SPI_Configuration_Ports[minor];

  SPI_InitTypeDef SPI_InitStructure;

  NVIC_SPI_Configuration(ct->ulCtrlPort1);
  /* Configure SPI GPIO */
  spi_gpio_initialize(ct->ulCtrlPort1);

  switch(ct->ulCtrlPort1)
  {
  case SPI1_BASE:
	  break;
  case SPI5_BASE:
	  /*!< SPI_FLASH_SPI clock enable */
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI5, ENABLE);
    break;
  default:
    break;
  }
  //spi_falsh mode 0 and mode 3
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init((SPI_TypeDef*)ct->ulCtrlPort1, &SPI_InitStructure);

  SPI_Cmd((SPI_TypeDef*)ct->ulCtrlPort1, ENABLE);
  SPI_Flash_WAKEUP();
  SPI_FLASH_Init();
}

static int spi_first_open(int minor)
{
  return 0;
}

static int spi_last_close(int minor)
{
  return 0;
}

static int spi_read_byte(int minor,
	      uint32_t read_addr,
		  uint8_t* arr,
		  uint32_t byte)
{
	SPI_FLASH_BufferRead(arr, read_addr, byte);
	return 0;
}

static int spi_write_byte(int minor,
					      uint32_t write_addr,
						  uint8_t* arr,
						  uint32_t byte)
{
   uint32_t flashid =0;
   flashid =SPI_FLASH_ReadID();
	SPI_FLASH_SectorErase(write_addr);
	SPI_FLASH_BufferWrite(arr, write_addr, byte);
	uint8_t readbuf1[256]={0};
	SPI_FLASH_BufferRead(readbuf1, write_addr, byte);
	printk("\r\n flashid22222 %d---%s\r\n",flashid,readbuf1);
	return 0;
}

const hal_spi_fns stm32f4xx_spi_fns = {
  .deviceFirstOpen = spi_first_open,
  .deviceLastClose = spi_last_close,
  .deviceRead = spi_read_byte,
  .deviceWrite = spi_write_byte,
  .deviceInitialize = spi_initialize,
};
