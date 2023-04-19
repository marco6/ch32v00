/**
 * This functions **is not** taken from newlib as the
 * linker script for ch32v00x can actually define the
 * symbols needed to use all the available ram.
 */
#include "glue.h"

#include <stddef.h>

void *_sbrk(ptrdiff_t incr) {
    extern char _end[];
    extern char _heap_end[];
    static char *curbrk = _end;

    if ((curbrk + incr < _end) || (curbrk + incr > _heap_end)) {
      return NULL - 1;
    }

    curbrk += incr;
    return curbrk - incr;
}
