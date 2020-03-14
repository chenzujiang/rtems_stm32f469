/*
 * Copyright (c) 2013 Christian Mauderer.  All rights reserved.
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

/* The I2C-module can not run with libi2c. The reason for this is, that libi2c
 * needs a possibility to generate a stop condition separately. This controller
 * wants to generate the condition automatically when sending or receiving data.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rtems/libio.h>

#include <bsp.h>
#include <bspopts.h>
#include <rtems/i2c-drv.h>
#include <libchip/hal_i2c.h>
#include <bsp/irq-generic.h>
#include <assert.h>
#include <bsp/fatal.h>
#include <assert.h>
#include <rtems/rtems/intr.h>

#define DEBUG
#define RTEMS_STATUS_CHECKS_USE_PRINTK

#include <rtems/status-checks.h>

#define STM32F4_I2C_INITIAL_BITRATE 100000

#define I2C_RW_BIT 0x1

unsigned long               hal_i2c_Port_Count  = 0;
hal_i2c_tbl                 **hal_i2c_Port_Tbl    = NULL;
rtems_device_minor_number   hal_i2c_Port_Minor  = 0;
static bool                 hal_i2c_initialized = false;

/*
 *  hal_i2c_initialize_pointers
 *
 *  This method is used to initialize the table of pointers to the
 *  serial port configuration structure entries.
 */
static void hal_i2c_initialize_pointers(void)
{
  int i;

  if ( hal_i2c_Port_Tbl )
    return;

  hal_i2c_Port_Count = HAL_I2C_Configuration_Count;
  hal_i2c_Port_Tbl   = malloc( hal_i2c_Port_Count * sizeof( hal_i2c_tbl * ) );
  if (hal_i2c_Port_Tbl == NULL)
	  printk("Register i2c driver failed: BSP_FATAL_LED_NO_MEMORY_0");

  for (i=0 ; i < hal_i2c_Port_Count ; i++)
	  hal_i2c_Port_Tbl[i] = &HAL_I2C_Configuration_Ports[i];
}


rtems_status_code stm32f4_i2c_set_bitrate(
		hal_i2c_tbl *e,
  uint32_t br
)
{
//ctrl call set bitrate
  return RTEMS_SUCCESSFUL;
}

rtems_status_code stm32f4_i2c_process_message(
   int minor,
  hal_i2c_tbl *e,
  stm32f4xxx_i2c_message *msg
)
{
  rtems_status_code sc = RTEMS_SUCCESSFUL;
  //call write read
  if(msg->read)
  {
	  printk("read befor len=%d,data = %s\r\n",msg->len,msg->buf);
	  msg->len = e->pDeviceFns->deviceMoreRead(minor,e->addr,0x00,msg->buf,msg->len>256?256:msg->len);
	  printk("read last len=%d,data = %s\r\n",msg->len,msg->buf);
  }
  else{
	  printk("write befor len=%d,data = %s\r\n",msg->len,msg->buf);
	  msg->len = e->pDeviceFns->deviceMoreWrite(minor,e->addr,0x00,msg->buf,msg->len>256?256:msg->len);
	  printk("write last len=%d,data = %s\r\n",msg->len,msg->buf);
  }
  /* Wait for end of message */

  return sc;
}


rtems_device_driver device_i2c_init(
	rtems_device_major_number major,
	rtems_device_minor_number minor_arg,
	void *arg 
)
{
  rtems_status_code status = RTEMS_SUCCESSFUL;
  rtems_device_minor_number  minor;
  hal_i2c_tbl               *port;

	/*
	* If we have no devices which were registered earlier then we
	* must still initialize pointers and set Console_Port_Data.
	*/
	if ( ! hal_i2c_Port_Tbl ) {
		hal_i2c_initialize_pointers();
	}
	/*
	*  console_initialize has been invoked so it is now too late to
	*  register devices.
	*/
	hal_i2c_initialized = true;

	for (minor = 0; minor < HAL_I2C_Configuration_Count; minor++) {
		/*
		 *  First perform the configuration dependent probe, then the
		 *  device dependent probe
		 */
		port = hal_i2c_Port_Tbl[minor];
		if(port == NULL)
			return RTEMS_IO_ERROR;
		if ( (!port->deviceProbe || port->deviceProbe(minor)) &&
				port->pDeviceFns->deviceProbe(minor)) {

			if (port->sDeviceName != NULL) {
				status = rtems_io_register_name( port->sDeviceName, major, minor );
				if (status != RTEMS_SUCCESSFUL) {
					bsp_fatal( BSP_FATAL_CONSOLE_REGISTER_DEV_0 );
				}
			}

			if (minor == hal_i2c_Port_Minor) {
				status = rtems_io_register_name( RTEMS_I2C_DRIVER_NAME, major, minor );
				if (status != RTEMS_SUCCESSFUL) {
					bsp_fatal( BSP_FATAL_CONSOLE_REGISTER_DEV_1 );
				}
			}
			/*
			 * Initialize the hardware device.
			 */
			port->pDeviceFns->deviceInitialize(minor);
			//RTEMS_CHECK_SC(status, "Register i2c device name\n\r");
		}
	}

	return status;
}

rtems_device_driver device_i2c_open(
	rtems_device_major_number major,
	rtems_device_minor_number minor,
	void *arg 
)
{
  return RTEMS_SUCCESSFUL;
}

rtems_device_driver device_i2c_close(
	rtems_device_major_number major,
	rtems_device_minor_number minor,
	void *arg 
)
{
  return RTEMS_SUCCESSFUL;
}

rtems_device_driver device_i2c_read(
	rtems_device_major_number major,
	rtems_device_minor_number minor,
	void *arg 
)
{
  rtems_libio_rw_args_t *local = arg;
  hal_i2c_tbl *e = hal_i2c_Port_Tbl[minor];
  stm32f4xxx_i2c_message msg;

  msg.addr = e->addr;
  msg.buf = local->buffer;
  msg.len = local->count;
  msg.read = true;

  return stm32f4_i2c_process_message(minor, e, &msg);
}

rtems_device_driver device_i2c_write(
	rtems_device_major_number major,
	rtems_device_minor_number minor,
	void *arg 
)
{
  rtems_libio_rw_args_t *local = arg;
  hal_i2c_tbl *e = hal_i2c_Port_Tbl[minor];
  stm32f4xxx_i2c_message msg;

  msg.addr = e->addr;
  msg.buf = local->buffer;
  msg.len = local->count;
  msg.read = false;

  return stm32f4_i2c_process_message(minor,e, &msg);
}

rtems_device_driver device_i2c_ioctl(
	rtems_device_major_number major,
	rtems_device_minor_number minor,
	void *arg 
)
{
  rtems_libio_ioctl_args_t *local = arg;
  hal_i2c_tbl *e = hal_i2c_Port_Tbl[minor];

  switch(local->command) {
  	case SET_SLAVE_ADDR:
		e->addr = *(uint32_t *)local->buffer;
		break;
	case SET_HOST_BAUDRATE: {
		int bdr = *(uint32_t *)local->buffer;
		stm32f4_i2c_set_bitrate(e, bdr);
		break;
	}
  }
  return RTEMS_SUCCESSFUL;
}




