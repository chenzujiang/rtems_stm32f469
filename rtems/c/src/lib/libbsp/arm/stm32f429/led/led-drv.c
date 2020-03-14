#include <rtems.h>
#include <rtems/libio.h>
#include <rtems/bspIo.h>
#include <rtems/rtems/intr.h>

#include <bsp/led-drv.h>
#include <bsp/io.h>



rtems_device_driver stm32f_led_init(rtems_device_major_number major,
									rtems_device_minor_number minor,
									void	*arg)
{
	rtems_status_code sc;

	/* Register LED device */
	sc = rtems_io_register_name(RTEMS_LED_DRIVER_NAME, major, 0);
	if (sc != RTEMS_SUCCESSFUL) {
		printk("Register led driver failed: sc = %d", sc);
		return sc;
	}

	/* Switch on led device */
	stm32f4_gpio_set_output(STM32F4_GPIO_PIN(3, 13), false);

	return RTEMS_SUCCESSFUL;
}


rtems_device_driver stm32f_led_open(rtems_device_major_number major,
									rtems_device_minor_number minor,
									void	*arg)
{
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
	switch(local->command) {
		case LED_DEVICE_OPEN:
			stm32f4_gpio_set_output(STM32F4_GPIO_PIN(3, 13), false);
			break;
		case LED_DEVICE_CLOSE:
			stm32f4_gpio_set_output(STM32F4_GPIO_PIN(3, 13), true);
			break;
	}
	rtems_interrupt_enable(level);

	return RTEMS_SUCCESSFUL;
}

