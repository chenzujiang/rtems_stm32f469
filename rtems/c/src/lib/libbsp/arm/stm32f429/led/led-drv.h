#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#ifdef __cplusplus
extern "C"{
#endif

#define  LED_DEVICE_OPEN   1
#define  LED_DEVICE_CLOSE  2
#define  RTEMS_LED_DRIVER_NAME  "/dev/led"

	
rtems_device_driver stm32f_led_init(rtems_device_major_number major,
									rtems_device_minor_number minor,
									void	*arg);
rtems_device_driver stm32f_led_open(rtems_device_major_number major,
									rtems_device_minor_number minor,
									void	*arg);
rtems_device_driver stm32f_led_close(rtems_device_major_number major,
									rtems_device_minor_number minor,
									void	*arg);
rtems_device_driver stm32f_led_ioctl(rtems_device_major_number major,
									rtems_device_minor_number minor,
									void	*arg);


#define  BSP_LED_DRIVER_HANDLE \
	{ \
		stm32f_led_init, \
		stm32f_led_open, \
		stm32f_led_close, \
		NULL,\
		NULL,\
		stm32f_led_ioctl \
	}

#ifdef __cplusplus
}
#endif

#endif