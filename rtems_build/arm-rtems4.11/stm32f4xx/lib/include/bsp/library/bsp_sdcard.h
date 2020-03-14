/**
  ******************************************************************************
  * @file    NVIC_cfg.h
  * @author  hw
  * @version V1.0
  * @date    2015-1-5
  * @brief   stm32 FWLib 3.5.0�⽨��GPRSģ��NVIC_cfg�������ļ�
  ******************************************************************************
  */
#ifndef _APP_SDCARD_H_
#define _APP_SDCARD_H_


/* Includes ------------------------------------------------------------------*/
//#include "stm32f4xx.h"
//#include "bsp_sdio_sdcard.h"
#include "stm324x9i_eval_sdio_sd.h"
#include <stdio.h>
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern SD_Error Status;
extern SD_CardInfo SDCardInfo;
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void SD_EraseTest(void);
void SD_SingleBlockTest(void);
void SD_MultiBlockTest(void);

#endif /* _APP_SDCARD_H_ */
/******************* (C) COPYRIGHT HW ************* END OF FILE ***************/
