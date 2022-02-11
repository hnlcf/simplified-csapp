/* CSAPP - Introduction to Computer Systems.
 * Author:      louchangfeng@outlook.com
 * Github:      https://github.com/hnlcf/simplified-csapp
 *
 * This project is exclusively owned by louchangfeng
 * and shall not be used for commercial and profitting purpose
 * without louchangfeng's permission.
 *
 * Thanks for yangminz's code repository and videos in my learning.
 */

#include "common.h"
#include <stdarg.h>
#include <stdio.h>

// wrapper of stdio printf,
// controlled by the debug verbose bit set
uint64_t
debug_printf(uint64_t open_set, const char* format, ...)
{
  if ((open_set & DEBUG_VERBOSE_SET) == 0x0) {
    return 0x1;
  }

  // implement of stdio printf()
  va_list argptr;
  va_start(argptr, format);
  vfprintf(stderr, format, argptr);
  va_end(argptr);

  return 0x0;
}