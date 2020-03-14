#include "system.h"

void thread_card(rtems_task_argument arg)
{
	  /* SD Init*/
	  Status = SD_Init();//task less
	  if(Status== SD_OK)
	      printf( " \r\n SD_Init successful!!!!\r\n ");
	  else
		  printf( " \r\n SD_Init FAILE!!!!\r\n ");
	  /* ²Á³ý²âÊÔ */
	  	SD_EraseTest();

	    /* µ¥¿é¶ÁÐ´²âÊÔ */
	  	SD_SingleBlockTest();

	  	/* ¶à¿é¶ÁÐ´²âÊÔ */
	  	SD_MultiBlockTest();

	for ( ; ; ) {
		//printf("sd-card while\r\n");
		rtems_task_wake_after(5000);
	}
}
