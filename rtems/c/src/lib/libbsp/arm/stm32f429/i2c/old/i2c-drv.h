#ifndef I2C_DRV_H
#define I2C_DRV_H

#ifdef __cplusplus
extern "C"{
#endif

#define SET_SLAVE_ADDR  0x1

rtems_device_driver device_i2c_init(
	rtems_device_major_number major,
	rtems_device_minor_number minor,
	void *arg 
);
rtems_device_driver device_i2c_open(
	rtems_device_major_number major,
	rtems_device_minor_number minor,
	void *arg 
);
rtems_device_driver device_i2c_close(
	rtems_device_major_number major,
	rtems_device_minor_number minor,
	void *arg 
);
rtems_device_driver device_i2c_read(
	rtems_device_major_number major,
	rtems_device_minor_number minor,
	void *arg 
);
rtems_device_driver device_i2c_write(
	rtems_device_major_number major,
	rtems_device_minor_number minor,
	void *arg 
);
rtems_device_driver device_i2c_ioctl(
	rtems_device_major_number major,
	rtems_device_minor_number minor,
	void *arg 
);


#define I2C_DEVICE_DRIVER_ENTRY\
{\
  device_i2c_init,\
  device_i2c_open,\
  device_i2c_close,\
  device_i2c_read,\
  device_i2c_write,\
  device_i2c_ioctl\
}



#ifdef __cplusplus
}
#endif

#endif
