#include "mb.h"
#include "mbport.h"

static eMBEventType eQueuedEvent;
static rtems_id eMB_event_semaphore;

/*******************************************************************************
* 名    称: xMBPortEventInit
* 入口参数: 无
* 出口参数: 无
* 返 回 值: 成功返回TRUE
* 说    明：Modbus事件初始化
*******************************************************************************/
BOOL xMBPortEventInit( void )
{
  rtems_status_code sc;
  sc = rtems_semaphore_create(
    rtems_build_name('x', 'M', 'B', 'E'), /* 名称 */
    1,                                    /* 初始值 */
    RTEMS_PRIORITY |                      /* 参数 */
      RTEMS_SIMPLE_BINARY_SEMAPHORE |
      RTEMS_NO_INHERIT_PRIORITY |
      RTEMS_NO_PRIORITY_CEILING |
      RTEMS_LOCAL,
    0,                                    /* 天花板优先级 */
    &eMB_event_semaphore);                /* 标识 */
  if(sc != RTEMS_SUCCESSFUL)
    return FALSE;

  return TRUE;
}

/*******************************************************************************
* 名    称: xMBPortEventPost
* 入口参数: eEvent - 发送的事件
* 出口参数: 无
* 返 回 值: 成功返回TRUE
* 说    明：发送一个事件，使用RTOS时最以阻塞的方式使用任务同步以提高效率，注意
* 该函数可能在中断中，也可能在任务中调用，请确保任务同步可以在这两种情景下使用
*******************************************************************************/
BOOL xMBPortEventPost( eMBEventType eEvent )
{
  rtems_status_code sc;
  eQueuedEvent = eEvent;

  sc = rtems_semaphore_release(eMB_event_semaphore);
  if(sc != RTEMS_SUCCESSFUL)
    return FALSE;
  
  return TRUE;
}

/*******************************************************************************
* 名    称: xMBPortEventGet
* 入口参数: 无
* 出口参数: eEvent - 获取的事件
* 返 回 值: 成功返回TRUE
* 说    明：获取一个事件，使用RTOS时最以阻塞的方式使用任务同步以提高效率
*******************************************************************************/
BOOL xMBPortEventGet( eMBEventType * eEvent )
{
  rtems_status_code sc;
  
  sc = rtems_semaphore_obtain(
    eMB_event_semaphore, 
    RTEMS_WAIT, 
    RTEMS_NO_TIMEOUT);
  
  if(sc != RTEMS_SUCCESSFUL)
    return FALSE;
  
  *eEvent = eQueuedEvent;

  return TRUE;
}
