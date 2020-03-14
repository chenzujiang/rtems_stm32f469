#include <bsp.h>
#include "mb.h"
#include "tasks.h"

/*******************************************************************************
* 名    称: task_modbus
* 入口参数: ignored - 任务参数
* 出口参数: 无
* 返 回 值: 无
* 说    明：Modbus协议栈处理任务，不能返回
*******************************************************************************/
rtems_task task_modbus (rtems_task_argument ignored)
{
  eMBErrorCode eStatus;

  eStatus = eMBInit(MB_RTU, 0x01, 0, 9600, MB_PAR_EVEN);
  /* Enable the Modbus Protocol Stack. */
  eStatus = eMBEnable();

  for(;;)
  { /* Block for a Semaphore */
    eStatus = eMBPoll();
  }
}
