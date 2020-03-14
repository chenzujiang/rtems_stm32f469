/* BSP dependent options file */
/* automatically generated -- DO NOT EDIT!! */

#ifndef __BSP_OPTIONS_H
#define __BSP_OPTIONS_H

/* include/bspopts.tmp.  Generated from bspopts.h.in by configure.  */
/* include/bspopts.h.in.  Generated from configure.ac by autoheader.  */

/* If defined, then the BSP Framework will put a non-zero pattern into the
   RTEMS Workspace and C program heap. This should assist in finding code that
   assumes memory starts set to zero. */
#define BSP_DIRTY_MEMORY 0

/* If defined, print a message and wait until pressed before resetting board
   when application exits. */
#define BSP_PRESS_KEY_FOR_RESET 0

/* If defined, prints the exception context when an unexpected exception
   occurs. */
/* #undef BSP_PRINT_EXCEPTION_CONTEXT */

/* If defined, reset the board when the application exits. */
#define BSP_RESET_BOARD_AT_EXIT 0







/* enable EXTI 0 */
#define STM32F4XX_ENABLE_EXTI0 1

/* enable EXTI 13 */
/* #undef STM32F4XX_ENABLE_EXTI13 */

/* enable I2C 1 */
#define STM32F4XX_ENABLE_I2C1 1

/* enable lED 1 */
#define STM32F4XX_ENABLE_LED_1 1

/* enable lED 2 */
#define STM32F4XX_ENABLE_LED_2 1

/* enable lED 3 */
#define STM32F4XX_ENABLE_LED_3 1

/* enable lED 4 */
#define STM32F4XX_ENABLE_LED_4 1

/* enable SPI 5 */
/* #undef STM32F4XX_ENABLE_SPI5 */

/* enable UART 4 */
/* #undef STM32F4XX_ENABLE_UART_4 */

/* enable UART 5 */
/* #undef STM32F4XX_ENABLE_UART_5 */

/* enable UART 7 */
/* #undef STM32F4XX_ENABLE_UART_7 */

/* enable UART 8 */
/* #undef STM32F4XX_ENABLE_UART_8 */

/* enable USART 1 */
/* #undef STM32F4XX_ENABLE_USART_1 */

/* enable USART 2 */
/* #undef STM32F4XX_ENABLE_USART_2 */

/* enable USART 3 */
#define STM32F4XX_ENABLE_USART_3 1

/* enable USART 6 */
#define STM32F4XX_ENABLE_USART_6 1

/* STM32F4 STM32F40_41xxx Family */
/* #undef STM32F4XX_FAMILY_STM32F40_41xxx */

/* STM32F4 STM32F429_439xx Family */
/* #undef STM32F4XX_FAMILY_STM32F429_439xx */

/* STM32F4 STM32F469_479xx Family */
#define STM32F4XX_FAMILY_STM32F469_479xx 1

/* HSE oscillator frequency in Hz */
#define STM32F4XX_HSE_OSCILLATOR 8000000

/* HSE oscillator startup timeout */
#define STM32F4XX_HSE_STARTUP_TIMEOUT 0x05000

/* HSI oscillator frequency in Hz */
#define STM32F4XX_HSI_OSCILLATOR 16000000

/* HCLK frequency in Hz */
#define STM32F4_HCLK 180000000

/* PCLK1 frequency in Hz */
#define STM32F4_PCLK1 45000000

/* PCLK2 frequency in Hz */
#define STM32F4_PCLK2 90000000

/* SYSCLK frequency in Hz */
#define STM32F4_SYSCLK 180000000

/* baud for USARTs */
#define STM32F4_USART_BAUD 115200

#endif /* __BSP_OPTIONS_H */
