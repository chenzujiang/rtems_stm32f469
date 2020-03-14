#include <rtems/libio.h>

//#define DEBUG
#define RTEMS_STATUS_CHECKS_USE_PRINTK
#include <rtems/status-checks.h>
#include <bsp.h>
#include <bsp/irq-generic.h>
#include <bsp/stm32f4.h>
#include <bsp/io.h>
#include <bsp/rcc.h>


//RTEMS_SYSLOG

typedef enum {
  LOW_LEVEL = 0x1,
  HIGH_LEVEL = 0x2,
  FALLING = 0x4,
  RISING = 0x8,
  FALLING_AND_RISING = 0xc
};

typedef struct {
  int  port;
  int  iline;
  int  irq;
  int  trig;
  int  val;
  rtems_interrupt_handler proc;
}key_config;

typedef struct {
  volatile stm32f4_exti *reg;
  const key_config *key;
  rtems_id  key_queue;
}key_control;

static void key_irq_pa0(void *arg);
static void key_irq_pc13(void *arg);
static void key_irq_pe2(void *arg);
static void key_irq_pe3(void *arg);


static const key_config key_info[] = {
	[0] = {             /* PA0 */
      .port = GPIO_PORT_A,
	  .iline = 0,
	  .irq = STM32F4_IRQ_EXTI0,
	  .trig = FALLING_AND_RISING,
	  .val = 'a',
	  .proc = key_irq_pa0
  },
#if 1
  [1] = {           /* PC13 */
    .port = GPIO_PORT_C,
	  .iline = 13,
	  .irq = STM32F4_IRQ_EXTI15_10,
	  .trig = FALLING_AND_RISING,
	  .val = 'b',
	  .proc = key_irq_pc13
	},
#endif
  [2] = {           /* PE2 */
    .port = GPIO_PORT_E,
	  .iline = 2,
      .irq = STM32F4_IRQ_EXTI2,
      .trig = FALLING_AND_RISING,
	  .val = 'c',
	  .proc = key_irq_pe2
	},
  [3] = {           /* PE3 */
      .port = GPIO_PORT_E,
	  .iline = 3,
	  .irq = STM32F4_IRQ_EXTI3,
	  .trig = FALLING_AND_RISING,
	  .val = 'd',
	  .proc = key_irq_pe3
	}
};

static key_control key_controller = {
	.reg = STM32F4_EXTI,
	.key = &key_info,
};   


static uint8_t keyboard_irq(rtems_id mq, int val, uint8_t blance)
{
  if (blance) {
  	if (--blance == 0)
  		rtems_message_queue_send(mq, &val, 4);
  }else {
    blance++;
  }
  return blance;
}

static void key_irq_pa0(void *arg)
{

  key_control *key_ctl = arg;
  int iline = key_ctl->key[0].iline;
  static uint8_t blance = 0;
  
  if (key_ctl->reg->pr & STM32F4_EXTI_PR(iline)) {
  	key_ctl->reg->pr = STM32F4_EXTI_PR(iline);
	blance = keyboard_irq(
				key_ctl->key_queue,
				key_ctl->key[0].val,
				blance
			);
  }
}

static void key_irq_pc13(void *arg)
{

  key_control *key_ctl = arg;
  int iline = key_ctl->key[1].iline;
  static uint8_t blance = 0;

  if (key_ctl->reg->pr & STM32F4_EXTI_PR(iline)) {
	key_ctl->reg->pr = STM32F4_EXTI_PR(iline);
	blance = keyboard_irq(
				key_ctl->key_queue,
				key_ctl->key[1].val,
				blance
			);
  	}

}
  
static void key_irq_pe2(void *arg)
{

  key_control *key_ctl = arg;
  int iline = key_ctl->key[2].iline;
  static uint8_t blance = 0;

  if (key_ctl->reg->pr & STM32F4_EXTI_PR(iline)) {
    key_ctl->reg->pr = STM32F4_EXTI_PR(iline);
	blance = keyboard_irq(
				key_ctl->key_queue,
				key_ctl->key[2].val,
				blance
			);

  }
}

static void key_irq_pe3(void *arg)
{

  key_control *key_ctl = arg;
  int iline = key_ctl->key[3].iline;
  static uint8_t blance = 0;

  if (key_ctl->reg->pr & STM32F4_EXTI_PR(iline)) {
	key_ctl->reg->pr = STM32F4_EXTI_PR(iline);
	blance = keyboard_irq(
				key_ctl->key_queue,
				key_ctl->key[3].val,
				blance
			);
  }
}

rtems_device_driver
key_device_init(rtems_device_major_number major,
		rtems_device_minor_number minor, void *arg)
{
  key_control *key_ctl = &key_controller;
  rtems_status_code sc = RTEMS_SUCCESSFUL;
  int count;
  int line;
  
  stm32f4_rcc_set_clock(STM32F4_RCC_SYSCFG, true);

  /* Configure gpio extern interrupt function */
  for (count = 0; count < RTEMS_ARRAY_SIZE(key_info); count++) {
    if (key_ctl->key[count].proc == NULL)
      continue;

    line = key_ctl->key[count].iline;

    /* configure extern interrupt pins*/
    stm32f4_exti_config(key_ctl->key[count].port, line);

	  key_ctl->reg->imr |= STM32F4_EXTI_IMR(line);
    if (key_ctl->key[count].trig & FALLING) 
		key_ctl->reg->ftsr |= STM32F4_EXTI_FTSR(line);
	  if (key_ctl->key[count].trig & RISING)
		key_ctl->reg->rtsr |= STM32F4_EXTI_RTSR(line);

	sc = rtems_interrupt_handler_install(
			key_ctl->key[count].irq,
			"extern-irq",
			RTEMS_INTERRUPT_UNIQUE,
			key_ctl->key[count].proc,
			key_ctl
	);
	RTEMS_CHECK_SC(sc, "Install keyboard interrupt\n\r");
  }

  /* */
  sc = rtems_message_queue_create(
		  rtems_build_name('q', 'k', 'e', 'y'),
		  3,
		  sizeof(int),
		  RTEMS_LOCAL | RTEMS_FIFO,
		  &key_ctl->key_queue
  );
  RTEMS_CHECK_SC(sc, "Create keyboard message queue\n\r");

  /* register keyboard */
  sc = rtems_io_register_name("/dev/keyboard", major, minor);
  RTEMS_CHECK_SC(sc, "Register keyboard driver name\n\r");

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
  key_control *key_ctl = &key_controller;
  rtems_libio_rw_args_t *rd = arg;
  rtems_status_code sc;
  int key_val;
  int size;

  sc = rtems_message_queue_receive(
  	           key_ctl->key_queue,
  	           &key_val,
  	           &size,
  	           RTEMS_WAIT,
  	           0
  	);
  RTEMS_CHECK_SC(sc, "Read keyboard message\n\r");
  *(int *)rd->buffer = key_val;

  return RTEMS_SUCCESSFUL;
}














