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
#include <libchip/sersupp.h>
#include <bsp.h>
#include <bsp/io.h>
#include <bsp/irq.h>
#include <bsp/uart.h>

/**
 * Default config, could override by user.
 */
__attribute__ ((weak)) void uart_gpio_initialize (uint32_t uart)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  switch(uart)
  {
  case USART1_BASE:/* PA9 - TX, PA10 - RX */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    break;

  case USART2_BASE:/* PA2 - TX, PA3 - RX */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    break;

  case USART3_BASE:/* PB10 - TX, PB11 - RX */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    break;

  case UART4_BASE:/* PA0 - TX, PA1 - RX */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    break;

  case UART5_BASE:/* PC12 - TX, PD2 - RX */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    break;

  case USART6_BASE:/* PC6 - TX, PC7 - RX */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    break;

  case UART7_BASE:/* PF6 - TX, PF7 - RX */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

    GPIO_PinAFConfig(GPIOF, GPIO_PinSource6, GPIO_AF_UART7);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource7, GPIO_AF_UART7);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    break;

 case UART8_BASE:/* PE1 - TX, PE0 - RX */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_UART8);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource1, GPIO_AF_UART8);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    break;
  }
}

static void uart_initialize(int minor)
{
  const console_tbl *ct = Console_Port_Tbl [minor];
  USART_InitTypeDef   USART_InitStructure;

  /* Configure UART GPIO */
  uart_gpio_initialize(ct->ulCtrlPort1);//uart_gpio_init funcation

  /* Enable UART Clock */
  switch(ct->ulCtrlPort1)
  {
  case USART1_BASE:
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    break;
  case USART2_BASE:
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    break;
  case USART3_BASE:
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    break;
  case UART4_BASE:
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
    break;
  case UART5_BASE:
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
    break;
  case USART6_BASE:
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
    break;
  case UART7_BASE:
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);
    break;
  case UART8_BASE:
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8, ENABLE);
    break;
  default:
    break;
  }

  USART_DeInit((USART_TypeDef *)ct->ulCtrlPort1);

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  /* When using Parity the word length must be configured to 9 bits */
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init((USART_TypeDef *)ct->ulCtrlPort1, &USART_InitStructure);

  /* Enable USART */
  USART_Cmd((USART_TypeDef *)ct->ulCtrlPort1, ENABLE);
}

static int uart_first_open(int major, int minor, void *arg)
{
  rtems_libio_open_close_args_t *oc = (rtems_libio_open_close_args_t *) arg;
  struct rtems_termios_tty *tty = (struct rtems_termios_tty *) oc->iop->data1;
  const console_tbl *ct = Console_Port_Tbl [minor];
  console_data *cd = &Console_Port_Data [minor];

  cd->termios_data = tty;
  rtems_termios_set_initial_baud(tty, ct->ulClock);

  return 0;
}

static int uart_last_close(int major, int minor, void *arg)
{
  return 0;
}

static int uart_read_polled(int minor)
{
  /* return -1 if no character could read */
  const console_tbl *ct = Console_Port_Tbl [minor];

  if(USART_GetFlagStatus((USART_TypeDef *)ct->ulCtrlPort1, USART_FLAG_RXNE) == SET)
  {
    return USART_ReceiveData((USART_TypeDef *)ct->ulCtrlPort1);
  }
  else
  {
    return -1;
  }
}

static void uart_write_polled(int minor, char c)
{
  const console_tbl *ct = Console_Port_Tbl [minor];
  /* wait until we can send a character */
  while(USART_GetFlagStatus((USART_TypeDef *)ct->ulCtrlPort1, USART_FLAG_TXE) == RESET);
  USART_SendData((USART_TypeDef *)ct->ulCtrlPort1, c);
}

static ssize_t uart_write_support_polled(
  int minor,
  const char *s,
  size_t n
)
{
  ssize_t i = 0;

  for (i = 0; i < n; ++i) {
    uart_write_polled(minor, s [i]);
  }

  return n;
}

static int uart_set_attributes(int minor, const struct termios *term)
{
  return -1;
}

const console_fns stm32f4xx_uart_fns = {
  .deviceProbe = libchip_serial_default_probe,
  .deviceFirstOpen = uart_first_open,
  .deviceLastClose = uart_last_close,
  .deviceRead = uart_read_polled,
  .deviceWrite = uart_write_support_polled,
  .deviceInitialize = uart_initialize,
  .deviceWritePolled = uart_write_polled,
  .deviceSetAttributes = uart_set_attributes,
  .deviceOutputUsesInterrupts = false
};
