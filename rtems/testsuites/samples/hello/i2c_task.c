#include "system.h"
void thread_i2c(
  rtems_task_argument unused
)
{
//  char writebuf[]="welcome to rtems on stm32f429igt6-ARM-I2C";
//  char readbuf[64]={0};
//
//  int fd = open("/dev/i2c1", O_RDWR);
//
//  printk("-stm32f4 i2c1 read write test-%d\r\n",fd);
//  write(fd,writebuf,sizeof(writebuf));
//  close(fd);
//  open("/dev/i2c1", O_RDWR);
//  read(fd,readbuf,sizeof(writebuf));
//  printk("-------readbuf %s\r\n",readbuf);
  while(1)
  {
  	rtems_task_wake_after(1000);
  	printf("this is i2c thread\r\n");
  }
}
