#ifndef SYSTEM_H
#define SYSTEM_H

#include <rtems/test.h>

#include <bsp.h> /* for device driver prototypes */

rtems_task Test_task(
  rtems_task_argument argument
);

extern void dummy_function_empty_body_to_force_call(void);

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MICROSECONDS_PER_TICK 1000

#define CONFIGURE_MAXIMUM_TASKS            6 //MESSAGE_QUEUES create need task
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#define CONFIGURE_LIBIO_MAXIMUM_FILE_DESCRIPTORS 5 //open need macro
#define CONFIGURE_USE_MINIIMFS_AS_BASE_FILESYSTEM

#define CONFIGURE_MAXIMUM_MESSAGE_QUEUES     3
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_EXTRA_TASK_STACKS         (3 * RTEMS_MINIMUM_STACK_SIZE)



#define CONFIGURE_APPLICATION_EXTRA_DRIVERS

#define CONFIGURE_INITIAL_EXTENSIONS RTEMS_TEST_INITIAL_EXTENSION

#include <rtems/confdefs.h>
#endif
