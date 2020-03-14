#include "system.h"

void thread_key(
  rtems_task_argument unused
)
{
  char keybuf[64]={0};
  int key = open("/dev/keyboard", O_RDONLY);
  printk("-stm32f4 exti read  test-%d\r\n",key);

  while(1)
  {
  	rtems_task_wake_after(1000);
  	read(key,keybuf,9);
  	//printk("-------keyread %s------------\r\n",keybuf);
  }
}
