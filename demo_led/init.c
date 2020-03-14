/*
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 */

#include <stdio.h>
#include <bsp.h>
#include <bsp/library/stm32f4xx.h>

/* BSP中该函数被声明为弱符号，因此可以被重定义而不产生错误，以便匹配不同的硬件 */
void uart_gpio_initialize (uint32_t uart)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  switch(uart)
  {
  case USART3_BASE:/* PB10 - TX, PB11 - RX */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    break;
    
  default:
    break;
  }
}

rtems_task Init(
  rtems_task_argument argument
)
{
  rtems_status_code status;

  puts( "\n\nLED BLINKER  task wake after" );

  while (1) {

    (void) rtems_task_wake_after( 1 * rtems_clock_get_ticks_per_second() );
    puts( "\n LED ON \n");
    (void) rtems_task_wake_after( 1 * rtems_clock_get_ticks_per_second() );
    puts( "\n LED OFF \n");

  }

  status = rtems_task_delete( RTEMS_SELF );
}

/**************** START OF CONFIGURATION INFORMATION ****************/

#define CONFIGURE_MICROSECONDS_PER_TICK 10000

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_TASKS             1

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT
#include <rtems/confdefs.h>

/****************  END OF CONFIGURATION INFORMATION  ****************/
