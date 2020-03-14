#include <stdint.h>
#include "delay.h"

/*******************************************************************************
* Func Name   : void main (uint32_t tick)
* Entry Params: tick - ticks to block
* Exit Params : None
* Description : block some ticks
* Notice      : This function cost 3 tick every cycle, and if it's break by
* other such as interrupt, this could be longer then wish.
*******************************************************************************/
#if defined(ewarm) || defined(DOXYGEN)
void
delay_tick(uint32_t tick)
{
    __asm("    subs    r0, #1\n"
          "    bne.n   delay_tick\n"
          "    bx      lr");
}
#endif
#if defined(codered) || defined(gcc) || defined(sourcerygxx)
void __attribute__((naked))
delay_tick(uint32_t tick)
{
    __asm("    subs    r0, #1\n"
          "    bne     delay_tick\n"
          "    bx      lr");
}
#endif
#if defined(rvmdk) || defined(__ARMCC_VERSION)
__asm void
delay_tick(uint32_t tick)
{
    subs    r0, #1;
    bne     delay_tick;
    bx      lr;
}
#endif
//
// For CCS implement this function in pure assembly.  This prevents the TI
// compiler from doing funny things with the optimizer.
//
#if defined(ccs)
__asm("    .sect \".text:delay_tick\"\n"
      "    .clink\n"
      "    .thumbfunc delay_tick\n"
      "    .thumb\n"
      "    .global delay_tick\n"
      "delay_tick:\n"
      "    subs r0, #1\n"
      "    bne.n delay_tick\n"
      "    bx lr\n");
#endif
