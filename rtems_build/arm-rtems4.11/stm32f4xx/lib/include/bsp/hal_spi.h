/*
 *  This file contains the Real-Time Clock definitions.
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 */

#ifndef __BSP_HAL_SPIx_h
#define __BSP_HAL_SPIx_h

#include <termios.h>
#include <rtems/rtems/status.h>
#include <rtems.h>
//#include <rtems/irq-extension.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef void (*SPI_ClearIT)(uint32_t SPIx);
/** @} */
typedef int (*SPI_GetStatusIT)(uint32_t SPIx);

/*
 *  Types for get and set register routines
 */
typedef struct _hal_spi_fns {
  int    (*deviceFirstOpen)(int minor);
  int    (*deviceLastClose)(int minor);
  void   (*deviceInitialize)(int minor);
  int    (*deviceRead)(int minor,uint32_t read_addr,uint8_t* arr,uint32_t byte);
  int    (*deviceWrite)(int minor,uint32_t write_addr,uint8_t* arr,uint32_t byte);
} hal_spi_fns;

typedef enum {                 /*  */
  HAL_SPI_CUSTOM                 /* BSP specific driver */
} hal_spi_devs;


typedef struct _hal_spi_tbl {
	/**  This is the name of the device. */
	const char    *sDeviceName;
	hal_spi_devs  deviceType;
	/** pDeviceFns   This is a pointer to the set of driver routines to use. */
	const hal_spi_fns *pDeviceFns;
	void          *pDeviceParams;
	uint32_t ulCtrlPort1 ;
	uint32_t write_addr;
	uint32_t read_addr;
	uint32_t  device_id;
	uint32_t  page_size;
	uint32_t  Per_WR_PageSize;
	uint32_t  irq;
	rtems_interrupt_handler proc;
	SPI_ClearIT clearIT;
	SPI_GetStatusIT getStatusIT;
	rtems_id  spi_queue;
} hal_spi_tbl;

extern unsigned long SPI_Configuration_Count;
extern hal_spi_tbl    HAL_SPI_Configuration_Ports[];
extern const hal_spi_fns stm32f4xx_spi_fns;

#ifdef __cplusplus
}
#endif

#endif
/* end of include file */
