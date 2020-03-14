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

#ifndef __LIBCHIP_HAL_EXTIx_h
#define __LIBCHIP_HAL_EXTIx_h

#include <termios.h>
#include <rtems/rtems/status.h>
#include <rtems.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef void (*EXTI_ClearIT)(uint32_t EXTI_Line);
/** @} */
typedef int (*EXTI_GetStatusIT)(uint32_t EXTI_Line);

typedef struct {
  uint32_t  port;
  uint32_t  line;
  uint32_t  irq;
  uint32_t  trig;
  char*  val;
  rtems_interrupt_handler proc;
}key_config;
/*
 *  Types for get and set register routines
 */
typedef struct _hal_exti_fns {
  int    (*deviceFirstOpen)(int minor);
  int    (*deviceLastClose)(int minor);
  void   (*deviceInitialize)(int minor);
  int    (*deviceRead)(int minor,uint32_t port,uint32_t line, uint8_t *byte);
  int    (*deviceWrite)(int minor,uint32_t port,uint32_t line, uint8_t *byte);
} hal_exti_fns;

typedef enum {                 /*  */
  HAL_EXTI_CUSTOM                 /* BSP specific driver */
} hal_exti_devs;


typedef struct _hal_exti_tbl {
  /**  This is the name of the device. */
  const char    *sDeviceName;
  hal_exti_devs  deviceType;
  /** pDeviceFns   This is a pointer to the set of driver routines to use. */
  const hal_exti_fns *pDeviceFns;
  void          *pDeviceParams;
  const key_config *key;
  EXTI_ClearIT clearIT;
  EXTI_GetStatusIT getStatusIT;
  rtems_id  key_queue;
} hal_exti_tbl;
extern unsigned long KEY_Configuration_Count;
extern hal_exti_tbl HAL_EXTI_Configuration_Ports;
extern const hal_exti_fns stm32f4xx_exti_fns;

#ifdef __cplusplus
}
#endif

#endif
/* end of include file */
