#ifndef __STM32F4xx_DRIVER_CONF_H
#define __STM32F4xx_DRIVER_CONF_H

#include <bspopts.h>

#if defined(STM32F4XX_FAMILY_STM32F40_41xxx)
 #define STM32F40_41xxx
#elif defined(STM32F4XX_FAMILY_STM32F427_437xx)
 #define STM32F427_437xx
#elif defined(STM32F4XX_FAMILY_STM32F429_439xx)
 #define STM32F429_439xx
#elif defined(STM32F4XX_FAMILY_STM32F401xx)
 #define STM32F401xx
#elif defined(STM32F4XX_FAMILY_STM32F410xx)
 #define STM32F410xx
#elif defined(STM32F4XX_FAMILY_STM32F411xE)
 #define STM32F411xE
#elif defined(STM32F4XX_FAMILY_STM32F446xx)
 #define STM32F446xx
#elif defined(STM32F4XX_FAMILY_STM32F469_479xx)
 #define STM32F469_479xx 
#else
 #error "Please select target STM32F4xx device used in your application (in stm32f4xx.h file)"
#endif

#define USE_STDPERIPH_DRIVER
#define HSE_STARTUP_TIMEOUT ((uint16_t)STM32F4XX_HSE_STARTUP_TIMEOUT)
#define HSE_VALUE ((uint32_t)STM32F4XX_HSE_OSCILLATOR)
#define HSI_VALUE ((uint32_t)STM32F4XX_HSI_OSCILLATOR)

#endif /* __STM32F4xx_DRIVER_CONF_H */
