#ifndef _PORT_H
#define _PORT_H

#include <assert.h>
#include <inttypes.h>
#include <bsp.h>
#include <bsp/library/stm32f4xx.h>

#define INLINE                      inline
#define PR_BEGIN_EXTERN_C           extern "C" {
#define PR_END_EXTERN_C             }

void eMB_enter_critical (void);
void eMB_exit_critical (void);

#define ENTER_CRITICAL_SECTION( )   eMB_enter_critical()
#define EXIT_CRITICAL_SECTION( )    eMB_exit_critical()

typedef uint8_t BOOL;

typedef unsigned char UCHAR;
typedef char CHAR;

typedef uint16_t USHORT;
typedef int16_t SHORT;

typedef uint32_t ULONG;
typedef int32_t LONG;

#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif

#endif
