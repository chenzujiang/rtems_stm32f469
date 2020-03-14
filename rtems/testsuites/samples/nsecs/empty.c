/*  COPYRIGHT (c) 1989-2007.
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
#include "tmacros.h"
/* put here hoping it won't get inlined */
void dummy_function_empty_body_to_force_call(void) {}

rtems_task Test_task(
  rtems_task_argument unused
)
{
  rtems_id          tid;
  rtems_status_code status;

//  status = rtems_task_ident( RTEMS_SELF, RTEMS_SEARCH_ALL_NODES, &tid );
//  directive_failed( status, "task ident" );
 // int fd = open("/dev/keyboard", O_RDWR);
  printf("dev --%d\r\n",1);
  for(;;)
  {
	  printf("dev --%d\r\n",2);
	  sleep(2);
  }


}
