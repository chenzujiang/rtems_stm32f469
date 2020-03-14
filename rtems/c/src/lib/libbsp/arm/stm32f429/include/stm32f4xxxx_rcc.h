/**
 * @file
 * @ingroup stm32f4xxxx_rcc
 * @brief STM32F4XXXX RCC support.
 */

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

#ifndef LIBBSP_ARM_STM32F4_STM32F4XXXX_RCC_H
#define LIBBSP_ARM_STM32F4_STM32F4XXXX_RCC_H

#include <bsp/utility.h>

/**
 * @defgroup stm32f4xxxx_rcc STM32F4XXXX RCC Support
 * @ingroup stm32f4_rcc
 * @brief STM32F4XXXX RCC Support
 * @{
 */

typedef struct {
	uint32_t cr;
	uint32_t pllcfgr;
	uint32_t cfgr;
#define STM32F4_RCC_CFGR_MCO1_SET(reg, val) BSP_FLD32SET(reg, val, 21, 22)
#define STM32F4_RCC_CFGR_MCO1_PRE_SET(reg, val) BSP_FLD32SET(reg, val, 24, 26)

	uint32_t cir;
	uint32_t ahbrstr [3];
	uint32_t reserved_1c;
	uint32_t apbrstr [2];
	uint32_t reserved_28 [2];
	uint32_t ahbenr [3];
	uint32_t reserved_3c;
	uint32_t apbenr [2];
	uint32_t reserved_48 [2];
	uint32_t ahblpenr [3];
	uint32_t reserved_5c;
	uint32_t apblpenr [2];
	uint32_t reserved_68 [2];
	uint32_t bdcr;
	uint32_t csr;
	uint32_t reserved_78 [2];
	uint32_t sscgr;
	uint32_t plli2scfgr;
} stm32f4_rcc;

/** @} */
#define  STM32F4_RCC_CR_HSEON         0x00010000
#define  STM32F4_RCC_CR_HSERDY        0x00020000
#define  STM32F4_RCC_APB1ENR_PWREN  0x10000000

#define  STM32F4_RCC_CFGR_HPRE_DIV1   0x00000000
#define  STM32F4_RCC_CFGR_PPRE2_DIV2  0x00008000
#define  STM32F4_RCC_CFGR_PPRE1_DIV4  0x00001400

#define  STM32F4_RCC_PLLCFGR_PLLSRC_HSE  0x00400000
#define  STM32F4_RCC_CR_PLLON   0x01000000
#define  STM32F4_RCC_CR_PLLRDY  0x02000000

#define  STM32F4_RCC_CFGR_SW       0x00000003
#define  STM32F4_RCC_CFGR_SW_PLL 0x00000002
#define  STM32F4_RCC_CFGR_SWS      0x0000000C
#define  STM32F4_RCC_CFGR_SWS_PLL 0x00000008
 

typedef struct {
	uint32_t	cr;
	uint32_t	csr;
}stm32f4_pwr;

#define STM32F4_PWR_CR_VOS   0x0000C000


typedef struct {
	uint32_t	acr;
	uint32_t	keyr;
	uint32_t	optkeyr;
	uint32_t	sr;
	uint32_t	cr;
	uint32_t	optcr;
	uint32_t	optcr1;
}stm32f4_flash;

#define  STM32F4_FLASH_ACR_PRFTEN	0x00000100
#define  STM32F4_FLASH_ACR_ICEN     0x00000200
#define  STM32F4_FLASH_ACR_DCEN     0x00000400
#define  STM32F4_FLASH_ACR_LATENCY_5WS  0x00000005


#endif /* LIBBSP_ARM_STM32F4_STM32F4XXXX_RCC_H */
