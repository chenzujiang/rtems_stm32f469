#include "system.h"

void thread_led(rtems_task_argument arg)
{
	int led1 = open("/dev/led1", O_RDONLY);
	int led2 = open("/dev/led3", O_RDONLY);

	for ( ; ; ) {
		printf("led led1 %d\r\n",led1);
		ioctl(led1, LED_DEVICE_OPEN,"led on transfer data");
		rtems_task_wake_after(1000);
		ioctl(led2, LED_DEVICE_OPEN,"led on transfer data");
		rtems_task_wake_after(1000);
		ioctl(led1, LED_DEVICE_CLOSE,"led off transfer,data");
		rtems_task_wake_after(1000);
		ioctl(led2, LED_DEVICE_CLOSE,"led off transfer,data");
		rtems_task_wake_after(1000);
	}
}
