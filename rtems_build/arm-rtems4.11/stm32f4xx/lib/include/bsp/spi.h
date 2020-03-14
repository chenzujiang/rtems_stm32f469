#ifndef LIBBSP_ARM_STM32F4_SPIx_H
#define LIBBSP_ARM_STM32F4_SPIx_H
#include <rtems.h>
#ifdef __cplusplus
extern "C"{
#endif

typedef struct {
	uint32_t addr;//read write addr
	char  *buf;
	uint32_t len;
	bool read;
}spi_message;

#define SET_SLAVE_READ_ADDR  0x01
#define SET_SLAVE_WRITE_ADDR  0x02

void spi_isr(void *arg);

rtems_device_driver
spi_device_init(rtems_device_major_number major, rtems_device_minor_number minor, void *arg);
rtems_device_driver
spi_device_open(rtems_device_major_number major, rtems_device_minor_number minor, void *arg);
rtems_device_driver
spi_device_close(rtems_device_major_number major, rtems_device_minor_number minor, void *arg);
rtems_device_driver
spi_device_read(rtems_device_major_number major, rtems_device_minor_number minor, void *arg);
rtems_device_driver
spi_device_write(rtems_device_major_number major, rtems_device_minor_number minor, void *arg);
rtems_device_driver
spi_device_ioctl(rtems_device_major_number major, rtems_device_minor_number minor, void *arg);

#define  SPI_DRIVER_TABLE_ENTRY \
{\
  spi_device_init, \
  spi_device_open, \
  spi_device_close, \
  spi_device_read, \
  spi_device_write,\
  spi_device_ioctl\
}

#ifdef __cplusplus
}
#endif
#endif
