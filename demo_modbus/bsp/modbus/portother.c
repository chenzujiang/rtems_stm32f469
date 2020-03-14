#include "mb.h"
#include "mbport.h"

static rtems_interrupt_level level;

void eMB_enter_critical (void)
{
  rtems_interrupt_disable (level);
}

void eMB_exit_critical (void)
{
  rtems_interrupt_enable (level);
}
