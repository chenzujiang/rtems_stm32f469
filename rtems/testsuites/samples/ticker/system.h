/*  system.h
 *
 *  This include file contains information that is included in every
 *  function in the test set.
 *
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 */

#include <rtems.h>
#include <rtems/test.h>
#include <inttypes.h>
#include "tmacros.h"

/* functions */

rtems_task Init(
  rtems_task_argument argument
);

rtems_task Test_task(
  rtems_task_argument argument
);

/* global variables */

/*
 *  Keep the names and IDs in global variables so another task can use them.
 */

extern rtems_id   Task_id[ 4 ];         /* array of task ids */
extern rtems_name Task_name[ 4 ];       /* array of task names */


/* configuration information */

#include <bsp.h> /* for device driver prototypes */

#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER

#define CONFIGURE_MAXIMUM_TASKS             6
#define CONFIGURE_ENABLE_BSP_I2C_DRIVER
#define CONFIGURE_LIBIO_MAXIMUM_FILE_DESCRIPTORS 5 //open need macro
#define CONFIGURE_USE_MINIIMFS_AS_BASE_FILESYSTEM
#define CONFIGURE_APPLICATION_EXTRA_DRIVERS
#define CONFIGURE_MAXIMUM_MESSAGE_QUEUES     3

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_EXTRA_TASK_STACKS         (3 * RTEMS_MINIMUM_STACK_SIZE)

#define CONFIGURE_INITIAL_EXTENSIONS RTEMS_TEST_INITIAL_EXTENSION

#include <rtems/confdefs.h>

/*
 *  This allows us to view the "Test_task" instantiations as a set
 *  of numbered tasks by eliminating the number of application
 *  tasks created.
 *
This allows us to view the "Test_task" instantiations as a set of numbered tasks by eliminating the number of application tasks created.
 *
 *  In reality, this is too complex for the purposes of thi example.  It would have been easier to pass a task argument. :)
 *  But it shows how rtems_id's can sometimes be used.
这允许我们通过消除创建的应用程序任务的数量，将“Test_task”实例化视为一组编号的任务。
*实际上，这对于这个例子来说太复杂了。传递任务参数会更容易。:)
*但它显示了rtems-id有时是如何使用的。
 *  In reality, this is too complex for the purposes of this
 *  example.  It would have been easier to pass a task argument. :)
 *  But it shows how rtems_id's can sometimes be used.
 */

#define task_number( tid ) \
  ( rtems_object_id_get_index( tid ) - \
      rtems_configuration_get_rtems_api_configuration()-> \
        number_of_initialization_tasks )

/* end of include file */
