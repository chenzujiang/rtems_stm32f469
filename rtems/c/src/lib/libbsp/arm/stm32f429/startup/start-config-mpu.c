#include <rtems/score/armv7m.h>
#include <bsp.h>

#ifdef ARM_MULTILIB_ARCH_V7M
const ARMV7M_MPU_Region
stm32f4xx_start_config_mpu_region[] = {
	
	ARMV7M_MPU_REGION_INITIALIZER(
	  0,
	  0x08000000,
	  ARMV7M_MPU_SIZE_2_MB,
	  ARMV7M_MPU_ATTR_RX
	),
	
	ARMV7M_MPU_REGION_INITIALIZER(
	  1,
	  0x20000000,
	  ARMV7M_MPU_SIZE_256_KB,
	  ARMV7M_MPU_ATTR_RWX
	),
	
	ARMV7M_MPU_REGION_INITIALIZER(
	  2,
	  0x40000000,
	  ARMV7M_MPU_SIZE_512_MB,
	  ARMV7M_MPU_ATTR_RW
	),
	
	ARMV7M_MPU_REGION_INITIALIZER(
	  3,
	  0x80000000,
	  ARMV7M_MPU_SIZE_1_GB,
	  ARMV7M_MPU_ATTR_RW
	),
	
	ARMV7M_MPU_REGION_INITIALIZER(
	  4,
	  0xD0000000,
	  ARMV7M_MPU_SIZE_16_MB,
	  ARMV7M_MPU_ATTR_RWX
	),	
	
	ARMV7M_MPU_REGION_INITIALIZER(
	  5,
	  0xE0000000,
	  ARMV7M_MPU_SIZE_1_MB,
	  ARMV7M_MPU_ATTR_RW
	),	
};


const uint32_t  stm32f4xx_start_config_mpu_region_count = 
	sizeof(stm32f4xx_start_config_mpu_region)/sizeof(stm32f4xx_start_config_mpu_region[0]);	
#endif





