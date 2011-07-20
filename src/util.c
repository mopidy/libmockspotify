#include <stdlib.h>
#include <string.h>
#include "util.h"

void*
xmalloc(size_t size, int count)
{
  size_t realsize = size * count;
  void *ptr = malloc(realsize);
  memset(ptr, 0, realsize);
  return ptr;
}
