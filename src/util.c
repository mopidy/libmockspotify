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

int
htoi(char n)
{
  if (n >= '0' && n <= '9') return n - '0';
  else if (n >= 'a' && n <= 'f') return n - 'a' + 10;
  else if (n >= 'A' && n <= 'F') return n - 'A' + 10;
  else return 0;
}

char*
hextoa(const char *str, int size)
{
  if (size % 2) return NULL;

  char *result = ALLOC_N(char, size / 2);

  int i;
  for (i = 0; i < size; i += 2)
  {
    result[i/2] = (htoi(str[i]) << 4) + htoi(str[i+1]);
  }

  return result;
}
