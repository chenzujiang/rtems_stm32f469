#include "./lv_tft.h"
#include <bsp/library/stm32f4xx.h>
#include <bsp/library/stm324x9i_eval_lcd.h>

/* ��غ궨�壬ʹ�ô洢�����洢���������ʹ��DMA2 */
#define DMA_STREAM               DMA2_Stream0
#define DMA_CHANNEL              DMA_Channel_0
#define DMA_STREAM_CLOCK         RCC_AHB1Periph_DMA2 
#define DMA_FLAG_TCIF            DMA_FLAG_TCIF0


static __IO uint16_t * my_fb = (__IO uint16_t*) (LCD_FRAME_BUFFER);


static void DMA_Config(void)
{
  DMA_InitTypeDef  DMA_InitStructure;
    
  /* ʹ��DMAʱ�� */
  RCC_AHB1PeriphClockCmd(DMA_STREAM_CLOCK, ENABLE);
  
  /* ��λ��ʼ��DMA����� */
  DMA_DeInit(DMA_STREAM);

  /* ȷ��DMA�������λ��� */
  while (DMA_GetCmdStatus(DMA_STREAM) != DISABLE)
  {
  }
  
  /* DMA�����ͨ��ѡ�� */
  DMA_InitStructure.DMA_Channel = DMA_CHANNEL;  
  /* �洢�����洢��ģʽ */
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToMemory;
  /* ʹ���Զ��������� */
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
  /* ʹ���Զ��������� */
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  /* Դ������ִ�С(32λ) */
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  /* Ŀ�����Ҳ���ִ�С(32λ) */
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  /* һ�δ���ģʽ���洢�����洢��ģʽ����ʹ��ѭ������ */
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  /* DMA��������ȼ�Ϊ�� */
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  /* ����FIFOģʽ */
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;     
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  /* ����ģʽ */
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  /* ����ģʽ */
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  /* ���DMA������������� */
  DMA_Init(DMA_STREAM, &DMA_InitStructure);
  
  /* ���DMA�����������ɱ�־λ */
  DMA_ClearFlag(DMA_STREAM,DMA_FLAG_TCIF);
  
}

/**
 * ��ʼ����ʾ�豸������lvgl
 * @param ��
 * @return ��
 */
void lv_tft_init(void)
{
	lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);
	
//	DMA_Config();
	
	disp_drv.disp_flush = lv_tft_flush;
	disp_drv.disp_fill = lv_tft_fill;
	disp_drv.disp_map = lv_tft_map;
//#if USE_LV_GPU
//	disp_drv.mem_blend = gpu_mem_blend;
//	disp_drv.mem_fill = gpu_mem_fill;
//#endif	
	lv_disp_drv_register(&disp_drv);
}

/**
 * ��ɫ��ˢ����Ļָ����������lvgl
 * @param ������߿����꣬x1
 * @param �����ұ߿����꣬x2
 * @param �����ϱ߿����꣬y1
 * @param �����±߿����꣬y2
 * @param color_p ָ��һ����ɫ����
 * @return ��
 */
void lv_tft_flush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p)
{

	/* �����ü��ٷ��� */	

	if(x2 < 0) return;
	if(y2 < 0) return;
	if(x1 > LV_HOR_RES - 1) return;
	if(y1 > LV_VER_RES - 1) return;

	/*Truncate the area to the screen*/
	int32_t act_x1 = x1 < 0 ? 0 : x1;
	int32_t act_y1 = y1 < 0 ? 0 : y1;
	int32_t act_x2 = x2 > LV_HOR_RES - 1 ? LV_HOR_RES - 1 : x2;
	int32_t act_y2 = y2 > LV_VER_RES - 1 ? LV_VER_RES - 1 : y2;
	
	uint32_t y;
	for(y = act_y1; y <= act_y2; y++) {
		memcpy((void*)&my_fb[y * LV_HOR_RES + act_x1],
				color_p,
				(act_x2 - act_x1 + 1) * sizeof(my_fb[0]));
		color_p += x2 - x1 + 1;    /*Skip the parts out of the screen*/
	}
	
	/* ����DMA���٣�δʵ�֣�ԭ���� */
//	DMA_InitTypeDef  DMA_InitStructure;
//	/* Դ��ݵ�ַ */
//  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)color_p;
//  /* Ŀ���ַ */
//  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)LCD_FRAME_BUFFER;	
//	/* �����Ŀ */
//  DMA_InitStructure.DMA_BufferSize = (uint32_t)(sizeof(color_p)/2);
//	/* ���DMA������������� */
//	DMA_Init(DMA_STREAM, &DMA_InitStructure);
//	/* ���DMA�����������ɱ�־λ */
//  DMA_ClearFlag(DMA_STREAM,DMA_FLAG_TCIF);
//	/* ʹ��DMA���������ʼDMA��ݴ��� */
//  DMA_Cmd(DMA_STREAM, ENABLE);
//	
//	 /* �ȴ�DMA������� */
//  while(DMA_GetFlagStatus(DMA_STREAM,DMA_FLAG_TCIF)==DISABLE)
//  {
//    
//  } 

/* ����GPU���� */
//	uint16_t offline;
//	uint32_t  Xaddress = 0;

//	offline=LCD_PIXEL_WIDTH-(x2-x1+1);
//	Xaddress = LCD_FRAME_BUFFER + 2*(LCD_PIXEL_WIDTH*y1 + x1);
//	/* configure DMA2D */
//	DMA2D->CR&=~(DMA2D_CR_START);	//��ֹͣDMA2D
//	DMA2D->CR=DMA2D_M2M;			//�洢�����洢��ģʽ
//	DMA2D->FGPFCCR=DMA2D_RGB565;	//������ɫ��ʽ
//	DMA2D->FGOR=0;					//ǰ������ƫ��Ϊ0
//	DMA2D->OOR=offline;				//������ƫ�� 

//	DMA2D->FGMAR=(u32)color_p;		//Դ��ַ
//	DMA2D->OMAR=Xaddress;				//����洢����ַ
//	DMA2D->NLR=(y2-y1+1)|((x2-x1+1)<<16);	//�趨����Ĵ��� 
//	DMA2D->CR|=DMA2D_CR_START;					//����DMA2D
//	while((DMA2D->ISR&(DMA2D_FLAG_TC))==0)		//�ȴ������
//	{
//		
//	} 

 
	lv_flush_ready();
}

/**
 * ��ָ����ɫ�����Ļ�趨��������lvgl
 * @param ��
 * @return ��
 */
void lv_tft_fill(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t color)
{
	LCD_SetTextColor(color.full);
	LCD_DrawFullRect(x1,y1,x2-x1+1,y2-y1+1);
}

/**
 * ��ʼ����ʾ�豸������lvgl
 * @param ��
 * @return ��
 */
void lv_tft_map(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_p)
{

/* �����ü��ٷ��� */	
	if(x2 < 0) return;
	if(y2 < 0) return;
	if(x1 > LV_HOR_RES - 1) return;
	if(y1 > LV_VER_RES - 1) return;

	/*Truncate the area to the screen*/
	int32_t act_x1 = x1 < 0 ? 0 : x1;
	int32_t act_y1 = y1 < 0 ? 0 : y1;
	int32_t act_x2 = x2 > LV_HOR_RES - 1 ? LV_HOR_RES - 1 : x2;
	int32_t act_y2 = y2 > LV_VER_RES - 1 ? LV_VER_RES - 1 : y2;
	
	uint32_t y;
	for(y = act_y1; y <= act_y2; y++) {
		memcpy((void*)&my_fb[y * LV_HOR_RES + act_x1],
				color_p,
				(act_x2 - act_x1 + 1) * sizeof(my_fb[0]));
		color_p += x2 - x1 + 1;    /*Skip the parts out of the screen*/
	}

	/* ����DMA���٣�δʵ�֣�ԭ���� */
//	DMA_InitTypeDef  DMA_InitStructure;
//	/* Դ��ݵ�ַ */
//  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)color_p;
//  /* Ŀ���ַ */
//  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)LCD_FRAME_BUFFER;	
//	/* �����Ŀ */
//  DMA_InitStructure.DMA_BufferSize = (uint32_t)(sizeof(color_p)/2);
//	/* ���DMA������������� */
//	DMA_Init(DMA_STREAM, &DMA_InitStructure);
//	/* ���DMA�����������ɱ�־λ */
//  DMA_ClearFlag(DMA_STREAM,DMA_FLAG_TCIF);
//	/* ʹ��DMA���������ʼDMA��ݴ��� */
//  DMA_Cmd(DMA_STREAM, ENABLE);
//	 /* �ȴ�DMA������� */
//  while(DMA_GetFlagStatus(DMA_STREAM,DMA_FLAG_TCIF)==DISABLE)
//  {
//    
//  } 

/* ����GPU���� */

//	uint16_t offline;
//	uint32_t  Xaddress = 0;

//	offline=LCD_PIXEL_WIDTH-(x2-x1+1);
//	Xaddress = LCD_FRAME_BUFFER + 2*(LCD_PIXEL_WIDTH*y1 + x1);
//	/* configure DMA2D */
//	DMA2D->CR&=~(DMA2D_CR_START);	//��ֹͣDMA2D
//	DMA2D->CR=DMA2D_M2M;			//�洢�����洢��ģʽ
//	DMA2D->FGPFCCR=DMA2D_RGB565;	//������ɫ��ʽ
//	DMA2D->FGOR=0;					//ǰ������ƫ��Ϊ0
//	DMA2D->OOR=offline;				//������ƫ�� 

//	DMA2D->FGMAR=(u32)color_p;		//Դ��ַ
//	DMA2D->OMAR=Xaddress;				//����洢����ַ
//	DMA2D->NLR=(y2-y1+1)|((x2-x1+1)<<16);	//�趨����Ĵ��� 
//	DMA2D->CR|=DMA2D_CR_START;					//����DMA2D
//	while((DMA2D->ISR&(DMA2D_FLAG_TC))==0)		//�ȴ������
//	{
//		
//	} 
}

#if USE_LV_GPU != 0

/**
 * Copy pixels to destination memory using opacity
 * @param dest a memory address. Copy 'src' here.
 * @param src pointer to pixel map. Copy it to 'dest'.
 * @param length number of pixels in 'src'
 * @param opa opacity (0, OPA_TRANSP: transparent ... 255, OPA_COVER, fully cover)
 */
static void gpu_mem_blend(lv_color_t * dest, const lv_color_t * src, uint32_t length, lv_opa_t opa)
{

}

/**
 * Copy pixels to destination memory using opacity
 * @param dest a memory address. Copy 'src' here.
 * @param src pointer to pixel map. Copy it to 'dest'.
 * @param length number of pixels in 'src'
 * @param opa opacity (0, OPA_TRANSP: transparent ... 255, OPA_COVER, fully cover)
 */
static void gpu_mem_fill(lv_color_t * dest, uint32_t length, lv_color_t color)
{

}

#endif

