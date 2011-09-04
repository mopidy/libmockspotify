#ifndef UTIL_H
#define UTIL_H

/*** Utility functions ***/

#define true 1
#define false 0

#define ALLOC(type) ALLOC_N(type, 1)
#define ALLOC_N(type, n) ((type*) xmalloc(sizeof(type) * (n)))
#define MEMCPY(dst, src, type) MEMCPY_N(dst, src, type, 1)
#define MEMCPY_N(dst, src, type, n) (memcpy((dst), (src), sizeof(type) * (n)))

void *xmalloc(size_t);
char *hextoa(const char *, int);
char *strclone(const char *string);

#define STARTS_WITH(x, y) (strncmp((x), (y), strlen(y)) == 0)

#endif /* UTIL_H */
