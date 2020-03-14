#include <bsp.h>
#include <bsp/fatal.h>
#include <rtems/libio.h>
#include <rtems/led-drv.h>
#include <stdlib.h>
#include <assert.h>
#include <rtems/rtems/intr.h>

#include <libchip/gpio_led.h>

unsigned long               gpio_Port_Count  = 0;
gpio_tbl                    **gpio_Port_Tbl    = NULL;
rtems_device_minor_number   gpio_Port_Minor  = 0;
static bool                 gpio_initialized = false;

/*
 *  console_initialize_pointers
 *
 *  This method is used to initialize the table of pointers to the
 *  serial port configuration structure entries.
 */
static void gpio_initialize_pointers(void)
{
  int i;

  if ( gpio_Port_Tbl )
    return;

  gpio_Port_Count = GPIO_Configuration_Count;
  gpio_Port_Tbl   = malloc( gpio_Port_Count * sizeof( gpio_tbl * ) );
  if (gpio_Port_Tbl == NULL)
	  printk("Register led driver failed: BSP_FATAL_LED_NO_MEMORY_0");

  for (i=0 ; i < gpio_Port_Count ; i++)
	  gpio_Port_Tbl[i] = &GPIO_Configuration_Ports[i];
}

rtems_device_driver stm32f_led_init(rtems_device_major_number major,
									rtems_device_minor_number minor_arg,
									void	*arg)
{
	rtems_status_code          status;
	rtems_device_minor_number  minor;

	/*
	* If we have no devices which were registered earlier then we
	* must still initialize pointers and set Console_Port_Data.
	*/
	if ( ! gpio_Port_Tbl ) {
		gpio_initialize_pointers();
	}
	/*
	*  console_initialize has been invoked so it is now too late to
	*  register devices.
	*/
	gpio_initialized = true;

	/*
	 *  Iterate over all of the console devices we know about
	 *  and initialize them.
	 */
	for (minor=0 ; minor < gpio_Port_Count ; minor++)
	{
	  if (gpio_Port_Tbl[minor]->pDeviceFns->deviceProbe(minor))
	  {
		if (gpio_Port_Tbl[minor]->sDeviceName != NULL) {
		  status = rtems_io_register_name( gpio_Port_Tbl[minor]->sDeviceName, major, minor );
		  if (status != RTEMS_SUCCESSFUL) {
			  printk("Register %s failed : sc = %d\r\n", gpio_Port_Tbl[minor]->sDeviceName,status);
		  }
		}
		if (minor == gpio_Port_Minor) {
			status = rtems_io_register_name( RTEMS_LED_DRIVER_NAME, major, minor );
			if (status != RTEMS_SUCCESSFUL)
			  printk("Register led driver RTEMS_LED_DRIVER_NAME failed: sc = %d\r\n", status);
		}
		/*
		 * Initialize the hardware device.
		 */
		gpio_Port_Tbl[minor]->pDeviceFns->deviceInitialize(minor);
	  }
	}
	return RTEMS_SUCCESSFUL;
}


rtems_device_driver stm32f_led_open(rtems_device_major_number major,
									rtems_device_minor_number minor,
									void	*arg)
{
	return RTEMS_SUCCESSFUL;
}
rtems_device_driver stm32f_led_read(rtems_device_major_number major,
									rtems_device_minor_number minor,
									void	*arg)
{
//	rtems_libio_ioctl_args_t *local = arg;
//
//	if(gpio_Port_Tbl == NULL)
//		return RTEMS_INVALID_ID;
//	else
//		gpio_Port_Tbl[minor]->pDeviceFns->deviceGetgpioStatus(minor,(uint32_t*)&local->command,local->buffer);/*address transfer of led status*/

	return RTEMS_SUCCESSFUL;
}
rtems_device_driver stm32f_led_write(rtems_device_major_number major,
									rtems_device_minor_number minor,
									void	*arg)
{
//	rtems_libio_ioctl_args_t *local = arg;
//
//	if(gpio_Port_Tbl == NULL)
//		return RTEMS_INVALID_ID;
//	else
//		gpio_Port_Tbl[minor]->pDeviceFns->deviceSetgpioStatus(minor,local->command,local->buffer);
	return RTEMS_SUCCESSFUL;
}

rtems_device_driver stm32f_led_close(rtems_device_major_number major,
									rtems_device_minor_number minor,
									void	*arg)
{
	return RTEMS_SUCCESSFUL;
}


rtems_device_driver stm32f_led_ioctl(rtems_device_major_number major,
									rtems_device_minor_number minor,
									void	*arg)
{
	rtems_libio_ioctl_args_t *local = arg;
	rtems_interrupt_level level;

	rtems_interrupt_disable(level);
	switch(local->command)
	{
		case LED_DEVICE_OPEN:
		{
			if(gpio_Port_Tbl == NULL)
				return RTEMS_INVALID_ID;
			else
				gpio_Port_Tbl[minor]->pDeviceFns->deviceSetgpioStatus(minor,(uint32_t)local->command,local->buffer);
		}
			break;
		case LED_DEVICE_CLOSE:
		{
			if(gpio_Port_Tbl == NULL)
				return RTEMS_INVALID_ID;
			else
				gpio_Port_Tbl[minor]->pDeviceFns->deviceSetgpioStatus(minor,(uint32_t)local->command,local->buffer);
		}
			break;
	}
	rtems_interrupt_enable(level);

	return RTEMS_SUCCESSFUL;
}

