#include <rtems/libio.h>
//#define DEBUG
#define RTEMS_STATUS_CHECKS_USE_PRINTK
#include <rtems/status-checks.h>
#include <bsp.h>
#include <bsp/irq-generic.h>
#include <bsp/io.h>
#include <bsp/keyboard.h>
#include <bsp/hal_exti.h>

static uint8_t keyboard_irq(rtems_id mq, char* val, uint8_t blance)
{
  if (blance) {
  	if (--blance == 0)
  		printk("key irq!\r\n");
  		rtems_message_queue_send(mq, val, 9);
  }else {
    blance++;
  }
  return blance;
}
#if defined(BSP_FEATURE_IRQ_EXTENSION) || \
    (CPU_SIMPLE_VECTORED_INTERRUPTS != TRUE)
void key_irq_pa0(void *arg)
#else
rtems_isr key_irq_pa0(rtems_vector_number vector)
#endif
{
  hal_exti_tbl *key_conf = &HAL_EXTI_Configuration_Ports;
  static uint8_t blance = 0;
  if(key_conf->getStatusIT(key_conf->key[0].line))
  {
	  key_conf->clearIT(key_conf->key[0].line);
	 blance = keyboard_irq(key_conf->key_queue,key_conf->key[0].val,blance);
  }
}

#if defined(BSP_FEATURE_IRQ_EXTENSION) || \
    (CPU_SIMPLE_VECTORED_INTERRUPTS != TRUE)
void key_irq_pc13(void *arg)
#else
rtems_isr key_irq_pc13(rtems_vector_number vector)
#endif
{

	  hal_exti_tbl *key_conf = &HAL_EXTI_Configuration_Ports;
	  static uint8_t blance = 0;
	  if(key_conf->getStatusIT(key_conf->key[1].line))
	  {
		  key_conf->clearIT(key_conf->key[1].line);
		  blance = keyboard_irq(key_conf->key_queue,key_conf->key[1].val,blance);
	  }
}
rtems_device_driver
key_device_init(rtems_device_major_number major,
		rtems_device_minor_number minor, void *arg)
{
  hal_exti_tbl *key_conf = &HAL_EXTI_Configuration_Ports;
  rtems_status_code sc = RTEMS_SUCCESSFUL;
  int count;
  /* Configure gpio extern interrupt function */
  for (count = 0; count < KEY_Configuration_Count; ++count) {
	key_conf->pDeviceFns->deviceInitialize(count);
    if (key_conf->key[count].proc == NULL)
      continue;
    printk("proc count =%d\r\n",count);
	sc = rtems_interrupt_handler_install(key_conf->key[count].irq,"extern-irq",
			RTEMS_INTERRUPT_UNIQUE,key_conf->key[count].proc,key_conf);
	RTEMS_CHECK_SC(sc, "Install keyboard interrupt\n\r");
  }

  sc = rtems_message_queue_create(
		  rtems_build_name('q', 'k', 'e', 'y'),
		  3,
		  9,// sizeof(int),
		  RTEMS_LOCAL | RTEMS_FIFO,
		  &key_conf->key_queue);
  RTEMS_CHECK_SC(sc, "Create keyboard message queue\n\r");

  /* register keyboard */
  sc = rtems_io_register_name(key_conf->sDeviceName, major, minor);
  RTEMS_CHECK_SC(sc, "Register keyboard driver name\n\r");
  printk("register status=%d,count =%d",sc,count);
  return sc;
}

rtems_device_driver
key_device_open(rtems_device_major_number major, rtems_device_minor_number minor, void *arg)
{
  return RTEMS_SUCCESSFUL;
}

rtems_device_driver
key_device_close(rtems_device_major_number major, rtems_device_minor_number minor, void *arg)
{
  return RTEMS_SUCCESSFUL;
}

rtems_device_driver
key_device_read(rtems_device_major_number major, rtems_device_minor_number minor, void *arg)
{
  hal_exti_tbl *key_conf = &HAL_EXTI_Configuration_Ports;
  rtems_libio_rw_args_t *rd = arg;
  rtems_status_code sc;
  //char* key_val = rd->buffer;
  size_t size = rd->count;

  sc = rtems_message_queue_receive(
		  key_conf->key_queue,
  	           (void *)rd->buffer,
  	           &size,
  	           RTEMS_WAIT,
  	           0
  	);
  //printk("recv queue msg%s\r\n",rd->buffer);
  RTEMS_CHECK_SC(sc, "Read keyboard message\n\r");
  return RTEMS_SUCCESSFUL;
}
rtems_device_driver
key_device_write(rtems_device_major_number major, rtems_device_minor_number minor, void *arg)
{
	return RTEMS_SUCCESSFUL;
}
rtems_device_driver
key_device_ioctl(rtems_device_major_number major, rtems_device_minor_number minor, void *arg)
{
	return RTEMS_SUCCESSFUL;
}












