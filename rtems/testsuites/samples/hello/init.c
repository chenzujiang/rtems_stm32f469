/*
 *  COPYRIGHT (c) 1989-2012.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/test.h>
//befor define
#include <bsp/library/stm32f4xx.h>
//#include <bsp/library/stm324x9i_eval_fmc_sdram.h>
#include <bsp/library/stm324x9i_eval_sdio_sd.h>
#include <bsp/library/qspi_readwrite_conf.h>
#include <bsp/library/stm324x9i_eval_ioe8.h>
#include <bsp/library/stm324x9i_eval_lcd.h>
#include <bsp/library/stm32_eval_legacy.h>
#include <bsp/library/otm8009a.h>
#include <bsp/littlevGL/bsp_general_tim.h>
#include <bsp/littlevGL/BSP_FT6206.h>

#include "../../../c/src/lib/libbsp/arm/stm32f4xx/littlevGL/lv_examples/lv_tests/lv_test_theme/lv_test_theme.h"
#include "../../../c/src/lib/libbsp/arm/stm32f4xx/littlevGL/lv_examples/lv_apps/demo/demo.h"
#include "../../../c/src/lib/libbsp/arm/stm32f4xx/littlevGL/lvgl-5.1/lv_themes/lv_theme_alien.h"

#include "../../../c/src/lib/libbsp/arm/stm32f4xx/littlevGL/lvgl-5.1/lv_themes/lv_theme.h"
#include "../../../c/src/lib/libbsp/arm/stm32f4xx/littlevGL/lvgl-5.1/lvgl.h"
#include "../../../c/src/lib/libbsp/arm/stm32f4xx/littlevGL/lvgl-5.1/lv_hal/lv_hal_disp.h"
#include "../../../c/src/lib/libbsp/arm/stm32f4xx/littlevGL/lv-app/lv_touchpad.h"
#include "../../../c/src/lib/libbsp/arm/stm32f4xx/littlevGL/lv-app/lv_tft.h"

//#include <bsp/library/bsp_sdcard.h>
//#include <bsp/library/main.h>
//#include <rtems/led-drv.h>
//#include <rtems/i2c-drv.h>
//#include <bsp/keyboard.h>
#include "system.h"
#include <bsp.h> /* for device driver prototypes */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <rtems.h>

  //1 Á½¸öÎÄ¼þÓÐÍ¬Ò»ÎÄ¼þ
  //2 ±äÁ¿ÔÚÍ·ÎÄ¼þÖÐ¶¨Òå£¬¶à´¦ÓÃ¸ÃÍ·ÎÄ¼þ
  //3 extern ±äÁ¿ºó²»Òª³õÊ¼»¯

 /* Private macro -------------------------------------------------------------*/
 /* Private variables ---------------------------------------------------------*/
 static __IO uint32_t uwTimingDelay;
 __IO uint32_t DSISync = 0;
 uint8_t reduced_table_row[4] = {0x00, 0x64, 0x01, 0x90};

const char rtems_test_name[] = "HELLO WORLD";
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
static lv_res_t btn_click_action(lv_obj_t * btn)
{
    uint8_t id = lv_obj_get_free_num(btn);

    printf("Button %d is released\n", id);

    /* The button is released.
     * Make something here */

    return LV_RES_OK; /*Return OK if the button is not deleted*/
}

void button_test(void)
{

    /*Create a title label*/
    lv_obj_t * label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, "Default buttons");
    lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);

    /*Create a normal button*/
    lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
    lv_cont_set_fit(btn1, true, true); /*Enable resizing horizontally and vertically*/
    lv_obj_align(btn1, label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    lv_obj_set_free_num(btn1, 1);   /*Set a unique number for the button*/
    lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, btn_click_action);

    /*Add a label to the button*/
    label = lv_label_create(btn1, NULL);
    lv_label_set_text(label, "Normal");

    /*Copy the button and set toggled state. (The release action is copied too)*/
    lv_obj_t * btn2 = lv_btn_create(lv_scr_act(), btn1);
    lv_obj_align(btn2, btn1, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    lv_btn_set_state(btn2, LV_BTN_STATE_TGL_REL);  /*Set toggled state*/
    lv_obj_set_free_num(btn2, 2);               /*Set a unique number for the button*/

    /*Add a label to the toggled button*/
    label = lv_label_create(btn2, NULL);
    lv_label_set_text(label, "Toggled");

    /*Copy the button and set inactive state.*/
    lv_obj_t * btn3 = lv_btn_create(lv_scr_act(), btn1);
    lv_obj_align(btn3, btn2, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    lv_btn_set_state(btn3, LV_BTN_STATE_INA);   /*Set inactive state*/
    lv_obj_set_free_num(btn3, 3);               /*Set a unique number for the button*/

    /*Add a label to the inactive button*/
    label = lv_label_create(btn3, NULL);
    lv_label_set_text(label, "Inactive");

    lv_obj_t * labelOS = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(labelOS, "RTEMS OS with littlevGL library");
    lv_obj_align(labelOS, btn3, LV_ALIGN_IN_TOP_MID, 0, 100);
}
rtems_task Init(
  rtems_task_argument ignored
)
{
  rtems_test_begin();
  rtems_id  task_led;
  rtems_id  task_i2c;
  rtems_id  task_card;
  rtems_id  task_exti;
  rtems_id  task_qspi;
  rtems_status_code	sc;
  printf("Hello, Welcome to rtems's world\r\n");
//  SysTick_Config(SystemCoreClock/ 1000);
//  rtems_interrupt_handler_install(
//		  SysTick_IRQn,
//    "SYS_INT",
//    RTEMS_INTERRUPT_UNIQUE,
//    (rtems_interrupt_handler) DSI_isr,
//    NULL);

  rtems_task_create(
               rtems_build_name('l', 'e', 'd', '1'),
               16,
			   RTEMS_MINIMUM_STACK_SIZE,
               RTEMS_PREEMPT | RTEMS_NO_TIMESLICE,
               RTEMS_LOCAL | RTEMS_NO_FLOATING_POINT,
               &task_led
    );
  rtems_task_create(
			  rtems_build_name('i', 'i', 'c', '-'),
			  9,
			  RTEMS_MINIMUM_STACK_SIZE ,
			  RTEMS_PREEMPT | RTEMS_NO_TIMESLICE | RTEMS_ASR,
			  RTEMS_DEFAULT_ATTRIBUTES,
			  &task_i2c
  );
  rtems_task_create(
			  rtems_build_name('e', 'x', 't', 'i'),
			  11,
			  RTEMS_MINIMUM_STACK_SIZE ,
			  //RTEMS_PREEMPT | RTEMS_NO_TIMESLICE,
			  RTEMS_PREEMPT | RTEMS_NO_TIMESLICE | RTEMS_ASR,
			  RTEMS_DEFAULT_ATTRIBUTES,
			  &task_exti
  );
  rtems_task_create(
			  rtems_build_name('q', 's', 'p', 'i'),
			  11,
			  RTEMS_MINIMUM_STACK_SIZE ,
			  //RTEMS_PREEMPT | RTEMS_NO_TIMESLICE,
			  RTEMS_PREEMPT | RTEMS_NO_TIMESLICE | RTEMS_ASR,
			  RTEMS_DEFAULT_ATTRIBUTES,
			  &task_qspi
  );
  rtems_task_create(
			  rtems_build_name('c', 'a', 'r', 'd'),
			  11,
			  RTEMS_MINIMUM_STACK_SIZE ,
			  RTEMS_PREEMPT | RTEMS_NO_TIMESLICE | RTEMS_ASR,
			  RTEMS_DEFAULT_ATTRIBUTES,
			  &task_card
  );
//  rtems_task_start(task_i2c, thread_i2c, 0 );//i2c touch and frame ???
  sc = rtems_task_start(task_led, thread_led, 0);
	if (sc != RTEMS_SUCCESSFUL)
	{
		printf("thread_led %d\r\n",sc);
	}

	sc =rtems_task_start(task_exti, thread_key, 0);
	if (sc != RTEMS_SUCCESSFUL)
	{
		printf("thread_key %d\r\n",sc);
	}
	sc =rtems_task_start(task_card, thread_card, 0);
	if (sc != RTEMS_SUCCESSFUL)
	{
		printf("thread_card %d\r\n",sc);
	}
	sc =rtems_task_start(task_qspi, thread_qspi, 0);
	if (sc != RTEMS_SUCCESSFUL)
	{
		printf("thread_qspi %d\r\n",sc);
	}

  /* DSI configuration */
  LCD_Init();
  /* Enable the DSI host and wrapper */
  DSI_Start(DSI);
  /* Drive the display */
#if OTM8009A_ORIENTATION
  OTM8009Setup(DSI, IMAGEFORMAT_RGB565);
  //OTM8009A_Init(OTM8009A_COLMOD_RGB565,OTM8009A_ORIENTATION_PORTRAIT);????
#else
  OTM8009A_Init(OTM8009A_COLMOD_RGB565,OTM8009A_ORIENTATION_LANDSCAPE);
#endif
  while (DSISync == 0)
  {}
  LCD_LayerInit();

  FT6206_INT_conf();
  BSP_FT6206_Init();
  TIMx_Configuration();

  LCD_SetFont(&Font16x24);
  LCD_Clear(LCD_COLOR_BLACK);
  LCD_DrawFullRect(100,100,100,100);
  LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_BLUE);
  LCD_DrawLine(500,300,300,Horizontal);
  LCD_DrawLine(100,30,500,Vertical);
  LCD_DrawFullRect(100,200,250,200);
  LCD_DisplayStringLine(LCD_LINE_2,"hello world");
  LCD_DisplayStringLine(LCD_LINE_5,"STM32F469");
  LCD_DisplayStringLine(LCD_LINE_6,"sd card driver sd card driversd card driver sd card driversd");
  LCD_DrawCircle(250,500,100);
  printf("Rtems RTOS start successful %d\r\n",sc);

  lv_init();
  Delay(0x100);

  lv_tft_init();
  lv_touchpad_init();

  //²âÊÔdemo
  button_test();
// // demo_create();
  /* Infinite loop */
  while (1)
  {
	  rtems_task_wake_after(30);
	 // Delay(30);//delay no zushe other thread
	  lv_task_handler();

//	  GPIO_ToggleBits(GPIOD, GPIO_Pin_4);
//	  GPIO_ToggleBits(GPIOD, GPIO_Pin_5);
  }
  rtems_test_end();
  exit( 0 );
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(volatile uint32_t nTime)
{
  uwTimingDelay = nTime;
  while(uwTimingDelay != 0);
}
/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (uwTimingDelay != 0x00)
  {
    uwTimingDelay--;
  }
}


/* NOTICE: the clock driver is explicitly disabled */
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER //#define CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER

#define CONFIGURE_MICROSECONDS_PER_TICK 100

#define CONFIGURE_MAXIMUM_TASKS           32
//#define CONFIGURE_FILESYSTEM_DEVFS
#define CONFIGURE_USE_MINIIMFS_AS_BASE_FILESYSTEM
//#define CONFIGURE_USE_DEVFS_AS_BASE_FILESYSTEM

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INITIAL_EXTENSIONS RTEMS_TEST_INITIAL_EXTENSION

#define CONFIGURE_ENABLE_BSP_LED_DRIVER
#define CONFIGURE_LIBIO_MAXIMUM_FILE_DESCRIPTORS 16 //open need macro
//#define	CONFIGURE_APPLICATION_EXTRA_DRIVERS
//#define CONFIGURE_ENABLE_BSP_I2C_DRIVER

#define CONFIGURE_MAXIMUM_MESSAGE_QUEUES    10

#define CONFIGURE_DISABLE_NEWLIB_REENTRANCY
#define CONFIGURE_MAXIMUM_SEMAPHORES 10
#define CONFIGURE_MINIMUM_TASK_STACK_SIZE    8*1024
//#define CONFIGURE_MAXIMUM_PRIORITY 255
#define CONFIGURE_EXECUTIVE_RAM_SIZE  40*1024
#define CONFIGURE_INIT
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#include <rtems/confdefs.h>
