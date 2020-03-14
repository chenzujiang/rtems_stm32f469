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
#include <rtems/bspIo.h>
#include <rtems/score/armv7m.h>
#include <bsp.h>
#include <bsp/start.h>
#include <bsp/library/stm32f4xx.h>
#include <bsp/library/stm324x9i_eval_fmc_sdram.h>
#include <bsp/library/stm324x9i_eval_sdio_sd.h>
#include <bsp/irq.h>
#include <bsp/irq-generic.h>

extern const uint32_t   stm32f4xx_start_config_mpu_region_count;
extern const ARMV7M_MPU_Region stm32f4xx_start_config_mpu_region[];
static BSP_START_TEXT_SECTION void stm32f4xx_init_mpu(void)
{
#ifdef ARM_MULTILIB_ARCH_V7M
	volatile ARMV7M_MPU *mpu = _ARMV7M_MPU;
	uint32_t region_count = stm32f4xx_start_config_mpu_region_count;
	uint32_t i = 0;

	for (i = 0; i < region_count; ++i) {
	  mpu->rbar = stm32f4xx_start_config_mpu_region [i].rbar;
	  mpu->rasr = stm32f4xx_start_config_mpu_region [i].rasr;
	}

	if (region_count > 0) {
	  mpu->ctrl = ARMV7M_MPU_CTRL_ENABLE;
	}
#endif
}
void BSP_START_TEXT_SECTION bsp_start_hook_0(void)
{
	stm32f4xx_init_mpu();
}

void BSP_START_TEXT_SECTION bsp_start_hook_1(void)
{
  bsp_start_copy_sections();
  bsp_start_clear_bss();
  /* At this point we can use objects outside the .start section */
  SystemInit();
  SDRAM_Init();
  SD_Init();

}
