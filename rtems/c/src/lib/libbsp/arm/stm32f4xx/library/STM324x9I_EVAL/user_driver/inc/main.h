/**
  ******************************************************************************
  * @file    DSI_TearingEffect_GPIO/main.h 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include <bsp/library/stm32f4xx.h>
#define OTM8009A_ORIENTATION       1//1����,0����
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* SAI PLL parameters to be used for the LTDC clock configuration */
/** 
  * @brief  HAL Status structures definition  
  */  
typedef enum 
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;

#define USED_USART6_PRINTF

#define LTDC_PLLSAIN          417
#define LTDC_PLLSAIP          2
#define LTDC_PLLSAIQ          4
#define LTDC_PLLSAIR          5
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TimingDelay_Decrement(void);

//typedef enum
//{
//	FALSE = 0,
//	TRUE
//}My_bool;
/* Private typedef -----------------------------------------------------------*/
typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;
/** @addtogroup QSPI_ReadWrite_IT
  * @{
  */
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line below according to QSPI FLASH Memory connected on your
   evaluation board (U3)
  */
void Delay(volatile uint32_t nTime);


#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
