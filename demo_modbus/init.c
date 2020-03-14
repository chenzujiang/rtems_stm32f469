#include <stdio.h>
#include <stdlib.h>
#include <bsp.h>
#include "user/tasks/tasks.h"

/*******************************************************************************
* 名    称: main
* 入口参数: 无
* 出口参数: int - 无意义
* 返 回 值: 无
* 说    明：主函数，初始化系统并创建任务
*******************************************************************************/
rtems_task Init(
  rtems_task_argument argument
)
{
  rtems_id    task_id_status, task_id_shell, task_id_modbus;
  rtems_status_code status;

  status = rtems_task_create(
    rtems_build_name('S','T','A','T'),
    1,
    RTEMS_MINIMUM_STACK_SIZE,
    RTEMS_DEFAULT_MODES,
    RTEMS_FLOATING_POINT | RTEMS_DEFAULT_ATTRIBUTES,
    &task_id_status
  );

  status = rtems_task_create(
    rtems_build_name('e','M','B','P'),
    2,
    RTEMS_MINIMUM_STACK_SIZE,
    RTEMS_DEFAULT_MODES,
    RTEMS_FLOATING_POINT | RTEMS_DEFAULT_ATTRIBUTES,
    &task_id_modbus
  );
  status = rtems_task_start( task_id_status, task_status, 1);
  status = rtems_task_start( task_id_modbus, task_modbus, 2);
  status = rtems_task_delete( RTEMS_SELF );
}

/**************** START OF CONFIGURATION INFORMATION ****************/
  
/* configuration for shell test */  
#define CONFIGURE_APPLICATION_NEEDS_LIBBLOCK  
#define CONFIGURE_MAXIMUM_TASKS             5  
#define CONFIGURE_MAXIMUM_SEMAPHORES        5  
#define CONFIGURE_MAXIMUM_MESSAGE_QUEUES    5  
#define CONFIGURE_LIBIO_MAXIMUM_FILE_DESCRIPTORS 5  
#define CONFIGURE_STACK_CHECKER_ENABLED  
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE  
#define CONFIGURE_EXTRA_TASK_STACKS         (6 * RTEMS_MINIMUM_STACK_SIZE)  
#define CONFIGURE_MALLOC_STATISTICS  
#define CONFIGURE_UNIFIED_WORK_AREAS  

#define CONFIGURE_MAXIMUM_POSIX_KEYS             10
#define CONFIGURE_MAXIMUM_POSIX_KEY_VALUE_PAIRS  10

//#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_INIT
#include <rtems/confdefs.h>

/****************  END OF CONFIGURATION INFORMATION  ****************/
