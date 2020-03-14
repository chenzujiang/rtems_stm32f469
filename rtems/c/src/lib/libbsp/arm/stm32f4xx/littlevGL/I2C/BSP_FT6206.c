#include "./BSP_FT6206.h"
#include <bsp/library/stm32f4xx_it.h>
#include <bsp/library/stm32f4xx.h>
#include <bsp/library/stm324x9i_eval_ioe8.h>
#include <bsp.h>
#include <bsp/irq.h>
#include <bsp/irq-generic.h>
 uint16_t touch_x;
 uint16_t touch_y;
 uint16_t touch_w;
 uint8_t is_touch;
/* FT6206 Chip address */
#define FT6206_I2C_ADDRESS 0x54

int BSP_FT6206_Init(void)
{
	IOE_I2C_Config();
	
	if(I2C_ReadDeviceRegister(FT6206_CHIP_ID_REG) == FT6206_ID_VALUE )
	{
		I2C_WriteDeviceRegister(FT6206_GMODE_REG,0x00);
		return 0;
	}
	else
	{
		printk("\r\n bsp_ft62006 --1\r\n");
		return 1;
	}
}
/*******************************************************************************
* ��    ��: 
* ��ڲ���: 
* ���ڲ���: ��
* �� �� ֵ: ��
* ˵    ����
*******************************************************************************/
static void FT6206_INT_gpio_configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOJ, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOJ, &GPIO_InitStructure);
}

static void exti_gpio_configuration(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOJ, EXTI_PinSource5);
	EXTI_InitStructure.EXTI_Line = EXTI_Line5;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}
static void NVIC_EXTI_TOUCH_Configuration()
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
}
#if defined(BSP_FEATURE_IRQ_EXTENSION) || \
   (CPU_SIMPLE_VECTORED_INTERRUPTS != TRUE)
void Touch_isr(void *arg)
#else
rtems_isr DSI_isr(rtems_vector_number vector)
#endif
{
	EXTI9_5_IRQHandler();
}
void FT6206_INT_conf()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	NVIC_EXTI_TOUCH_Configuration();
	FT6206_INT_gpio_configuration();
	exti_gpio_configuration();

	rtems_interrupt_handler_install(
			STM32F4XX_IRQ_EXTI9_5,
			"TOU_INI",
			RTEMS_INTERRUPT_UNIQUE,
			(rtems_interrupt_handler) Touch_isr,
			NULL);
}

int BSP_FT6205_Detect(void)
{
	return I2C_ReadDeviceRegister(FT6206_TD_STAT_REG);
}
int BSP_FT6205_GetXY(uint16_t *pTouchX,uint16_t *pTouchY)
{
	int nNumPoint;
	uint8_t FT6206_Value[8]={0};

	nNumPoint = BSP_FT6205_Detect();//��ȡ���������м�����

	if( (nNumPoint!=1) && (nNumPoint!=2))
	{
		return 0;
	}
	
	I2C_ReadDataBuffer(FT6206_P1_XH_REG,FT6206_Value,4);
    //��ȡһ����ʱ��Ӧ�ĸ��Ĵ�����ֵ->��ʾ��Ӧ������
    /* Send back ready X position to caller */
    *pTouchX = ((FT6206_Value[0] & FT6206_MSB_MASK) << 8) | (FT6206_Value[1] & FT6206_LSB_MASK);   
    /* Send back ready Y position to caller */
    *pTouchY = ((FT6206_Value[2] & FT6206_MSB_MASK) << 8) | (FT6206_Value[3] & FT6206_LSB_MASK);
	return 1;
//	if(nNumPoint==2)
//	{
//		I2C_Reads(FT6206_I2C_ADDRESS,FT6206_P2_XH_REG,FT6206_Value+4,4);
//	}
	
}

void Goodix_TS_Work_Func(void)
{   
    int nNumPoint = 0;
	uint8_t FT6206_Value[8]={0};

	nNumPoint = BSP_FT6205_Detect();//��ȡ���������м�����

    	//�жϵ�ǰ����������Ƿ���Ч
	if(0 == nNumPoint)		//û����ݣ��˳�
	{
		if(is_touch)
		{
			touch_x=0;
			touch_y=0;
			is_touch=0;
            return;
		}
        else{
           printk("no touch\r\n");
            is_touch = 0;
            return;
        }

	}
	if( (nNumPoint!=1) && (nNumPoint!=2))
	{
		return 0;
	}
	
	I2C_ReadDataBuffer(FT6206_P1_XH_REG,FT6206_Value,4);
    //��ȡһ����ʱ��Ӧ�ĸ��Ĵ�����ֵ->��ʾ��Ӧ������
        /* Send back ready X position to caller */
    touch_x = ((FT6206_Value[0] & FT6206_MSB_MASK) << 8) | (FT6206_Value[1] & FT6206_LSB_MASK);
    /* Send back ready Y position to caller */
    touch_y = ((FT6206_Value[2] & FT6206_MSB_MASK) << 8) | (FT6206_Value[3] & FT6206_LSB_MASK);
    printk("(%d,%d)\r\n",touch_x,touch_y);
	is_touch=1;
}

