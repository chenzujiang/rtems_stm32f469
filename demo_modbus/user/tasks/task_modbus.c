#include <bsp.h>
#include "mb.h"
#include "tasks.h"

/*******************************************************************************
* ��    ��: task_modbus
* ��ڲ���: ignored - �������
* ���ڲ���: ��
* �� �� ֵ: ��
* ˵    ����ModbusЭ��ջ�������񣬲��ܷ���
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
