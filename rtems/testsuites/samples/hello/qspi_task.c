#include "system.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BUFFER_SIZE         ((uint32_t)0x0100)
#define WRITE_READ_ADDR     ((uint32_t)0x0800)

/* Status variables */
__IO uint32_t uwWriteReadStatus = 0;

/* Counter index */
uint32_t uwIndex = 0;

void thread_qspi(rtems_task_argument arg)
{
	  /* Private macro -------------------------------------------------------------*/
	  /* Private variables ---------------------------------------------------------*/
	  /* Read/Write Buffers */
	  uint32_t aTxBuffer[BUFFER_SIZE];
	  uint32_t aRxBuffer[BUFFER_SIZE];

	  /* Fill the buffer to write */
	  Fill_Buffer(aTxBuffer, BUFFER_SIZE, 0x250F);
	  /* Write data to the SDRAM memory */
	  SDRAM_WriteBuffer(aTxBuffer, WRITE_READ_ADDR, BUFFER_SIZE);

	  /* Read back data from the SDRAM memory */
	  SDRAM_ReadBuffer(aRxBuffer, WRITE_READ_ADDR, BUFFER_SIZE);

	  /* Check the SDRAM memory content's correctness */
	  for (uwIndex = 0; (uwIndex < BUFFER_SIZE) && (uwWriteReadStatus == 0); uwIndex++)
	  {
	    if (aRxBuffer[uwIndex] != aTxBuffer[uwIndex])
	    {
	      uwWriteReadStatus++;
	    }
	  }
	  if (uwWriteReadStatus)
	  {
		  printf("test ko \r\n");
	  }
	  else
	  {
	    printf("test ok \r\n");
	  }

    qspi_conf();
    printf( " \r\n QSPI_Read_Write_Test!!!!\r\n ");
    printf("qspi read write\r\n");
    QSPI_Read_Write_Test();
	for ( ; ; ) {

		 rtems_task_wake_after(10000);
	}
}
