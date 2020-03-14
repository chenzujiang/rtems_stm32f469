#ifndef STM32F4_SYS_H
#define STM32F4_SYS_H

#include <stdint.h>
#include <bsp/utility.h>


#ifdef __cplusplus
extern "C"{
#endif

typedef struct {
  uint32_t memmap;
#define  STM32F4_REMAP_MAIN_FLASH  0x00
#define  STM32F4_REMAP_SYS_FLASH   0x01
#define  STM32F4_REMAP_FSMC_BANK1  0x10
#define  STM32F4_REMAP_SRAM  0x11

  uint32_t pmc;
#define  STM32F4_ETH_SEL_RMII BSP_BIT32(23)

  uint32_t exticr[4];
#define  STM32F4_EXTI_PIN_SROUCE(n) (n)

  uint32_t reserved[2];
  uint32_t cmpcr;
#define  STM32F4_CMPCR_READY  BSP_BIT32(8)
#define  STM32F4_CMPCF_POWERDOWN BSP_BIT32(0)
}stm32f4_syscfg;


#ifdef __cplusplus
}
#endif

#endif
