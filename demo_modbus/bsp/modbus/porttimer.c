#include "port.h"
#include "mb.h"
#include "mbport.h"
#include <rtems.h> 
#include <bsp/irq.h>
#include <bsp/irq-generic.h>

/*******************************************************************************
* ��    ��: TIM7_isr
* ��ڲ���: ��
* ���ڲ���: ��
* �� �� ֵ: ��
* ˵    ������ʱ�����ڴﵽʱ֪ͨЭ��ջ
*******************************************************************************/
#if defined(BSP_FEATURE_IRQ_EXTENSION) || \
    (CPU_SIMPLE_VECTORED_INTERRUPTS != TRUE)
void TIM7_isr(void *arg)
#else
rtems_isr TIM7_isr(rtems_vector_number vector)
#endif
{
  if (TIM_GetITStatus(TIM7, TIM_FLAG_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM7, TIM_FLAG_Update);
    (void)pxMBPortCBTimerExpired();
  }
}

/*******************************************************************************
* ��    ��: xMBPortTimersInit
* ��ڲ���: usTim1Timerout50us - ��ʱ������
* ���ڲ���: ��
* �� �� ֵ: �ɹ�����TRUE
* ˵    ��������һ������ΪusTim1Timerout50us * 50us�Ķ�ʱ��
*******************************************************************************/
BOOL xMBPortTimersInit( USHORT usTim1Timerout50us )
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
  TIM_DeInit(TIM7);
  TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);

  /* Clock Freq is 48MHz */
  TIM_TimeBaseInitStructure.TIM_Prescaler = 2400 - 1;
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStructure.TIM_Period = usTim1Timerout50us;

  TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStructure);

  TIM_ARRPreloadConfig(TIM7, ENABLE);

  rtems_interrupt_handler_install(
    STM32F4XX_IRQ_TIM7,
    "eMB_TIME",
    RTEMS_INTERRUPT_UNIQUE,
    (rtems_interrupt_handler) TIM7_isr,
    NULL);
 
  NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&NVIC_InitStructure);

  TIM_ClearFlag(TIM7, TIM_FLAG_Update);
  TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM7, DISABLE);

  return TRUE;
}

/*******************************************************************************
* ��    ��: vMBPortTimersEnable
* ��ڲ���: ��
* ���ڲ���: ��
* �� �� ֵ: ��
* ˵    ����ʹ�����ڶ�ʱ��������ȷ����ʱ�����¿�ʼ����
*******************************************************************************/
inline void vMBPortTimersEnable(  )
{
  TIM_ClearFlag(TIM7, TIM_FLAG_Update);
  TIM_SetCounter(TIM7, 0x0);
  TIM_Cmd(TIM7, ENABLE);
}

/*******************************************************************************
* ��    ��: vMBPortTimersDisable
* ��ڲ���: ��
* ���ڲ���: ��
* �� �� ֵ: ��
* ˵    �����ر����ڶ�ʱ��
*******************************************************************************/
inline void vMBPortTimersDisable(  )
{
  TIM_Cmd(TIM7, DISABLE);
  TIM_ClearFlag(TIM7, TIM_FLAG_Update);
}
