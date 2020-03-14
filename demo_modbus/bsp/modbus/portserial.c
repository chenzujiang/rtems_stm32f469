#include "port.h"
#include "mb.h"
#include "mbport.h"
#include <rtems.h> 
#include <bsp/irq.h>
#include <bsp/irq-generic.h>

static BOOL recv_7bit;

/*******************************************************************************
* ��    ��: USART3_isr
* ��ڲ���: ��
* ���ڲ���: ��
* �� �� ֵ: ��
* ˵    ���������жϴ�����
*******************************************************************************/
#if defined(BSP_FEATURE_IRQ_EXTENSION) || \
    (CPU_SIMPLE_VECTORED_INTERRUPTS != TRUE)
void USART3_isr(void *arg)
#else
rtems_isr USART3_isr(rtems_vector_number vector)
#endif
{
  if(USART_GetITStatus(USART3, USART_IT_RXNE))
  {
    USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    pxMBFrameCBByteReceived(  );
  }

  if(USART_GetITStatus(USART3, USART_IT_TXE))
  {
    USART_ClearITPendingBit(USART3, USART_IT_TXE);
    pxMBFrameCBTransmitterEmpty(  );
  }
}

/*******************************************************************************
* ��    ��: vMBPortSerialEnable
* ��ڲ���: xRxEnable - ���տ���
*           xTxEnable - ���Ϳ���
* ���ڲ���: ��
* �� �� ֵ: ��
* ˵    �������ƶ˿��շ�ʹ��
*******************************************************************************/
void vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
  if(xRxEnable)
  {
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
  }
  else
  {
    USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
  }

  if(xTxEnable)
  {
    USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
  }
  else
  {
    USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
  }
}

/*******************************************************************************
* ��    ��: xMBPortSerialInit
* ��ڲ���: ucPORT - ����˿ڱ��
*           ulBaudRate - ͨ�Ų�����
*           ucDataBits - ����λ��7��8
*           eParity - У�鷽ʽ��EVEN ODD NONE
* ���ڲ���: ��
* �� �� ֵ: �ɹ�����TRUE
* ˵    �����˿ڳ�ʼ��
*******************************************************************************/
BOOL xMBPortSerialInit( UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
  USART_InitTypeDef   USART_InitStructure;
  GPIO_InitTypeDef    GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Peripheral Clock Enable -------------------------------------------------*/
  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

  /* Enable USART clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

  /* USARTx GPIO configuration -----------------------------------------------*/
  /* Connect USART pins to AF7 */
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);

  /* Configure USART Tx and Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  USART_DeInit(USART3);
  /* USARTx configuration ----------------------------------------------------*/
  /* Enable the USART OverSampling by 16 */
  USART_OverSampling8Cmd(USART3, DISABLE);

  /* USARTx configured as follows:
      - BaudRate = 5250000 baud
         - Maximum BaudRate that can be achieved when using the Oversampling by 8
           is: (USART APB Clock / 8)
           Example:
              - (USART3 APB1 Clock / 8) = (42 MHz / 8) = 5250000 baud
              - (USART1 APB2 Clock / 8) = (84 MHz / 8) = 10500000 baud
         - Maximum BaudRate that can be achieved when using the Oversampling by 16
           is: (USART APB Clock / 16)
           Example: (USART3 APB1 Clock / 16) = (42 MHz / 16) = 2625000 baud
           Example: (USART1 APB2 Clock / 16) = (84 MHz / 16) = 5250000 baud
      - Word Length = 8 Bits
      - one Stop Bit
      - No parity
      - Hardware flow control disabled (RTS and CTS signals)
      - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = ulBaudRate;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;

  /* */
  if(ucDataBits == 7)
  {
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    recv_7bit = TRUE;

    switch(eParity)
    {
    case MB_PAR_ODD:
      USART_InitStructure.USART_Parity = USART_Parity_Odd;
      break;
    case MB_PAR_EVEN:
      USART_InitStructure.USART_Parity = USART_Parity_Even;
      break;
    default:
      return FALSE;
    }
  }
  else if(ucDataBits == 8)
  {
    USART_InitStructure.USART_WordLength = USART_WordLength_9b;
    recv_7bit = FALSE;

    switch(eParity)
    {
    case MB_PAR_ODD:
      USART_InitStructure.USART_Parity = USART_Parity_Odd;
      break;
    case MB_PAR_EVEN:
      USART_InitStructure.USART_Parity = USART_Parity_Even;
      break;
    case MB_PAR_NONE:
      USART_InitStructure.USART_Parity = USART_Parity_No;
      USART_InitStructure.USART_WordLength = USART_WordLength_8b;
      break;
    default:
      return FALSE;
    }
  }
  else
  {
    return FALSE;
  }

  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART3, &USART_InitStructure);

  rtems_interrupt_handler_install(
    STM32F4XX_IRQ_USART3,
    "eMB_UART",
    RTEMS_INTERRUPT_UNIQUE,
    (rtems_interrupt_handler) USART3_isr,
    NULL);

  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&NVIC_InitStructure);

  /* Configure DMA controller to manage USART TX and RX DMA request ----------*/
  /* Enable USART */
  USART_Cmd(USART3, ENABLE);

  return TRUE;
}

/*******************************************************************************
* ��    ��: xMBPortSerialPutByte
* ��ڲ���: ucByte - ��Ҫ���͵��ֽ�
* ���ڲ���: ��
* �� �� ֵ: �ɹ�����TRUE
* ˵    ��������һ���ֽ�
*******************************************************************************/
BOOL xMBPortSerialPutByte( CHAR ucByte )
{
  USART_SendData(USART3, ucByte);
  return TRUE;
}

/*******************************************************************************
* ��    ��: xMBPortSerialGetByte
* ��ڲ���: pucByte - ���յ����ֽ�
* ���ڲ���: ��
* �� �� ֵ: �ɹ�����TRUE
* ˵    ��������һ���ֽ�
*******************************************************************************/
BOOL xMBPortSerialGetByte( CHAR * pucByte )
{
  /* ����λΪ7ʱ����У��λ */
  if(recv_7bit)
    *pucByte = USART_ReceiveData(USART3)&0x7F;
  else
    *pucByte = USART_ReceiveData(USART3);
  return TRUE;
}
