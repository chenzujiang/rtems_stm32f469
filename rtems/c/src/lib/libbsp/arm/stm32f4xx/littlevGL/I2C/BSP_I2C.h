#ifndef __BSP_I2C_H
#define __BSP_I2C_H

//#include "stm32f4xx.h"
#include <bsp/library/stm32f4xx.h>
/*PB8=>SCL PB9=>SDA*/

#define IIC_SCL_H	GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define IIC_SCL_L	GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define IIC_SDA_H	GPIO_SetBits(GPIOB,GPIO_Pin_9)
#define IIC_SDA_L	GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define IIC_SDA_IN	(GPIOB->IDR&GPIO_Pin_9)
#define IIC_SDA_MODE_IN (GPIOB->MODER&=~(3<<18))
#define IIC_SDA_MODE_OUT (GPIOB->MODER|=1<<18)

void BSP_I2C_Init(void);
u8 I2C_Write(u8 IIC_Adr,u8 address,u8 data);
u8 I2C_Read(u8 IIC_Adr,u8 address);
u8 I2C_Writes(u8 IIC_Adr,u8 *buff,u8 address,u8 length);
u8 I2C_Reads(u8 IIC_Adr,u8 address,u8 *buff,u8 length);


#endif

