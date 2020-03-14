#include "mb.h"
#include "mbport.h"

static eMBEventType eQueuedEvent;
static rtems_id eMB_event_semaphore;

/*******************************************************************************
* ��    ��: xMBPortEventInit
* ��ڲ���: ��
* ���ڲ���: ��
* �� �� ֵ: �ɹ�����TRUE
* ˵    ����Modbus�¼���ʼ��
*******************************************************************************/
BOOL xMBPortEventInit( void )
{
  rtems_status_code sc;
  sc = rtems_semaphore_create(
    rtems_build_name('x', 'M', 'B', 'E'), /* ���� */
    1,                                    /* ��ʼֵ */
    RTEMS_PRIORITY |                      /* ���� */
      RTEMS_SIMPLE_BINARY_SEMAPHORE |
      RTEMS_NO_INHERIT_PRIORITY |
      RTEMS_NO_PRIORITY_CEILING |
      RTEMS_LOCAL,
    0,                                    /* �컨�����ȼ� */
    &eMB_event_semaphore);                /* ��ʶ */
  if(sc != RTEMS_SUCCESSFUL)
    return FALSE;

  return TRUE;
}

/*******************************************************************************
* ��    ��: xMBPortEventPost
* ��ڲ���: eEvent - ���͵��¼�
* ���ڲ���: ��
* �� �� ֵ: �ɹ�����TRUE
* ˵    ��������һ���¼���ʹ��RTOSʱ���������ķ�ʽʹ������ͬ�������Ч�ʣ�ע��
* �ú����������ж��У�Ҳ�����������е��ã���ȷ������ͬ���������������龰��ʹ��
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
* ��    ��: xMBPortEventGet
* ��ڲ���: ��
* ���ڲ���: eEvent - ��ȡ���¼�
* �� �� ֵ: �ɹ�����TRUE
* ˵    ������ȡһ���¼���ʹ��RTOSʱ���������ķ�ʽʹ������ͬ�������Ч��
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
