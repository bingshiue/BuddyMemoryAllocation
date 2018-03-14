#ifndef BUDDY_MEMORY_ALLOCATION_H
#define BUDDY_MEMORY_ALLOCATION_H

#ifdef __cplusplus
extern "C" {
#endif

  struct buddy; /* opaque decl. */

  struct buddy * buddy_new(int level);
  void buddy_delete(struct buddy *);
  int buddy_alloc(struct buddy *, int size);
  void buddy_free(struct buddy *, int offset);
  int buddy_size(struct buddy *, int offset);
  void buddy_dump(struct buddy *);
  void buddy_dump_f(struct buddy *, void (*)(const char*)); /* ’Ç‰Á */

#ifdef __cplusplus
}

#endif

#endif
