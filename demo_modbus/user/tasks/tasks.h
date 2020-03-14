#ifndef __TASKS_H__
#define __TASKS_H__

#ifdef __cplusplus
extern "C" {
#endif

rtems_task task_status (rtems_task_argument ignored);
rtems_task task_modbus (rtems_task_argument ignored);

#ifdef __cplusplus
  }
#endif

#endif /* __TASKS_H__ */
