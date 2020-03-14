#include "./BSP_I2C.h"
void IIC_Delay(void)
{
	vu32 IIC_Step=20;
	while(IIC_Step--);
}
static int I2C_INIT_FLAG=0;

void BSP_I2C_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	if(I2C_INIT_FLAG != 0)
		return;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	IIC_SDA_H;IIC_SCL_H;
	I2C_INIT_FLAG=1;
	
}

u8 IIC_Start(void)
{
	IIC_SDA_H;
	IIC_SCL_H;
	IIC_Delay();
//	if(!IIC_SDA_IN) return 0;//SDA��Ϊ�͵�ƽ������æ,�˳�
	IIC_SDA_L;
//	IIC_Delay();
//	IIC_SCL_L;
	return 1;
}
void IIC_Stop(void)
{
	IIC_SDA_L;
	IIC_SCL_H;
	IIC_Delay();
	IIC_SDA_H;
}
void IIC_Ack(void)
{
	IIC_SDA_L;
	IIC_Delay();
	IIC_SCL_H;
	IIC_Delay();
	IIC_SCL_L;
	IIC_Delay();
}
void IIC_NAck(void)
{
	IIC_SDA_H;
	IIC_Delay();
	IIC_SCL_H;
	IIC_Delay();
	IIC_SCL_L;
	IIC_Delay();
}
u8 IIC_WaitAck(void)
{
	IIC_SDA_H;
	IIC_Delay();
	IIC_SCL_H;
	IIC_Delay();
	if(IIC_SDA_IN)
	{
		IIC_SCL_L;
		return 0;
	}
	IIC_SCL_L;
	return 1;
}
void IIC_SendByte(u8 SendByte) //��ݴӸ�λ����λ
{
	u8 i=8;
	while(i--)
	{
		IIC_SCL_L;
		IIC_Delay();
		if(SendByte&0x80)
			IIC_SDA_H;
		else
			IIC_SDA_L;
		SendByte<<=1;
//		IIC_Delay();
		IIC_SCL_H;
		IIC_Delay();
	}
	IIC_SCL_L;
}
u8 IIC_ReceiveByte(void)  //��ݴӸ�λ����λ//
{
	u8 i=8;
	u8 ReceiveByte=0;

	IIC_SDA_H;
	while(i--)
	{
		ReceiveByte<<=1;
		IIC_SCL_L;
		IIC_Delay();
		IIC_SCL_H;
		IIC_Delay();
		if(IIC_SDA_IN)
		{
			ReceiveByte|=0x01;
		}
	}
	IIC_SCL_L;
	return ReceiveByte;
}
u8 I2C_Write(u8 IIC_Adr,u8 address,u8 val)
{
	IIC_Start();
	IIC_SendByte(IIC_Adr);//����������ַ
	IIC_Ack();
	IIC_SendByte(address);   //���õ���ʼ��ַ
	IIC_Ack();
	IIC_SendByte(val);
	IIC_Ack();
	IIC_Stop();
	//ע�⣺��Ϊ����Ҫ�ȴ�EEPROMд�꣬���Բ��ò�ѯ����ʱ��ʽ(10ms)
	//delay_ms(10);
	return 1;
}

u8 I2C_Read(u8 IIC_Adr,u8 address)//���ֽ�
{
	u8 temp=0;
	IIC_Start();
	IIC_SendByte(IIC_Adr);//����������ַ
	IIC_Ack();
	IIC_SendByte(address);   //���õ���ʼ��ַ
	IIC_Ack();
	IIC_Start();
	IIC_SendByte(IIC_Adr|0x01);//����������ַ
	IIC_Ack();
	temp=IIC_ReceiveByte();
	IIC_NAck();
	IIC_Stop();
	return temp;
}
u8 I2C_Writes(u8 IIC_Adr,u8 *buff,u8 address,u8 length)
{
	if(!IIC_Start())
		return 0;
	IIC_SendByte(IIC_Adr);//����������ַ 
	if(!IIC_WaitAck())
	{
		IIC_Stop(); 
		return 0;
	}
	IIC_SendByte(address);   //���õ���ʼ��ַ      
	IIC_WaitAck();
	while(length--)
	{
		IIC_SendByte(*buff);
		IIC_WaitAck();
		buff++;
	}       
	IIC_Stop(); 
	//ע�⣺��Ϊ����Ҫ�ȴ�EEPROMд�꣬���Բ��ò�ѯ����ʱ��ʽ(10ms)
	//delay_ms(10);
	return 1;   
}
u8 I2C_Reads(u8 IIC_Adr,u8 address,u8 *buff,u8 length)//���ַ�
{
	IIC_Start();
    IIC_SendByte(IIC_Adr);//����������ַ
	IIC_WaitAck();
    IIC_SendByte(address);   //���õ���ʼ��ַ      
    IIC_WaitAck();
    IIC_Start();
    IIC_SendByte(IIC_Adr|0x01);//����������ַ
    IIC_WaitAck();
	while(length)
	{
		*buff=IIC_ReceiveByte();
		if(length==1)
			IIC_NAck();
		else
			IIC_Ack();
		buff++;
		length--;
	}
    IIC_Stop();
    return 1;    
}
