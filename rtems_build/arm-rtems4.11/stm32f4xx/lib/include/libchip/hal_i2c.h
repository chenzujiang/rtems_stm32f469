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

#ifndef __LIBCHIP_HAL_I2Cx_h
#define __LIBCHIP_HAL_I2Cx_h

#include <termios.h>
#include <rtems/rtems/status.h>
#include <rtems.h>
#ifdef __cplusplus
extern "C" {
#endif

/*
 *  Types for get and set register routines
 */


typedef struct _hal_i2c_fns {
  bool    (*deviceProbe)(int minor);
  int    (*deviceFirstOpen)(int minor);
  int    (*deviceLastClose)(int minor);
  void    (*deviceInitialize)(int minor);
  int     (*deviceRead)(int minor,uint16_t slave_addr,uint16_t reg, uint8_t *byte);
  int     (*deviceWrite)(int minor,uint16_t slave_addr,uint16_t reg, uint8_t *byte);
  int     (*deviceMoreRead)(int minor,uint16_t slave_addr,uint16_t reg, uint8_t* arr,uint16_t byte);
  int     (*deviceMoreWrite)(int minor,uint16_t slave_addr,uint16_t reg,uint8_t* arr,uint16_t byte);
} hal_i2c_fns;

typedef enum {                 /* Harris ICM-7170 */
  HAL_I2C_CUSTOM                 /* BSP specific driver */
} hal_i2c_devs;

typedef struct _hal_i2c_tbl {
  /**  This is the name of the device. */
  const char    *sDeviceName;
  hal_i2c_devs       deviceType;
  /** pDeviceFns   This is a pointer to the set of driver routines to use. */
  const hal_i2c_fns *pDeviceFns;
  /** This value is passed to the serial device driver for use.  In termios
   *  itself the number is ignored.
   */
  bool         (*deviceProbe)(int minor);
  void          *pDeviceParams;
  uint16_t 		 addr;
  uint32_t       ulCtrlPort1;
  uint32_t       ulCtrlPort2;
  uint32_t       ulClock;
} hal_i2c_tbl;
/**
 *  This is a dynamically sized set of tables containing the serial
 *  port information.
 */
extern hal_i2c_tbl   **hal_i2c_Port_Tbl;
/**
 * This is the number of led ports defined in the gpio_Port_Tbl.
 */
extern unsigned long   hal_i2c_Port_Count;

extern rtems_device_minor_number hal_i2c_Port_Minor;

extern hal_i2c_tbl  HAL_I2C_Configuration_Ports[];
extern unsigned long   HAL_I2C_Configuration_Count;

#ifdef __cplusplus
}
#endif

#endif
/* end of include file */
