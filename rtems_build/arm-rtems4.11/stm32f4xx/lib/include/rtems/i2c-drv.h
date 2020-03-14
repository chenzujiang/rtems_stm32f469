#ifndef I2C_DRV_H
#define I2C_DRV_H
#include <rtems.h>
#include <libchip/hal_i2c.h>
#ifdef __cplusplus
extern "C"{
#endif
#define  RTEMS_I2C_DRIVER_NAME  "/dev/i2c"
#define SET_SLAVE_ADDR  0x1
#define SET_HOST_BAUDRATE 0x2

typedef struct {
  /**
   * @brief The address of the slave without the read write bit.
   * A 7-Bit address should be placed in the bits [6..0]
   */
  uint16_t addr;
  uint16_t addr_reg;
  /** @brief Read (true) or write (false) data */
  bool read;
  /** @brief Size of data to read or write */
  uint32_t len;
  /** @brief Buffer for data */
  uint8_t *buf;
} stm32f4xxx_i2c_message;


/** @brief Process a i2c message */
rtems_status_code stm32f4_i2c_process_message(
		int minor,
		hal_i2c_tbl *e,
  stm32f4xxx_i2c_message *msg
);

/** @brief Set another baud rate than the default one */
rtems_status_code stm32f4_i2c_set_bitrate(
		hal_i2c_tbl *e,
  uint32_t br
);
/**
 * @defgroup stm32f4_i2c I2C Support
 * @ingroup arm_stm32f4
 * @brief I2C Module
 * @{
 */


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


#define CONFIGURE_ENABLE_BSP_I2C_DRIVER_ENTRY\
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
