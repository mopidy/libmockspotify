#include "libmockspotify.h"

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

char
itoh(int n)
{
  char hex[] = { "0123456789abcdef" };
  return hex[n];
}

char*
hextoa(const char *str, int size)
{
  if (size % 2) return NULL;
  int length = (size / 2) + 1;

  char *result = ALLOC_N(char, length);

  int i;
  for (i = 0; i < size; i += 2)
  {
    result[i/2] = (htoi(str[i]) << 4) + htoi(str[i+1]);
  }

  result[length - 1] = '\0';

  return result;
}

void
atohex(char *dst, const char *src, int size)
{
  int i;
  int p;
  for (i = p = 0; i < size; i += 2, p = i/2)
  {
    dst[i]   = itoh((src[p] >> 4) & 0x0F);
    dst[i+1] = itoh(src[p] & 0xF);
  }
}

char *
strclone(const char *string)
{
  if (string == NULL)
  {
    return (char *) ""; /* Oh shit… */
  }

  char *dst = ALLOC_N(char, strlen(string) + 1);
  strcpy(dst, string);
  return dst;
}

int
compare_ints(const void *a, const void *b)
{
  const int *ia = (int *)a;
  const int *ib = (int *)b;

  return *ia - *ib;
}
