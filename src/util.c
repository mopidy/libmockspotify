#include <stdlib.h>
#include <string.h>
#include "util.h"

void*
xmalloc(size_t size)
{
  void *ptr = malloc(size);
  memset(ptr, 0, size);
  return ptr;
}
