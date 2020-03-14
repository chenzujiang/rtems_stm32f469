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

#ifndef __LIBCHIP_GPIO_LED_h
#define __LIBCHIP_GPIO_LED_h

#include <termios.h>
#include <rtems/rtems/status.h>
#include <rtems.h>
#ifdef __cplusplus
extern "C" {
#endif

/*
 *  Types for get and set register routines
 */


typedef struct _gpio_fns {
  bool    (*deviceProbe)(int minor);
  void    (*deviceInitialize)(int minor);
  int     (*deviceGetgpioStatus)(int minor,uint32_t* status,void* buffer);
  int     (*deviceSetgpioStatus)(int minor,uint32_t status,void* buffer);
} gpio_fns;

typedef enum {                 /* Harris ICM-7170 */
  GPIO_CUSTOM                 /* BSP specific driver */
} gpio_devs;

typedef struct _gpio_tbl {
  /**  This is the name of the device. */
  const char    *sDeviceName;
  gpio_devs       deviceType;
  /** pDeviceFns   This is a pointer to the set of driver routines to use. */
  const gpio_fns *pDeviceFns;
  /** This value is passed to the serial device driver for use.  In termios
   *  itself the number is ignored.
   */
  bool         (*deviceProbe)(int minor);
  void          *pDeviceParams;
  uint32_t       ulCtrlPort1;
  uint32_t       ulCtrlPort2;
  uint32_t       ulClock;
} gpio_tbl;
/**
 *  This is a dynamically sized set of tables containing the serial
 *  port information.
 */
extern gpio_tbl   **gpio_Port_Tbl;
/**
 * This is the number of led ports defined in the gpio_Port_Tbl.
 */
extern unsigned long   gpio_Port_Count;

extern rtems_device_minor_number gpio_Port_Minor;

extern gpio_tbl  GPIO_Configuration_Ports[];
extern unsigned long   GPIO_Configuration_Count;

#ifdef __cplusplus
}
#endif

#endif
/* end of include file */
