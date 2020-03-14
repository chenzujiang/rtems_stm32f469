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

#include <bsp/rcc.h>
#include <bsp/stm32f4.h>

#include <rtems.h>

static void rcc_set(
  stm32f4_rcc_index index,
  bool set,
  volatile uint32_t *regs
)
{
  int reg = index >> 5;
  uint32_t one = 1;
  uint32_t bit = one << (index & 0x1f);
  rtems_interrupt_level level;
  uint32_t val;

  rtems_interrupt_disable(level);
  val = regs [reg];
  if (set) {
    val |= bit;
  } else {
    val &= ~bit;
  }
  regs [reg] = val;
  rtems_interrupt_enable(level);
}

void stm32f4_rcc_reset(stm32f4_rcc_index index)
{
  stm32f4_rcc_set_reset(index, true);
  stm32f4_rcc_set_reset(index, false);
}

void stm32f4_rcc_set_reset(stm32f4_rcc_index index, bool set)
{
  volatile stm32f4_rcc *rcc = STM32F4_RCC;

#ifdef STM32F4_FAMILY_F4XXXX
  rcc_set(index, set, &rcc->ahbrstr [0]);
#endif/* STM32F4_FAMILY_F4XXXX */
#ifdef STM32F4_FAMILY_F10XXX
  /* The first register is missing for the reset-block */
  rcc_set(index, set, &rcc->cir);
#endif /* STM32F4_FAMILY_F10XXX */
}

void stm32f4_rcc_set_clock(stm32f4_rcc_index index, bool set)
{
  volatile stm32f4_rcc *rcc = STM32F4_RCC;

  rcc_set(index, set, &rcc->ahbenr [0]);
}

#ifdef STM32F4_FAMILY_F4XXXX
void stm32f4_rcc_set_low_power_clock(stm32f4_rcc_index index, bool set)
{
  volatile stm32f4_rcc *rcc = STM32F4_RCC;

  rcc_set(index, set, &rcc->ahblpenr [0]);
}
#endif /* STM32F4_FAMILY_F4XXXX */


#ifdef STM32F4_FAMILY_F4XXXX

/* Define pll parameters */
#define STM32F4_PLL_M  (uint32_t)25
#define STM32F4_PLL_N  (uint32_t)336
#define STM32F4_PLL_P  (uint32_t)2
#define STM32F4_PLL_Q  (uint32_t)7

void stm32f4_rcc_init_clock(void)
{
  volatile stm32f4_rcc *rcc = STM32F4_RCC;
  volatile stm32f4_pwr *pwr = STM32F4_PWR;
  volatile stm32f4_flash *flash = STM32F4_FLASH;
  uint32_t  count = 0;
  bool  timeout = false;

  /* Reset the RCC clock configuration to the default reset state ------------*/
  rcc->cr  |= 0x1;
  rcc->cfgr = 0x0;
  rcc->cr  &= 0xFEF6FFFF;
  rcc->pllcfgr = 0x24003010;
  rcc->cr  &= 0xFFFBFFFF;
  rcc->cir  = 0x0; /* Disable all interrupt */

  /* Configure the System clock source, PLL Multiplier and Divider factors */
  rcc->cr |= STM32F4_RCC_CR_HSEON;
  while(!(rcc->cr & STM32F4_RCC_CR_HSERDY)) {
    if (count++ >= 0x5000) 
      return;
  }

  rcc->apbenr[0] |= STM32F4_RCC_APB1ENR_PWREN;
  pwr->cr |= STM32F4_PWR_CR_VOS;

  /* HCLK = SYSCLK / 1*/
  rcc->cfgr |= STM32F4_RCC_CFGR_HPRE_DIV1;

  /* PCLK2 = HCLK / 2*/
  rcc->cfgr |= STM32F4_RCC_CFGR_PPRE2_DIV2;

  /* PCLK1 = HCLK / 4*/
  rcc->cfgr |= STM32F4_RCC_CFGR_PPRE1_DIV4;
  
   /* Configure the main PLL */
  rcc->pllcfgr = STM32F4_PLL_M | \
           (STM32F4_PLL_N << 6) | \
           (((STM32F4_PLL_P >> 1) -1) << 16) | \
           STM32F4_RCC_PLLCFGR_PLLSRC_HSE | \
           (STM32F4_PLL_Q << 24);
  rcc->cr |= STM32F4_RCC_CR_PLLON;

  /* Wait till the main PLL is ready */
  while (!(rcc->cr & STM32F4_RCC_CR_PLLON))
    ;

  flash->acr = STM32F4_FLASH_ACR_PRFTEN | \
               STM32F4_FLASH_ACR_ICEN | \
               STM32F4_FLASH_ACR_DCEN | \
               STM32F4_FLASH_ACR_LATENCY_5WS;
           
  rcc->cfgr &= ~STM32F4_RCC_CFGR_SW;
  rcc->cfgr |= STM32F4_RCC_CFGR_SW_PLL;

  while ((rcc->cfgr & STM32F4_RCC_CFGR_SWS) != STM32F4_RCC_CFGR_SWS_PLL)
    ;
}
#endif
