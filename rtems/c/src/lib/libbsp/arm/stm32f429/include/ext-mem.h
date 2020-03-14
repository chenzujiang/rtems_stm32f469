#ifndef EXTERN_MEM_H
#define EXTERN_MEM_H
#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef enum {
	STM32F4_FMC_SDRAM_BANK1 = 0,
	STM32F4_FMC_SDRAM_BANK2 = 1
}stm32f4_sdram_bank;


typedef struct {
	uint32_t	btcr[8];
}stm32f4_fmc_bank1;

typedef struct {
	uint32_t	bwtr[7];
}stm32f4_fmc_bank1e;

typedef struct {
	uint32_t	pcr;
	uint32_t	sr;
	uint32_t	pmem;
	uint32_t	patt;
	uint32_t	reserved0;
	uint32_t	eccr;
}stm32f4_fmc_bank23;

typedef struct {
	uint32_t	pcr4;
	uint32_t	sr4;
	uint32_t	pmem4;
	uint32_t	patt4;
	uint32_t	pio4;
}stm32f4_fmc_bank4;

typedef struct {
	uint32_t	sdcr[2];
	uint32_t	sdtr[2];
	uint32_t	sdcmr;
	uint32_t	sdrtr;
	uint32_t	sdsr;
}stm32f4_fmc_bank56;


extern void stm32f4_sdram_init(stm32f4_sdram_bank bank);

#ifdef __cplusplus
}
#endif

#endif
