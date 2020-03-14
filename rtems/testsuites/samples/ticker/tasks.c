/*  Test_task
 *
 *  This routine serves as a test task.  It verifies the basic task
 *  switching capabilities of the executive.
 *
 *  Input parameters:  NONE
 *
 *  Output parameters:  NONE
 *
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "system.h"
#include <fcntl.h>
uint8_t I2c_Buf_Write[256];
uint8_t I2c_Buf_Read[256]={0};

int Test_Func();
rtems_task Test_task(
  rtems_task_argument unused
)
{
  rtems_id          tid;
  //rtems_time_of_day time;
  //uint32_t          task_index;
  rtems_status_code status;

  status = rtems_task_ident( RTEMS_SELF, RTEMS_SEARCH_ALL_NODES, &tid );
  directive_failed( status, "task ident" ); 
  int fd = open("/dev/i2c1", O_RDWR);
  char writebuf[]="welcome to rtems on stm32f429igt6-ARM-SPI5";
  char readbuf[64]={0};

  printk("-stm32f4 i2c1 read write test-%d\r\n",fd);
  int writeCount = write(fd,writebuf,sizeof(writebuf));
  int clo = close(fd);
  printf("close file stutus %d\r\n",clo);
  open("/dev/i2c1", O_RDWR);
  int count = read(fd,readbuf,sizeof(writebuf));
  printk("readbuf %s",readbuf);


//	  int spifd = open("/dev/spi5", O_RDWR);
//
//	  printk("-stm32f4 spi5 read write test-%d\r\n",spifd);
//	  int writeCount = write(spifd,writebuf,sizeof(writebuf));
//
//	  int count_spi = read(spifd,readbuf,sizeof(writebuf));
//	  printk("readbuf111111 %s",readbuf);
	 // int clo = close(spifd);

//////////first call write then call write buf empty ->number?/////////////////
//    int i=0;
//	for (i=255; i>0; --i )
//	{
//	  I2c_Buf_Write[i] = i;
//	 }
//	printf("-----------------------------------------------\r\n");
//	  int writeCount = write(fd,I2c_Buf_Write,sizeof(I2c_Buf_Write));
//	  int clo = close(fd);
//	printf("close file stutus %d\r\n",clo);
//	open("/dev/i2c1", O_RDWR);
//	int count = read(fd,I2c_Buf_Read,sizeof(I2c_Buf_Read));
//	int statusFUNC = Test_Func();
//	if(statusFUNC !=0)
//		printf("error test");
//	else
//		printf("ok test");
//
//	close(fd);

//  task_index = task_number( tid );
//  for ( ; ; ) {
//    status = rtems_clock_get_tod( &time );
//    if ( time.second >= 35 ) {
//      TEST_END();
//      rtems_test_exit( 0 );
//    }
//    put_name( Task_name[ task_index ], FALSE );
//    print_time( " - rtems_clock_get_tod - ", &time, "\n" );
//    status = rtems_task_wake_after(
//      task_index * 5 * rtems_clock_get_ticks_per_second()
//    );
//    directive_failed( status, "wake after" );
//  }

}
int Test_Func()
{
	int i;
	for (i=0; i<256; i++)
	{
		if(I2c_Buf_Read[i] != I2c_Buf_Write[i])
		{
			printf("[ error ] 0x%02X ", I2c_Buf_Read[i]);

			return -1;
		}
	  printf("0x%02X ", I2c_Buf_Read[i]);
	  if(i%16 == 15)
		  printf("\n\r");

	}
	return 0;
}
