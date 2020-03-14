#include "mb.h"
#include "mbport.h"

#define REG_INPUT_START 1001
#define REG_INPUT_NREGS 4

static USHORT   usRegInputStart = REG_INPUT_START;
static USHORT   usRegInputBuf[REG_INPUT_NREGS];

/*******************************************************************************
* 名    称: eMBRegInputCB
* 入口参数: usAddress - 起始地址
*           usNRegs - 数目
* 出口参数: pucRegBuffer - 写缓存
* 返 回 值: eMBErrorCode - 错误码
* 说    明：输入寄存器回调处理函数
*******************************************************************************/
eMBErrorCode
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
  eMBErrorCode    eStatus = MB_ENOERR;
  int             iRegIndex;

  if( ( usAddress >= REG_INPUT_START )
      && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
  {
    iRegIndex = ( int )( usAddress - usRegInputStart );
    while( usNRegs > 0 )
    {
      *pucRegBuffer++ = ( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
      *pucRegBuffer++ = ( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
      iRegIndex++;
      usNRegs--;
    }
    /* Here we simply count the number of poll cycles. */
    usRegInputBuf[0]++;
  }
  else
  {
    eStatus = MB_ENOREG;
  }

  return eStatus;
}

#define REG_HOLDING_START 1001
#define REG_HOLDING_NREGS 4

static USHORT   usRegHoldingStart = REG_HOLDING_START;
static USHORT   usRegHoldingBuf[REG_HOLDING_NREGS];

/*******************************************************************************
* 名    称: eMBRegHoldingCB
* 入口参数: usAddress - 起始地址
*           usNRegs - 数目
* 出口参数: pucRegBuffer - 写缓存
* 返 回 值: eMBErrorCode - 错误码
* 说    明：保存寄存器回调处理函数
*******************************************************************************/
eMBErrorCode
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs,
                 eMBRegisterMode eMode )
{
  eMBErrorCode    eStatus = MB_ENOERR;
  int             iRegIndex;

  if( ( usAddress >= REG_HOLDING_START )
      && ( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ) )
  {
    iRegIndex = ( int )( usAddress - usRegHoldingStart );
    while( usNRegs > 0 )
    {
      *pucRegBuffer++ = ( unsigned char )( usRegHoldingBuf[iRegIndex] >> 8 );
      *pucRegBuffer++ = ( unsigned char )( usRegHoldingBuf[iRegIndex] & 0xFF );
      iRegIndex++;
      usNRegs--;
    }
    /* Here we simply count the number of poll cycles. */
    usRegHoldingBuf[0]++;
  }
  else
  {
    eStatus = MB_ENOREG;
  }

  return eStatus;
}

/*******************************************************************************
* 名    称: eMBRegCoilsCB
* 入口参数: usAddress - 起始地址
*           usNCoils - 数目
* 出口参数: pucRegBuffer - 写缓存
* 返 回 值: eMBErrorCode - 错误码
* 说    明：线圈寄存器回调处理函数
*******************************************************************************/
eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
               eMBRegisterMode eMode )
{
  return MB_ENOREG;
}

/*******************************************************************************
* 名    称: eMBRegDiscreteCB
* 入口参数: usAddress - 起始地址
*           usNDiscrete - 数目
* 出口参数: pucRegBuffer - 写缓存
* 返 回 值: eMBErrorCode - 错误码
* 说    明：离散输入寄存器回调处理函数
*******************************************************************************/
eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
  return MB_ENOREG;
}
