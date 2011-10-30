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

#define DEFINE_REFCOUNTERS_FOR(type)       \
  void sp_##type##_add_ref(sp_##type *x) {} \
  void sp_##type##_release(sp_##type *x) {}

#define DEFINE_READER(kind, field, return_type) \
  return_type sp_##kind##_##field(sp_##kind *x) \
  {                                             \
    return x->field;                            \
  }

#define DEFINE_MOCK_READER(kind, field, return_type) \
  return_type mocksp_##kind##_get_##field(sp_##kind *x) \
  {                                             \
    return x->field;                            \
  }

#define DEFINE_SESSION_READER(kind, field, return_type) \
  return_type sp_##kind##_##field(sp_session *x, sp_##kind *y) \
  {                                                     \
    return y->field;                                    \
  }

#define DEFINE_ARRAY_READER(kind, field, return_type) \
  return_type sp_##kind##_##field(sp_##kind *x, int index) \
  {                                                        \
    if (index >= x->num_##field##s) return NULL;         \
    return x->field##s[index];                           \
  }

#define DEFINE_ARRAY_MEMBER_READER(kind, field, member, return_type) \
  return_type sp_##kind##_##field##_##member(sp_##kind *x, int index) \
  {                                                        \
    if (index >= x->num_##field##s) return (return_type) 0;         \
    return x->field##s[index].member;                   \
  }

#endif /* UTIL_H */
