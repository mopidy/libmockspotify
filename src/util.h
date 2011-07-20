#ifndef UTIL_H
#define UTIL_H

/*** Utility functions ***/

#define ALLOC(type) ALLOC_N(type, 1)
#define ALLOC_N(type, n) ((type*) xmalloc(sizeof(type) * (n)))
void *xmalloc(size_t);

#define STARTS_WITH(x, y) (strncmp((x), (y), strlen(y)) == 0)

#endif /* UTIL_H */
