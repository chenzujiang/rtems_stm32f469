/**
  ******************************************************************************
  * @file    bsp_general_tim.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ͨ�ö�ʱ����ʱ����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���  STM32 F429 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
#include <bsp/library/stm32f4xx.h>
#include "bsp_general_tim.h"
#include <bsp/library/main.h>
#include <bsp.h>
#include <bsp/irq-generic.h>
#include "./lvgl-5.1/lv_hal/lv_hal_tick.h"

 #if defined(BSP_FEATURE_IRQ_EXTENSION) || \
    (CPU_SIMPLE_VECTORED_INTERRUPTS != TRUE)
void TIM2_isr(void *arg)
#else
rtems_isr DSI_isr(rtems_vector_number vector)
#endif
{
	TIM2_IRQHandler();
}
/**
  * @brief  ͨ�ö�ʱ�� TIMx,x[1,8]�ж����ȼ�����
  * @param  ��
  * @retval ��
  */
static void TIMx_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = GENERAL_TIM_IRQn; 	
		// ������ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ���������ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*
 * ע�⣺TIM_TimeBaseInitTypeDef�ṹ��������5����Ա��TIM6��TIM7�ļĴ�������ֻ��
 * TIM_Prescaler��TIM_Period������ʹ��TIM6��TIM7��ʱ��ֻ���ʼ����������Ա���ɣ�
 * ���������Ա��ͨ�ö�ʱ���͸߼���ʱ������.
 *-----------------------------------------------------------------------------
 * TIM_Prescaler         ����
 * TIM_CounterMode			 TIMx,x[6,7]û�У������У���ʱ����
 * TIM_Period            ����
 * TIM_ClockDivision     TIMx,x[6,7]û�У�������(��ʱ��)
 * TIM_RepetitionCounter TIMx,x[1,8]����(�߼���ʱ��)
 *-----------------------------------------------------------------------------
 */
static void TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	// ����TIMx_CLK,x[6,7] 
  RCC_APB1PeriphClockCmd(GENERAL_TIM_CLK, ENABLE); 

  /* �ۼ� TIM_Period�������һ�����»����ж�*/		
  //����ʱ����0����4999����Ϊ5000�Σ�Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Period = 10-1;       
	
	// �߼����ƶ�ʱ��ʱ��ԴTIMxCLK = HCLK/2=90MHz 
	// �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=10000Hz
  TIM_TimeBaseStructure.TIM_Prescaler = 9000-1;	
  // ����ʱ�ӷ�Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  // ����ʽ
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	// ��ʼ����ʱ��TIMx, x[1,8]
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);
	
	
	// ���ʱ�������жϱ�־λ
	TIM_ClearFlag(GENERAL_TIM, TIM_FLAG_Update);
	
	// ������ʱ�������ж�
	TIM_ITConfig(GENERAL_TIM,TIM_IT_Update,ENABLE);
	
	// ʹ�ܶ�ʱ��
	TIM_Cmd(GENERAL_TIM, ENABLE);	
}

/**
  * @brief  ��ʼ���߼����ƶ�ʱ����ʱ��1ms����һ���ж�
  * @param  ��
  * @retval ��
  */
void TIMx_Configuration(void)
{
	TIMx_NVIC_Configuration();	
	TIM_Mode_Config();
    rtems_interrupt_handler_install(
    		STM32F4XX_IRQ_TIM2,
      "TIM2_INT",
      RTEMS_INTERRUPT_UNIQUE,
      (rtems_interrupt_handler) TIM2_isr,
      NULL);
}

void  TIM2_IRQHandler (void)
{
	if ( TIM_GetITStatus( GENERAL_TIM, TIM_IT_Update) != RESET ) 
	{	
		TimingDelay_Decrement();
		lv_tick_inc(1);	//1ms interrupt
		TIM_ClearITPendingBit(GENERAL_TIM , TIM_IT_Update);  		 
	}		 	
}
/*********************************************END OF FILE**********************/
