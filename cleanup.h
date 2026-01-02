#ifndef _CLEANUP_H
#define _CLEANUP_H

#include <stdio.h>
#include <stdlib.h>

static inline void clean_one(void *ptr) {
  free(*(void **)ptr);
  *(void **)ptr = 0;
}

static inline void clean_file(void *ptr) {
  free(*(FILE **)ptr);
  *(FILE **)ptr = 0;
}

#define cl(fn) [[gnu::cleanup(fn)]]

#endif /* _CLEANUP_H */
