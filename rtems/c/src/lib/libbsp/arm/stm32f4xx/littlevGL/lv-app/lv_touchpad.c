#include "./lv_touchpad.h"
//#include "./touch/gt9xx.h"
#include "I2C/BSP_FT6206.h"
extern uint16_t touch_x=0;
extern uint16_t touch_y=0;
extern uint16_t touch_w=0;
uint8_t is_touch=0;
/**
  * @brief   ���lvgl������ʼ������
  * @param ��
  * @retval ��
  */
void lv_touchpad_init(void)
{
	lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.read = lv_touchpad_read;
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  lv_indev_drv_register(&indev_drv);
}

/**
  * @brief   ��ȡ���������㣬����lvgl
  * @param �����豸�ṹ���ַ
  * @retval false
  */
bool lv_touchpad_read(lv_indev_data_t *data)
{
	static uint16_t last_x = 0;
	static uint16_t last_y = 0;
	if(is_touch)//�а�����ʱ
	{
		data->point.x = touch_x;
		data->point.y = touch_y;
		data->state = LV_INDEV_STATE_PR;
		last_x = data->point.x;
		last_y = data->point.y;
		is_touch = 0;
	}
	else
	{		
		data->point.x = last_x;
		data->point.y = last_y;
		data->state = LV_INDEV_STATE_REL;
	}
		
	return false;
}


