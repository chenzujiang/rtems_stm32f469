#include "port.h"
#include "mb.h"
#include "mbport.h"
#include <rtems.h> 
#include <bsp/irq.h>
#include <bsp/irq-generic.h>

static BOOL recv_7bit;

/*******************************************************************************
* 名    称: USART3_isr
* 入口参数: 无
* 出口参数: 无
* 返 回 值: 无
* 说    明：串口中断处理函数
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
* 名    称: vMBPortSerialEnable
* 入口参数: xRxEnable - 接收控制
*           xTxEnable - 发送控制
* 出口参数: 无
* 返 回 值: 无
* 说    明：控制端口收发使能
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
* 名    称: xMBPortSerialInit
* 入口参数: ucPORT - 物理端口编号
*           ulBaudRate - 通信波特率
*           ucDataBits - 数据位，7或8
*           eParity - 校验方式，EVEN ODD NONE
* 出口参数: 无
* 返 回 值: 成功返回TRUE
* 说    明：端口初始化
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
* 名    称: xMBPortSerialPutByte
* 入口参数: ucByte - 将要发送的字节
* 出口参数: 无
* 返 回 值: 成功返回TRUE
* 说    明：发送一个字节
*******************************************************************************/
BOOL xMBPortSerialPutByte( CHAR ucByte )
{
  USART_SendData(USART3, ucByte);
  return TRUE;
}

/*******************************************************************************
* 名    称: xMBPortSerialGetByte
* 入口参数: pucByte - 接收到的字节
* 出口参数: 无
* 返 回 值: 成功返回TRUE
* 说    明：接收一个字节
*******************************************************************************/
BOOL xMBPortSerialGetByte( CHAR * pucByte )
{
  /* 数据位为7时丢弃校验位 */
  if(recv_7bit)
    *pucByte = USART_ReceiveData(USART3)&0x7F;
  else
    *pucByte = USART_ReceiveData(USART3);
  return TRUE;
}
