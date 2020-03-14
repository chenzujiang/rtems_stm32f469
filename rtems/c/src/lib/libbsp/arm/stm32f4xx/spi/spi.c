#include <rtems/libio.h>
//#define DEBUG
#define RTEMS_STATUS_CHECKS_USE_PRINTK
#include <rtems/status-checks.h>
#include <bsp.h>
#include <bsp/irq-generic.h>
#include <bsp/io.h>
#include <bsp/spi.h>
#include <bsp/hal_spi.h>
#include <bsp/fatal.h>


static rtems_status_code spi_transmit(int minor,hal_spi_tbl *spi, spi_message *msg)
{
  rtems_status_code sc=RTEMS_IO_ERROR;
  if(msg->read)
  {
	  printk("read befor len=%d,data = %s\r\n",msg->len,(uint8_t*)msg->buf);
	  msg->len = spi->pDeviceFns->deviceRead(minor,spi->read_addr,(uint8_t*)msg->buf,msg->len);
	  printk("read last len=%d,data = %s\r\n",msg->len,msg->buf);
	  return RTEMS_SUCCESSFUL;
  }
  else{
	  printk("write befor len=%d,data = %s\r\n",msg->len,(uint8_t*)msg->buf);
	  msg->len = spi->pDeviceFns->deviceWrite(minor,spi->write_addr,(uint8_t*)msg->buf,msg->len);
	  printk("write last len=%d,data = %s\r\n",msg->len,msg->buf);
	  return RTEMS_SUCCESSFUL;
  }
  return sc;
}

void spi_isr(void *arg)
{
	printk("SPIx interrupter...\r\n");
}

rtems_device_driver
spi_device_init(rtems_device_major_number major,
		rtems_device_minor_number minor_arg, void *arg)
{
	rtems_status_code sc = RTEMS_SUCCESSFUL;
	int count=-1;
	/* Configure gpio extern interrupt function */
	for (count = 0; count < SPI_Configuration_Count; ++count) {
		hal_spi_tbl* spi_table = &HAL_SPI_Configuration_Ports[count];
		spi_table->pDeviceFns->deviceInitialize(count);
		if (spi_table->proc == NULL)
			continue;
		printk("proc count =%d\r\n",count);

		/* Install spi interrupt .......*/
//		sc = rtems_interrupt_handler_install(
//				spi_table->irq,
//				"SPIx ISR",
//				RTEMS_INTERRUPT_UNIQUE,
//				spi_table->proc,
//				spi_table);
//		RTEMS_CHECK_SC(sc, "Install SPIx interrupt handler\r\n");

		if (spi_table->sDeviceName != NULL) {
			sc = rtems_io_register_name(spi_table->sDeviceName, major, count );
			if (sc != RTEMS_SUCCESSFUL) {
				//printk("regester faild");
				bsp_fatal( BSP_FATAL_CONSOLE_REGISTER_DEV_0 );
			}
		}
	}
	return sc;
}
rtems_device_driver
spi_device_open(rtems_device_major_number major, rtems_device_minor_number minor, void *arg)
{
  return RTEMS_SUCCESSFUL;
}

rtems_device_driver
spi_device_close(rtems_device_major_number major, rtems_device_minor_number minor, void *arg)
{
  return RTEMS_SUCCESSFUL;
}

rtems_device_driver
spi_device_write(rtems_device_major_number major, rtems_device_minor_number minor, void *arg)
{
	rtems_libio_rw_args_t *local = arg;
  hal_spi_tbl *spi_table = &HAL_SPI_Configuration_Ports[minor];
  spi_message msg;
  msg.addr = spi_table->write_addr;
  msg.buf = local->buffer;
  msg.len = local->count;
  msg.read = false;
  return spi_transmit(minor,spi_table, &msg);
}
rtems_device_driver spi_device_read(
	rtems_device_major_number major,
	rtems_device_minor_number minor,
	void *arg
)
{
  rtems_libio_rw_args_t *local = arg;
  hal_spi_tbl *spi_table = &HAL_SPI_Configuration_Ports[minor];
  spi_message msg;

  msg.addr = spi_table->read_addr;
  msg.buf = local->buffer;
  msg.len = local->count;
  msg.read = true;

  return spi_transmit(minor,spi_table, &msg);
}
rtems_device_driver spi_device_ioctl(
	rtems_device_major_number major,
	rtems_device_minor_number minor,
	void *arg
)
{
  rtems_libio_ioctl_args_t *local = arg;
  //hal_spi_tbl *spi_table = &HAL_SPI_Configuration_Ports[minor];

  switch(local->command) {
  	case SET_SLAVE_READ_ADDR:
  		//spi_table->read_addr;
		break;
	case SET_SLAVE_WRITE_ADDR:
		//spi_table->write_addr;
		break;

  }
  return RTEMS_SUCCESSFUL;
}


