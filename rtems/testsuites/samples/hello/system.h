#include <bsp/library/stm324x9i_eval_sdio_sd.h>
#include <bsp/library/bsp_sdcard.h>
#include <bsp/library/main.h>
#include <bsp/library/stm324x9i_eval_fmc_sdram.h>
#include <bsp/library/qspi_readwrite_conf.h>
#include <rtems.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <rtems/led-drv.h>
#include <rtems/i2c-drv.h>
#include <bsp/keyboard.h>
#include <sys/ioccom.h>
rtems_task Init(rtems_task_argument argument);
void thread_i2c(rtems_task_argument unused);
void thread_led(rtems_task_argument arg);
void thread_key(rtems_task_argument unused);
void thread_card(rtems_task_argument arg);
void thread_qspi(rtems_task_argument arg);
