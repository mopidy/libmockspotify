#ifndef UTIL_H
#define UTIL_H

/*** Utility functions ***/

#define ALLOC(type) ((type*) xmalloc(sizeof(type)))
void *xmalloc(size_t);

#define STARTS_WITH(x, y) (strncmp((x), (y), strlen(y)) == 0)

#endif /* UTIL_H */
