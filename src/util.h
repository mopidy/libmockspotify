#ifndef UTIL_H
#define UTIL_H

/*** Utility functions ***/

#define ALLOC(type) ((type*) xmalloc(sizeof(type)))
void *xmalloc(size_t);

#define STRNCMP2(x, y) (strncmp((x), (y), sizeof(y) - 1))

#endif /* UTIL_H */
