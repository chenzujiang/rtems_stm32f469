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

#include <rtems/irq-extension.h>
#include <rtems/libio.h>
#include <libchip/sersupp.h>

#include <bsp.h>
#include <bsp/io.h>
#include <bsp/rcc.h>
#include <bsp/irq.h>
#include <bsp/usart.h>
#include <bsp/stm32f4.h>


#define  USART_DRIVER_USE_DMA
//#define  USART_DRIVER_USE_INTERRUPT


static void usart_interrupt_handler(void *arg);

static volatile stm32f4_usart *usart_get_regs(const console_tbl *ct)
{
  return (stm32f4_usart *) ct->ulCtrlPort1;
}

#if 0
static rtems_vector_number usart_get_irq_number(const console_tbl *ct)
{
  return ct->ulIntVector;
}
#endif

static const stm32f4_rcc_index usart_rcc_index [] = {
  STM32F4_RCC_USART1,
  STM32F4_RCC_USART2,
  STM32F4_RCC_USART3,
  STM32F4_RCC_UART4,
  STM32F4_RCC_UART5,
#ifdef STM32F4_FAMILY_F4XXXX
  STM32F4_RCC_USART6
#endif /* STM32F4_FAMILY_F4XXXX */
};

static stm32f4_rcc_index usart_get_rcc_index(const console_tbl *ct)
{
  return usart_rcc_index [ct->ulCtrlPort2];
}

static const uint8_t usart_pclk_index [] = { 1, 0, 0, 0, 0, 1 };

static const uint32_t usart_pclk_by_index [] = {
  STM32F4_PCLK1,
  STM32F4_PCLK2
};


static uint32_t usart_get_pclk(const console_tbl *ct)
{
  return usart_pclk_by_index [usart_pclk_index [ct->ulCtrlPort2]];
}

static uint32_t usart_get_baud(const console_tbl *ct)
{
  return ct->ulClock;
}

/*
 * a = 8 * (2 - CR1[OVER8])
 *
 * usartdiv = div_mantissa + div_fraction / a
 *
 * baud = pclk / (a * usartdiv)
 *
 * usartdiv = pclk / (a * baud)
 *
 * Calculation in integer arithmetic:
 *
 * 1. div_mantissa = pclk / (a * baud)
 *
 * 2. div_fraction = pclk / (baud - a * div_mantissa)
 */
static uint32_t usart_get_bbr(
  volatile stm32f4_usart *usart,
  uint32_t pclk,
  uint32_t baud
)
{
  uint32_t a = 8 * (2 - ((usart->cr1 & STM32F4_USART_CR1_OVER8) != 0));
  uint32_t div_mantissa_low = pclk / (a * baud);
  uint32_t div_fraction_low = pclk / (baud - a * div_mantissa_low);
  uint32_t div_mantissa_high;
  uint32_t div_fraction_high;
  uint32_t high_err;
  uint32_t low_err;
  uint32_t div_mantissa;
  uint32_t div_fraction;

  if (div_fraction_low < a - 1) {
    div_mantissa_high = div_fraction_low;
    div_fraction_high = div_fraction_low + 1;
  } else {
    div_mantissa_high = div_fraction_low + 1;
    div_fraction_high = 0;
  }

  high_err = pclk - baud * (a * div_mantissa_high + div_fraction_high);
  low_err = baud * (a * div_mantissa_low + div_fraction_low) - pclk;

  if (low_err < high_err) {
    div_mantissa = div_mantissa_low;
    div_fraction = div_fraction_low;
  } else {
    div_mantissa = div_mantissa_high;
    div_fraction = div_fraction_high;
  }

  return STM32F4_USART_BBR_DIV_MANTISSA(div_mantissa)
    | STM32F4_USART_BBR_DIV_FRACTION(div_fraction);
}

static inline void start_tx_irq(int minor)
{
  const console_tbl *ct = Console_Port_Tbl [minor];
  volatile stm32f4_usart *usart = usart_get_regs(ct);

  usart->cr1 |= STM32F4_USART_CR1_TXEIE;
}

static inline void stop_tx_irq(int minor)
{
  const console_tbl *ct = Console_Port_Tbl [minor];
  volatile stm32f4_usart *usart = usart_get_regs(ct);

  usart->cr1 &=  ~STM32F4_USART_CR1_TXEIE;
}


static void usart_initialize(int minor)
{
  const console_tbl *ct = Console_Port_Tbl [minor];
  volatile stm32f4_usart *usart = usart_get_regs(ct);
  uint32_t pclk = usart_get_pclk(ct);
  uint32_t baud = usart_get_baud(ct);
  stm32f4_rcc_index rcc_index = usart_get_rcc_index(ct);

  stm32f4_rcc_set_clock(rcc_index, true);

  usart->cr1 = 0;
  usart->cr2 = 0;
  usart->cr3 = 0;
  usart->bbr = usart_get_bbr(usart, pclk, baud);

#ifdef USART_DRIVER_USE_INTERRUPT
  /* Install USART interrupt handler */
  rtems_interrupt_handler_install(
                      ct->ulIntVector,
                      "usart-handler",
                      RTEMS_INTERRUPT_UNIQUE,
                      usart_interrupt_handler,
                      (void *)minor
                  );
#endif

  usart->cr1 = STM32F4_USART_CR1_UE  /* Enable USART */
    | STM32F4_USART_CR1_TE           /* Enable Tx */
    | STM32F4_USART_CR1_RE           /* Enable Rx */
#ifdef USART_DRIVER_USE_INTERRUPT
    | STM32F4_USART_CR1_RXNEIE;      /* Enable Rx interrupt */
#else
    ;
#endif
#ifdef USART_DRIVER_USE_DMA
  dma_config dma_cfg = {.config = 0};
  int  channel = 

  dma_cfg.dma_tcie = true; /* Enalbe send compeleted interrupt */
  dma_cfg.dma_pfctrl = 0;
  dma_cfg.dma_dir = 1;     /* From memory to periph */
  dma_cfg.dma_circ = 0;
  dma_cfg.dma_pinc = 0;
  dma_cfg.dma_minc = 1;
  dma_cfg.dma_psize = 0;
  dma_cfg.dma_msize = 0;
  dma_cfg.dma_pl = 1;
  dma_cfg.dma_chsel = STM32F4_GET_CHANNEL(channel);
  stm32f4_dma_init(channel, &dma_cfg, 0);
  usart->cr3 |= (1 << 7);  /* Enable DMA send */
#endif
}

static int usart_first_open(int major, int minor, void *arg)
{
  rtems_libio_open_close_args_t *oc = (rtems_libio_open_close_args_t *) arg;
  struct rtems_termios_tty *tty = (struct rtems_termios_tty *) oc->iop->data1;
  const console_tbl *ct = Console_Port_Tbl [minor];
  console_data *cd = &Console_Port_Data [minor];

  cd->termios_data = tty;
  rtems_termios_set_initial_baud(tty, ct->ulClock);

  return 0;
}

static int usart_last_close(int major, int minor, void *arg)
{
  return 0;
}

static int usart_read_polled(int minor)
{
  const console_tbl *ct = Console_Port_Tbl [minor];
  volatile stm32f4_usart *usart = usart_get_regs(ct);

  if ((usart->sr & STM32F4_USART_SR_RXNE) != 0) {
    return STM32F4_USART_DR_GET(usart->dr);
  } else {
    return -1;
  }
}

static void usart_write_polled(int minor, char c)
{
  const console_tbl *ct = Console_Port_Tbl [minor];
  volatile stm32f4_usart *usart = usart_get_regs(ct);

  while ((usart->sr & STM32F4_USART_SR_TXE) == 0) {
    /* Wait */
  }

  usart->dr = STM32F4_USART_DR(c);
}

static ssize_t usart_write_support_polled(
  int minor,
  const char *s,
  size_t n
)
{
  ssize_t i = 0;

  for (i = 0; i < n; ++i) {
    usart_write_polled(minor, s [i]);
  }

  return n;
}

static int usart_set_attributes(int minor, const struct termios *term)
{
  return -1;
}

#ifdef USART_DRIVER_USE_INTERRUPT
static int usart_interrupt_write(int minor, const char *d, size_t n)
{
  if (d == NULL || n == 0)
    return 0;
  iwrite_control[minor].wbuf = d;
  iwrite_control[minor].len = n;
  iwrite_control[minor].idx = 0;
  start_tx_irq(minor);

  return n;
}


static void usart_interrupt_handler(void *arg)
{
  int  minor = (int)arg;
  const console_tbl *ct = Console_Port_Tbl [minor];
  volatile stm32f4_usart *usart = usart_get_regs(ct);
  console_data  *cdata = Console_Port_Data + minor;
  char  d;

  if (usart->sr & STM32F4_USART_SR_RXNE) { /* Rx interrupt */

    do {
      usart->sr &= ~STM32F4_USART_SR_RXNE;
      d = usart->dr;
      rtems_termios_enqueue_raw_characters(cdata->termios_data, (const char *)&d, 1);
    }while (usart->sr & STM32F4_USART_SR_RXNE);
  }

  else if (usart->sr & STM32F4_USART_SR_TXE) { /* Tx interrupt */
    iwrite_t  *pwc = &iwrite_control[minor];
    
    if (pwc->idx < pwc->len) {
      do {
        usart->sr &= ~STM32F4_USART_SR_TXE;
        usart->dr = pwc->wbuf[pwc->idx];
        pwc->idx++;
        rtems_termios_dequeue_characters(
            cdata->termios_data,
            1
        );
      }while ((pwc->idx < pwc->len) && (usart->sr & STM32F4_USART_SR_TXE));

    } else {
      usart->sr &= ~STM32F4_USART_SR_TXE;
      stop_tx_irq(minor);
    }
  }

}
#endif


void debuh_usart_initialize(void)
{
  volatile stm32f4_usart *usart = STM32F4_USART_1;
  uint32_t pclk = STM32F4_PCLK2;
  uint32_t baud = STM32F4_USART_BAUD;
  stm32f4_rcc_index rcc_index = STM32F4_RCC_USART1;

  stm32f4_rcc_set_clock(rcc_index, true);

  usart->cr1 = 0;
  usart->cr2 = 0;
  usart->cr3 = 0;
  usart->bbr = usart_get_bbr(usart, pclk, baud);


  usart->cr1 = STM32F4_USART_CR1_UE  /* Enable USART */
    | STM32F4_USART_CR1_TE           /* Enable Tx */
    | STM32F4_USART_CR1_RE;          /* Enable Rx */
}

static void output_char(char c)
{
  volatile stm32f4_usart *usart = STM32F4_USART_1;
  while ((usart->sr & STM32F4_USART_SR_TXE) == 0) {
    /* Wait */
  }
  usart->dr = STM32F4_USART_DR(c);
}


const console_fns stm32f4_usart_fns = {
  .deviceProbe = libchip_serial_default_probe,
  .deviceFirstOpen = usart_first_open,
  .deviceLastClose = usart_last_close,

#ifndef USART_DRIVER_USE_INTERRUPT
  .deviceRead = usart_read_polled,
  .deviceWrite = usart_write_support_polled,
#else
  .deviceRead = NULL,
  .deviceWrite = usart_interrupt_write,
#endif
  .deviceInitialize = usart_initialize,
  .deviceWritePolled = usart_write_polled,
  .deviceSetAttributes = usart_set_attributes,

#ifndef USART_DRIVER_USE_INTERRUPT
  .deviceOutputUsesInterrupts = false
#else
  .deviceOutputUsesInterrupts = true
#endif
};

const BSP_output_char_function_type __bsp_out_port = output_char;

BSP_output_char_function_type BSP_output_char = output_char;

BSP_polling_getchar_function_type BSP_poll_char = NULL;