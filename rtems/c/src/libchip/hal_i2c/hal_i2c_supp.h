#ifndef __LIBCHIP_HAL_I2C_SUPPORT_h
#define __LIBCHIP_HAL_I2C_SUPPORT_h
#include <rtems.h>
#include <rtems/libio.h>
#include <rtems/assoc.h>
#include <rtems/chain.h>
#include <termios.h>

#ifdef __cplusplus
extern "C" {
#endif

bool libchip_hal_i2c_probe(
  int minor
);

#ifdef __cplusplus
}
#endif

#endif
/* end of include file */
