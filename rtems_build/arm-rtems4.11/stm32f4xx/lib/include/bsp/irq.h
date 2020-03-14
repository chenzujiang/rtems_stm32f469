/*
* Copyright (c) 2012 Sebastian Huber.  All rights reserved.
*
*  embedded brains GmbH
*  Obere Lagerstr. 30
*  82178 Puchheim
*  Germany
*  <rtems@embedded-brains.de>
*
* The license and distribution terms for this file may be
* found in the file LICENSE in this distribution or at
* http://www.rtems.org/license/LICENSE.
*/

#ifndef LIBBSP_ARM_STM32F4XX_IRQ_H
#define LIBBSP_ARM_STM32F4XX_IRQ_H

#ifndef ASM

#include <rtems.h>
#include <rtems/irq.h>
#include <rtems/irq-extension.h>
#include <bspopts.h>
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ASM */

#define BSP_INTERRUPT_VECTOR_MIN              0

#define STM32F4XX_IRQ_WWDG                    0
#define STM32F4XX_IRQ_PVD                     1
#define STM32F4XX_IRQ_TAMP_STAMP              2
#define STM32F4XX_IRQ_RTC_WKUP                3
#define STM32F4XX_IRQ_FLASH                   4
#define STM32F4XX_IRQ_RCC                     5
#define STM32F4XX_IRQ_EXTI0                   6
#define STM32F4XX_IRQ_EXTI1                   7
#define STM32F4XX_IRQ_EXTI2                   8
#define STM32F4XX_IRQ_EXTI3                   9
#define STM32F4XX_IRQ_EXTI4                   10
#define STM32F4XX_IRQ_DMA1_Stream0            11
#define STM32F4XX_IRQ_DMA1_Stream1            12
#define STM32F4XX_IRQ_DMA1_Stream2            13
#define STM32F4XX_IRQ_DMA1_Stream3            14
#define STM32F4XX_IRQ_DMA1_Stream4            15
#define STM32F4XX_IRQ_DMA1_Stream5            16
#define STM32F4XX_IRQ_DMA1_Stream6            17
#define STM32F4XX_IRQ_ADC                     18

#if defined(STM32F4XX_FAMILY_STM32F40_41xxx)
#define STM32F4XX_IRQ_CAN1_TX                 19
#define STM32F4XX_IRQ_CAN1_RX0                20
#define STM32F4XX_IRQ_CAN1_RX1                21
#define STM32F4XX_IRQ_CAN1_SCE                22
#define STM32F4XX_IRQ_EXTI9_5                 23
#define STM32F4XX_IRQ_TIM1_BRK_TIM9           24
#define STM32F4XX_IRQ_TIM1_UP_TIM10           25
#define STM32F4XX_IRQ_TIM1_TRG_COM_TIM11      26
#define STM32F4XX_IRQ_TIM1_CC                 27
#define STM32F4XX_IRQ_TIM2                    28
#define STM32F4XX_IRQ_TIM3                    29
#define STM32F4XX_IRQ_TIM4                    30
#define STM32F4XX_IRQ_I2C1_EV                 31
#define STM32F4XX_IRQ_I2C1_ER                 32
#define STM32F4XX_IRQ_I2C2_EV                 33
#define STM32F4XX_IRQ_I2C2_ER                 34
#define STM32F4XX_IRQ_SPI1                    35
#define STM32F4XX_IRQ_SPI2                    36
#define STM32F4XX_IRQ_USART1                  37
#define STM32F4XX_IRQ_USART2                  38
#define STM32F4XX_IRQ_USART3                  39
#define STM32F4XX_IRQ_EXTI15_10               40
#define STM32F4XX_IRQ_RTC_Alarm               41
#define STM32F4XX_IRQ_OTG_FS_WKUP             42
#define STM32F4XX_IRQ_TIM8_BRK_TIM12          43
#define STM32F4XX_IRQ_TIM8_UP_TIM13           44
#define STM32F4XX_IRQ_TIM8_TRG_COM_TIM14      45
#define STM32F4XX_IRQ_TIM8_CC                 46
#define STM32F4XX_IRQ_DMA1_Stream7            47
#define STM32F4XX_IRQ_FSMC                    48
#define STM32F4XX_IRQ_SDIO                    49
#define STM32F4XX_IRQ_TIM5                    50
#define STM32F4XX_IRQ_SPI3                    51
#define STM32F4XX_IRQ_UART4                   52
#define STM32F4XX_IRQ_UART5                   53
#define STM32F4XX_IRQ_TIM6_DAC                54
#define STM32F4XX_IRQ_TIM7                    55
#define STM32F4XX_IRQ_DMA2_Stream0            56
#define STM32F4XX_IRQ_DMA2_Stream1            57
#define STM32F4XX_IRQ_DMA2_Stream2            58
#define STM32F4XX_IRQ_DMA2_Stream3            59
#define STM32F4XX_IRQ_DMA2_Stream4            60
#define STM32F4XX_IRQ_ETH                     61
#define STM32F4XX_IRQ_ETH_WKUP                62
#define STM32F4XX_IRQ_CAN2_TX                 63
#define STM32F4XX_IRQ_CAN2_RX0                64
#define STM32F4XX_IRQ_CAN2_RX1                65
#define STM32F4XX_IRQ_CAN2_SCE                66
#define STM32F4XX_IRQ_OTG_FS                  67
#define STM32F4XX_IRQ_DMA2_Stream5            68
#define STM32F4XX_IRQ_DMA2_Stream6            69
#define STM32F4XX_IRQ_DMA2_Stream7            70
#define STM32F4XX_IRQ_USART6                  71
#define STM32F4XX_IRQ_I2C3_EV                 72
#define STM32F4XX_IRQ_I2C3_ER                 73
#define STM32F4XX_IRQ_OTG_HS_EP1_OUT          74
#define STM32F4XX_IRQ_OTG_HS_EP1_IN           75
#define STM32F4XX_IRQ_OTG_HS_WKUP             76
#define STM32F4XX_IRQ_OTG_HS                  77
#define STM32F4XX_IRQ_DCMI                    78
#define STM32F4XX_IRQ_CRYP                    79
#define STM32F4XX_IRQ_HASH_RNG                80
#define STM32F4XX_IRQ_FPU                     81
#define BSP_INTERRUPT_VECTOR_MAX STM32F4XX_IRQ_FPU
#endif

#if defined(STM32F4XX_FAMILY_STM32F427_437xx)
#define STM32F4XX_IRQ_CAN1_TX                 19
#define STM32F4XX_IRQ_CAN1_RX0                20
#define STM32F4XX_IRQ_CAN1_RX1                21
#define STM32F4XX_IRQ_CAN1_SCE                22
#define STM32F4XX_IRQ_EXTI9_5                 23
#define STM32F4XX_IRQ_TIM1_BRK_TIM9           24
#define STM32F4XX_IRQ_TIM1_UP_TIM10           25
#define STM32F4XX_IRQ_TIM1_TRG_COM_TIM11      26
#define STM32F4XX_IRQ_TIM1_CC                 27
#define STM32F4XX_IRQ_TIM2                    28
#define STM32F4XX_IRQ_TIM3                    29
#define STM32F4XX_IRQ_TIM4                    30
#define STM32F4XX_IRQ_I2C1_EV                 31
#define STM32F4XX_IRQ_I2C1_ER                 32
#define STM32F4XX_IRQ_I2C2_EV                 33
#define STM32F4XX_IRQ_I2C2_ER                 34
#define STM32F4XX_IRQ_SPI1                    35
#define STM32F4XX_IRQ_SPI2                    36
#define STM32F4XX_IRQ_USART1                  37
#define STM32F4XX_IRQ_USART2                  38
#define STM32F4XX_IRQ_USART3                  39
#define STM32F4XX_IRQ_EXTI15_10               40
#define STM32F4XX_IRQ_RTC_Alarm               41
#define STM32F4XX_IRQ_OTG_FS_WKUP             42
#define STM32F4XX_IRQ_TIM8_BRK_TIM12          43
#define STM32F4XX_IRQ_TIM8_UP_TIM13           44
#define STM32F4XX_IRQ_TIM8_TRG_COM_TIM14      45
#define STM32F4XX_IRQ_TIM8_CC                 46
#define STM32F4XX_IRQ_DMA1_Stream7            47
#define STM32F4XX_IRQ_FMC                     48
#define STM32F4XX_IRQ_SDIO                    49
#define STM32F4XX_IRQ_TIM5                    50
#define STM32F4XX_IRQ_SPI3                    51
#define STM32F4XX_IRQ_UART4                   52
#define STM32F4XX_IRQ_UART5                   53
#define STM32F4XX_IRQ_TIM6_DAC                54
#define STM32F4XX_IRQ_TIM7                    55
#define STM32F4XX_IRQ_DMA2_Stream0            56
#define STM32F4XX_IRQ_DMA2_Stream1            57
#define STM32F4XX_IRQ_DMA2_Stream2            58
#define STM32F4XX_IRQ_DMA2_Stream3            59
#define STM32F4XX_IRQ_DMA2_Stream4            60
#define STM32F4XX_IRQ_ETH                     61
#define STM32F4XX_IRQ_ETH_WKUP                62
#define STM32F4XX_IRQ_CAN2_TX                 63
#define STM32F4XX_IRQ_CAN2_RX0                64
#define STM32F4XX_IRQ_CAN2_RX1                65
#define STM32F4XX_IRQ_CAN2_SCE                66
#define STM32F4XX_IRQ_OTG_FS                  67
#define STM32F4XX_IRQ_DMA2_Stream5            68
#define STM32F4XX_IRQ_DMA2_Stream6            69
#define STM32F4XX_IRQ_DMA2_Stream7            70
#define STM32F4XX_IRQ_USART6                  71
#define STM32F4XX_IRQ_I2C3_EV                 72
#define STM32F4XX_IRQ_I2C3_ER                 73
#define STM32F4XX_IRQ_OTG_HS_EP1_OUT          74
#define STM32F4XX_IRQ_OTG_HS_EP1_IN           75
#define STM32F4XX_IRQ_OTG_HS_WKUP             76
#define STM32F4XX_IRQ_OTG_HS                  77
#define STM32F4XX_IRQ_DCMI                    78
#define STM32F4XX_IRQ_CRYP                    79
#define STM32F4XX_IRQ_HASH_RNG                80
#define STM32F4XX_IRQ_FPU                     81
#define STM32F4XX_IRQ_UART7                   82
#define STM32F4XX_IRQ_UART8                   83
#define STM32F4XX_IRQ_SPI4                    84
#define STM32F4XX_IRQ_SPI5                    85
#define STM32F4XX_IRQ_SPI6                    86
#define STM32F4XX_IRQ_SAI1                    87
#define STM32F4XX_IRQ_DMA2D                   90
#define BSP_INTERRUPT_VECTOR_MAX STM32F4XX_IRQ_DMA2D
#endif

#if defined(STM32F4XX_FAMILY_STM32F429_439xx)
#define STM32F4XX_IRQ_CAN1_TX                 19
#define STM32F4XX_IRQ_CAN1_RX0                20
#define STM32F4XX_IRQ_CAN1_RX1                21
#define STM32F4XX_IRQ_CAN1_SCE                22
#define STM32F4XX_IRQ_EXTI9_5                 23
#define STM32F4XX_IRQ_TIM1_BRK_TIM9           24
#define STM32F4XX_IRQ_TIM1_UP_TIM10           25
#define STM32F4XX_IRQ_TIM1_TRG_COM_TIM11      26
#define STM32F4XX_IRQ_TIM1_CC                 27
#define STM32F4XX_IRQ_TIM2                    28
#define STM32F4XX_IRQ_TIM3                    29
#define STM32F4XX_IRQ_TIM4                    30
#define STM32F4XX_IRQ_I2C1_EV                 31
#define STM32F4XX_IRQ_I2C1_ER                 32
#define STM32F4XX_IRQ_I2C2_EV                 33
#define STM32F4XX_IRQ_I2C2_ER                 34
#define STM32F4XX_IRQ_SPI1                    35
#define STM32F4XX_IRQ_SPI2                    36
#define STM32F4XX_IRQ_USART1                  37
#define STM32F4XX_IRQ_USART2                  38
#define STM32F4XX_IRQ_USART3                  39
#define STM32F4XX_IRQ_EXTI15_10               40
#define STM32F4XX_IRQ_RTC_Alarm               41
#define STM32F4XX_IRQ_OTG_FS_WKUP             42
#define STM32F4XX_IRQ_TIM8_BRK_TIM12          43
#define STM32F4XX_IRQ_TIM8_UP_TIM13           44
#define STM32F4XX_IRQ_TIM8_TRG_COM_TIM14      45
#define STM32F4XX_IRQ_TIM8_CC                 46
#define STM32F4XX_IRQ_DMA1_Stream7            47
#define STM32F4XX_IRQ_FMC                     48
#define STM32F4XX_IRQ_SDIO                    49
#define STM32F4XX_IRQ_TIM5                    50
#define STM32F4XX_IRQ_SPI3                    51
#define STM32F4XX_IRQ_UART4                   52
#define STM32F4XX_IRQ_UART5                   53
#define STM32F4XX_IRQ_TIM6_DAC                54
#define STM32F4XX_IRQ_TIM7                    55
#define STM32F4XX_IRQ_DMA2_Stream0            56
#define STM32F4XX_IRQ_DMA2_Stream1            57
#define STM32F4XX_IRQ_DMA2_Stream2            58
#define STM32F4XX_IRQ_DMA2_Stream3            59
#define STM32F4XX_IRQ_DMA2_Stream4            60
#define STM32F4XX_IRQ_ETH                     61
#define STM32F4XX_IRQ_ETH_WKUP                62
#define STM32F4XX_IRQ_CAN2_TX                 63
#define STM32F4XX_IRQ_CAN2_RX0                64
#define STM32F4XX_IRQ_CAN2_RX1                65
#define STM32F4XX_IRQ_CAN2_SCE                66
#define STM32F4XX_IRQ_OTG_FS                  67
#define STM32F4XX_IRQ_DMA2_Stream5            68
#define STM32F4XX_IRQ_DMA2_Stream6            69
#define STM32F4XX_IRQ_DMA2_Stream7            70
#define STM32F4XX_IRQ_USART6                  71
#define STM32F4XX_IRQ_I2C3_EV                 72
#define STM32F4XX_IRQ_I2C3_ER                 73
#define STM32F4XX_IRQ_OTG_HS_EP1_OUT          74
#define STM32F4XX_IRQ_OTG_HS_EP1_IN           75
#define STM32F4XX_IRQ_OTG_HS_WKUP             76
#define STM32F4XX_IRQ_OTG_HS                  77
#define STM32F4XX_IRQ_DCMI                    78
#define STM32F4XX_IRQ_CRYP                    79
#define STM32F4XX_IRQ_HASH_RNG                80
#define STM32F4XX_IRQ_FPU                     81
#define STM32F4XX_IRQ_UART7                   82
#define STM32F4XX_IRQ_UART8                   83
#define STM32F4XX_IRQ_SPI4                    84
#define STM32F4XX_IRQ_SPI5                    85
#define STM32F4XX_IRQ_SPI6                    86
#define STM32F4XX_IRQ_SAI1                    87
#define STM32F4XX_IRQ_LTDC                    88
#define STM32F4XX_IRQ_LTDC_ER                 89
#define STM32F4XX_IRQ_DMA2D                   90
#define BSP_INTERRUPT_VECTOR_MAX STM32F4XX_IRQ_DMA2D
#endif

#if defined(STM32F4XX_FAMILY_STM32F410xx)
#define STM32F4XX_IRQ_EXTI9_5                 23
#define STM32F4XX_IRQ_TIM1_BRK_TIM9           24
#define STM32F4XX_IRQ_TIM1_UP                 25
#define STM32F4XX_IRQ_TIM1_TRG_COM_TIM11      26
#define STM32F4XX_IRQ_TIM1_CC                 27
#define STM32F4XX_IRQ_I2C1_EV                 31
#define STM32F4XX_IRQ_I2C1_ER                 32
#define STM32F4XX_IRQ_I2C2_EV                 33
#define STM32F4XX_IRQ_I2C2_ER                 34
#define STM32F4XX_IRQ_SPI1                    35
#define STM32F4XX_IRQ_SPI2                    36
#define STM32F4XX_IRQ_USART1                  37
#define STM32F4XX_IRQ_USART2                  38
#define STM32F4XX_IRQ_EXTI15_10               40
#define STM32F4XX_IRQ_RTC_Alarm               41
#define STM32F4XX_IRQ_DMA1_Stream7            47
#define STM32F4XX_IRQ_TIM5                    50
#define STM32F4XX_IRQ_TIM6_DAC                54
#define STM32F4XX_IRQ_DMA2_Stream0            56
#define STM32F4XX_IRQ_DMA2_Stream1            57
#define STM32F4XX_IRQ_DMA2_Stream2            58
#define STM32F4XX_IRQ_DMA2_Stream3            59
#define STM32F4XX_IRQ_DMA2_Stream4            60
#define STM32F4XX_IRQ_DMA2_Stream5            68
#define STM32F4XX_IRQ_DMA2_Stream6            69
#define STM32F4XX_IRQ_DMA2_Stream7            70
#define STM32F4XX_IRQ_USART6                  71
#define STM32F4XX_IRQ_RNG                     80
#define STM32F4XX_IRQ_FPU                     81
#define STM32F4XX_IRQ_SPI5                    85
#define STM32F4XX_IRQ_FMPI2C1_EV              95
#define STM32F4XX_IRQ_FMPI2C1_ER              96
#define STM32F4XX_IRQ_LPTIM1                  97
#define BSP_INTERRUPT_VECTOR_MAX STM32F4XX_IRQ_LPTIM1
#endif

#if defined(STM32F4XX_FAMILY_STM32F401xx) || defined(STM32F4XX_FAMILY_STM32F411xE)
#define STM32F4XX_IRQ_EXTI9_5                 23
#define STM32F4XX_IRQ_TIM1_BRK_TIM9           24
#define STM32F4XX_IRQ_TIM1_UP_TIM10           25
#define STM32F4XX_IRQ_TIM1_TRG_COM_TIM11      26
#define STM32F4XX_IRQ_TIM1_CC                 27
#define STM32F4XX_IRQ_TIM2                    28
#define STM32F4XX_IRQ_TIM3                    29
#define STM32F4XX_IRQ_TIM4                    30
#define STM32F4XX_IRQ_I2C1_EV                 31
#define STM32F4XX_IRQ_I2C1_ER                 32
#define STM32F4XX_IRQ_I2C2_EV                 33
#define STM32F4XX_IRQ_I2C2_ER                 34
#define STM32F4XX_IRQ_SPI1                    35
#define STM32F4XX_IRQ_SPI2                    36
#define STM32F4XX_IRQ_USART1                  37
#define STM32F4XX_IRQ_USART2                  38
#define STM32F4XX_IRQ_EXTI15_10               40
#define STM32F4XX_IRQ_RTC_Alarm               41
#define STM32F4XX_IRQ_OTG_FS_WKUP             42
#define STM32F4XX_IRQ_DMA1_Stream7            47
#define STM32F4XX_IRQ_SDIO                    49
#define STM32F4XX_IRQ_TIM5                    50
#define STM32F4XX_IRQ_SPI3                    51
#define STM32F4XX_IRQ_DMA2_Stream0            56
#define STM32F4XX_IRQ_DMA2_Stream1            57
#define STM32F4XX_IRQ_DMA2_Stream2            58
#define STM32F4XX_IRQ_DMA2_Stream3            59
#define STM32F4XX_IRQ_DMA2_Stream4            60
#define STM32F4XX_IRQ_OTG_FS                  67
#define STM32F4XX_IRQ_DMA2_Stream5            68
#define STM32F4XX_IRQ_DMA2_Stream6            69
#define STM32F4XX_IRQ_DMA2_Stream7            70
#define STM32F4XX_IRQ_USART6                  71
#define STM32F4XX_IRQ_I2C3_EV                 72
#define STM32F4XX_IRQ_I2C3_ER                 73
#define STM32F4XX_IRQ_FPU                     81
#if defined(STM32F4XX_FAMILY_STM32F401xx)
#define STM32F4XX_IRQ_SPI4                    84
#define BSP_INTERRUPT_VECTOR_MAX STM32F4XX_IRQ_SPI4
#endif
#if defined(STM32F4XX_FAMILY_STM32F411xE)
#define STM32F4XX_IRQ_SPI4                    84
#define STM32F4XX_IRQ_SPI5                    85
#define BSP_INTERRUPT_VECTOR_MAX STM32F4XX_IRQ_SPI5
#endif
#endif
//STM32F4XX_FAMILY_STM32F410xx used std version 1.6.1,but STM32F4XX_FAMILY_STM32F429_439xx used std version 1.8.0
#if defined(STM32F4XX_FAMILY_STM32F410xx) || defined(STM32F4XX_FAMILY_STM32F469_479xx)
#define STM32F4XX_IRQ_CAN1_TX                 19
#define STM32F4XX_IRQ_CAN1_RX0                20
#define STM32F4XX_IRQ_CAN1_RX1                21
#define STM32F4XX_IRQ_CAN1_SCE                22
#define STM32F4XX_IRQ_EXTI9_5                 23
#define STM32F4XX_IRQ_TIM1_BRK_TIM9           24
#define STM32F4XX_IRQ_TIM1_UP_TIM10           25
#define STM32F4XX_IRQ_TIM1_TRG_COM_TIM11      26
#define STM32F4XX_IRQ_TIM1_CC                 27
#define STM32F4XX_IRQ_TIM2                    28
#define STM32F4XX_IRQ_TIM3                    29
#define STM32F4XX_IRQ_TIM4                    30
#define STM32F4XX_IRQ_I2C1_EV                 31
#define STM32F4XX_IRQ_I2C1_ER                 32
#define STM32F4XX_IRQ_I2C2_EV                 33
#define STM32F4XX_IRQ_I2C2_ER                 34
#define STM32F4XX_IRQ_SPI1                    35
#define STM32F4XX_IRQ_SPI2                    36
#define STM32F4XX_IRQ_USART1                  37
#define STM32F4XX_IRQ_USART2                  38
#define STM32F4XX_IRQ_USART3                  39
#define STM32F4XX_IRQ_EXTI15_10               40
#define STM32F4XX_IRQ_RTC_Alarm               41
#define STM32F4XX_IRQ_OTG_FS_WKUP             42
#define STM32F4XX_IRQ_TIM8_BRK_TIM12          43
#define STM32F4XX_IRQ_TIM8_UP_TIM13           44
#define STM32F4XX_IRQ_TIM8_TRG_COM_TIM14      45
#define STM32F4XX_IRQ_TIM8_CC                 46
#define STM32F4XX_IRQ_DMA1_Stream7            47
#define STM32F4XX_IRQ_FMC                     48
#define STM32F4XX_IRQ_SDIO                    49
#define STM32F4XX_IRQ_TIM5                    50
#define STM32F4XX_IRQ_SPI3                    51
#define STM32F4XX_IRQ_UART4                   52
#define STM32F4XX_IRQ_UART5                   53
#define STM32F4XX_IRQ_TIM6_DAC                54
#define STM32F4XX_IRQ_TIM7                    55
#define STM32F4XX_IRQ_DMA2_Stream0            56
#define STM32F4XX_IRQ_DMA2_Stream1            57
#define STM32F4XX_IRQ_DMA2_Stream2            58
#define STM32F4XX_IRQ_DMA2_Stream3            59
#define STM32F4XX_IRQ_DMA2_Stream4            60
#define STM32F4XX_IRQ_ETH                     61
#define STM32F4XX_IRQ_ETH_WKUP                62
#define STM32F4XX_IRQ_CAN2_TX                 63
#define STM32F4XX_IRQ_CAN2_RX0                64
#define STM32F4XX_IRQ_CAN2_RX1                65
#define STM32F4XX_IRQ_CAN2_SCE                66
#define STM32F4XX_IRQ_OTG_FS                  67
#define STM32F4XX_IRQ_DMA2_Stream5            68
#define STM32F4XX_IRQ_DMA2_Stream6            69
#define STM32F4XX_IRQ_DMA2_Stream7            70
#define STM32F4XX_IRQ_USART6                  71
#define STM32F4XX_IRQ_I2C3_EV                 72
#define STM32F4XX_IRQ_I2C3_ER                 73
#define STM32F4XX_IRQ_OTG_HS_EP1_OUT          74
#define STM32F4XX_IRQ_OTG_HS_EP1_IN           75
#define STM32F4XX_IRQ_OTG_HS_WKUP             76
#define STM32F4XX_IRQ_OTG_HS                  77
#define STM32F4XX_IRQ_DCMI                    78
#define STM32F4XX_IRQ_CRYP                    79
#define STM32F4XX_IRQ_HASH_RNG                80
#define STM32F4XX_IRQ_FPU                     81
#define STM32F4XX_IRQ_UART7                   82
#define STM32F4XX_IRQ_UART8                   83
#define STM32F4XX_IRQ_SPI4                    84
#define STM32F4XX_IRQ_SPI5                    85
#define STM32F4XX_IRQ_SPI6                    86
#define STM32F4XX_IRQ_SAI1                    87
#define STM32F4XX_IRQ_LTDC                    88
#define STM32F4XX_IRQ_LTDC_ER                 89
#define STM32F4XX_IRQ_DMA2D                   90
#define STM32F4XX_IRQ_QUADSPI                 91
#define STM32F4XX_IRQ_DSI                     92
#define BSP_INTERRUPT_VECTOR_MAX STM32F4XX_IRQ_DSI
#endif

#if defined(STM32F4XX_FAMILY_STM32F446xx)
#define STM32F4XX_IRQ_CAN1_TX                 19
#define STM32F4XX_IRQ_CAN1_RX0                20
#define STM32F4XX_IRQ_CAN1_RX1                21
#define STM32F4XX_IRQ_CAN1_SCE                22
#define STM32F4XX_IRQ_EXTI9_5                 23
#define STM32F4XX_IRQ_TIM1_BRK_TIM9           24
#define STM32F4XX_IRQ_TIM1_UP_TIM10           25
#define STM32F4XX_IRQ_TIM1_TRG_COM_TIM11      26
#define STM32F4XX_IRQ_TIM1_CC                 27
#define STM32F4XX_IRQ_TIM2                    28
#define STM32F4XX_IRQ_TIM3                    29
#define STM32F4XX_IRQ_TIM4                    30
#define STM32F4XX_IRQ_I2C1_EV                 31
#define STM32F4XX_IRQ_I2C1_ER                 32
#define STM32F4XX_IRQ_I2C2_EV                 33
#define STM32F4XX_IRQ_I2C2_ER                 34
#define STM32F4XX_IRQ_SPI1                    35
#define STM32F4XX_IRQ_SPI2                    36
#define STM32F4XX_IRQ_USART1                  37
#define STM32F4XX_IRQ_USART2                  38
#define STM32F4XX_IRQ_USART3                  39
#define STM32F4XX_IRQ_EXTI15_10               40
#define STM32F4XX_IRQ_RTC_Alarm               41
#define STM32F4XX_IRQ_OTG_FS_WKUP             42
#define STM32F4XX_IRQ_TIM8_BRK                43
#define STM32F4XX_IRQ_TIM8_BRK_TIM12          43
#define STM32F4XX_IRQ_TIM8_UP_TIM13           44
#define STM32F4XX_IRQ_TIM8_TRG_COM_TIM14      45
#define STM32F4XX_IRQ_DMA1_Stream7            47
#define STM32F4XX_IRQ_FMC                     48
#define STM32F4XX_IRQ_SDIO                    49
#define STM32F4XX_IRQ_TIM5                    50
#define STM32F4XX_IRQ_SPI3                    51
#define STM32F4XX_IRQ_UART4                   52
#define STM32F4XX_IRQ_UART5                   53
#define STM32F4XX_IRQ_TIM6_DAC                54
#define STM32F4XX_IRQ_TIM7                    55
#define STM32F4XX_IRQ_DMA2_Stream0            56
#define STM32F4XX_IRQ_DMA2_Stream1            57
#define STM32F4XX_IRQ_DMA2_Stream2            58
#define STM32F4XX_IRQ_DMA2_Stream3            59
#define STM32F4XX_IRQ_DMA2_Stream4            60
#define STM32F4XX_IRQ_CAN2_TX                 63
#define STM32F4XX_IRQ_CAN2_RX0                64
#define STM32F4XX_IRQ_CAN2_RX1                65
#define STM32F4XX_IRQ_CAN2_SCE                66
#define STM32F4XX_IRQ_OTG_FS                  67
#define STM32F4XX_IRQ_DMA2_Stream5            68
#define STM32F4XX_IRQ_DMA2_Stream6            69
#define STM32F4XX_IRQ_DMA2_Stream7            70
#define STM32F4XX_IRQ_USART6                  71
#define STM32F4XX_IRQ_I2C3_EV                 72
#define STM32F4XX_IRQ_I2C3_ER                 73
#define STM32F4XX_IRQ_OTG_HS_EP1_OUT          74
#define STM32F4XX_IRQ_OTG_HS_EP1_IN           75
#define STM32F4XX_IRQ_OTG_HS_WKUP             76
#define STM32F4XX_IRQ_OTG_HS                  77
#define STM32F4XX_IRQ_DCMI                    78
#define STM32F4XX_IRQ_FPU                     81
#define STM32F4XX_IRQ_SPI4                    84
#define STM32F4XX_IRQ_SAI1                    87
#define STM32F4XX_IRQ_SAI2                    91
#define STM32F4XX_IRQ_QUADSPI                 92
#define STM32F4XX_IRQ_CEC                     93
#define STM32F4XX_IRQ_SPDIF_RX                94
#define STM32F4XX_IRQ_FMPI2C1_EV              95
#define STM32F4XX_IRQ_FMPI2C1_ER              96
#define BSP_INTERRUPT_VECTOR_MAX STM32F4XX_IRQ_FMPI2C1_ER
#endif

#define STM32F4XX_IRQ_PRIORITY_VALUE_MIN 0
#define STM32F4XX_IRQ_PRIORITY_VALUE_MAX 15
#define STM32F4XX_IRQ_PRIORITY_COUNT (STM32F4XX_IRQ_PRIORITY_VALUE_MAX + 1)
#define STM32F4XX_IRQ_PRIORITY_HIGHEST STM32F4XX_IRQ_PRIORITY_VALUE_MIN
#define STM32F4XX_IRQ_PRIORITY_LOWEST STM32F4XX_IRQ_PRIORITY_VALUE_MAX

#endif /* LIBBSP_ARM_STM32F4XX_IRQ_H */
