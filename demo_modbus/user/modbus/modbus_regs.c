#include "mb.h"
#include "mbport.h"

#define REG_INPUT_START 1001
#define REG_INPUT_NREGS 4

static USHORT   usRegInputStart = REG_INPUT_START;
static USHORT   usRegInputBuf[REG_INPUT_NREGS];

/*******************************************************************************
* ��    ��: eMBRegInputCB
* ��ڲ���: usAddress - ��ʼ��ַ
*           usNRegs - ��Ŀ
* ���ڲ���: pucRegBuffer - д����
* �� �� ֵ: eMBErrorCode - ������
* ˵    ��������Ĵ����ص�������
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
* ��    ��: eMBRegHoldingCB
* ��ڲ���: usAddress - ��ʼ��ַ
*           usNRegs - ��Ŀ
* ���ڲ���: pucRegBuffer - д����
* �� �� ֵ: eMBErrorCode - ������
* ˵    ��������Ĵ����ص�������
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
* ��    ��: eMBRegCoilsCB
* ��ڲ���: usAddress - ��ʼ��ַ
*           usNCoils - ��Ŀ
* ���ڲ���: pucRegBuffer - д����
* �� �� ֵ: eMBErrorCode - ������
* ˵    ������Ȧ�Ĵ����ص�������
*******************************************************************************/
eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
               eMBRegisterMode eMode )
{
  return MB_ENOREG;
}

/*******************************************************************************
* ��    ��: eMBRegDiscreteCB
* ��ڲ���: usAddress - ��ʼ��ַ
*           usNDiscrete - ��Ŀ
* ���ڲ���: pucRegBuffer - д����
* �� �� ֵ: eMBErrorCode - ������
* ˵    ������ɢ����Ĵ����ص�������
*******************************************************************************/
eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
  return MB_ENOREG;
}
