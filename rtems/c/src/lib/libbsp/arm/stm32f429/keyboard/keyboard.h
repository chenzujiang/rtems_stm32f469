#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#ifdef __cplusplus
extern "C"{
#endif

rtems_device_driver
key_device_init(rtems_device_major_number major, rtems_device_minor_number minor, void *arg);
rtems_device_driver
key_device_open(rtems_device_major_number major, rtems_device_minor_number minor, void *arg);
rtems_device_driver
key_device_close(rtems_device_major_number major, rtems_device_minor_number minor, void *arg);
rtems_device_driver
key_device_read(rtems_device_major_number major, rtems_device_minor_number minor, void *arg);

#define  KEYBOARD_DRIVER_TABLE_ENTRY \
{\
  key_device_init, \
  key_device_open, \
  key_device_close, \
  key_device_read, \
  NULL, \
  NULL\
}

#ifdef __cplusplus
}
#endif

#endif
