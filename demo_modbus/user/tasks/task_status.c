#include <bsp.h>
#include <bsp/library/stm32f4xx.h>
#include "tasks.h"

/*******************************************************************************
* 名    称: task_status
* 入口参数: ignored - 任务参数
* 出口参数: 无
* 返 回 值: 无
* 说    明：最低优先级任务，指示系统运行状态
*******************************************************************************/
rtems_task task_status (rtems_task_argument ignored)
{
  /* Blink status led when system running */
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(GPIOD, &GPIO_InitStructure);

  for(;;)
  {
    GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
    rtems_task_wake_after( 1 * rtems_clock_get_ticks_per_second() );
  }
}
