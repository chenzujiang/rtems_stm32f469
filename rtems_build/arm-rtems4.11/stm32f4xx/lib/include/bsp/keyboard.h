#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#include <rtems.h>
#ifdef __cplusplus
extern "C"{
#endif

void key_irq_pa0(void *arg);
void key_irq_pc13(void *arg);

rtems_device_driver
key_device_init(rtems_device_major_number major, rtems_device_minor_number minor, void *arg);
rtems_device_driver
key_device_open(rtems_device_major_number major, rtems_device_minor_number minor, void *arg);
rtems_device_driver
key_device_close(rtems_device_major_number major, rtems_device_minor_number minor, void *arg);
rtems_device_driver
key_device_read(rtems_device_major_number major, rtems_device_minor_number minor, void *arg);
rtems_device_driver
key_device_write(rtems_device_major_number major, rtems_device_minor_number minor, void *arg);
rtems_device_driver
key_device_ioctl(rtems_device_major_number major, rtems_device_minor_number minor, void *arg);

#define  KEYBOARD_DRIVER_TABLE_ENTRY \
{\
  key_device_init, \
  key_device_open, \
  key_device_close, \
  key_device_read, \
  key_device_write,\
  key_device_ioctl\
}

#ifdef __cplusplus
}
#endif

#endif
