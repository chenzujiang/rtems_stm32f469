/*
 *  This file contains the default Real-Time Clock probe routine.
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 */

#include <rtems.h>
#include <libchip/gpio_led.h>
#include <libchip/gpio_led_supp.h>

bool libchip_gpio_led_probe(
  int minor
)
{
  return true;
}
