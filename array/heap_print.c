#include <stdio.h>

/* ceil(log2(n)) */
int ln2c(size_t n) { return n ? 64 - __builtin_clzll(n) : -1; }

int is_pow2(int x) { return (x & (x - 1)) == 0; }

int is_keyline(int l) {
  if (!l)
    return 1;
  int v = l + 1;
  return (v % 3 == 0) && (is_pow2(v / 3));
}

void print_heap(int *arr, size_t n, const char *fmt) {
  if (!n)
    return;
  if (n == 1) {
    printf(fmt, arr[0]);
    printf("\n");
    return;
  }
  int d = ln2c(n);
  int line = d >= 2 ? 3 * (1 << (d - 2)) - 1 : ((d == 1) ? 3 : 1);
  int lvl_keyline = line;
  while (line >= 0 && d) {
    /*print initial spaces*/
    if (d == 2)
      printf(" ");
    else if (d > 2)
      for (int i = 0; i < line; i++)
        printf(" ");
    int ln = ln2c(n) - d;
    int max_slash;
    /* print the values*/
    if (is_keyline(line)) {
      if (d == 2)
        printf(" ");
      int l = 0, r = 0;
      if (ln) {
        l = (1 << ln) - 1;
        r = 2 * l;
        if (r >= n)
          r = n - 1;
      }
      size_t nr = 2 * r + 2;
      if (nr >= n)
        nr = n - 1;
      max_slash = nr - r;
      for (int i = l; i < r; i++) {
        printf(fmt, arr[i]);
        for (int j = 0; j < 3 * (1 << (d - 1)) - 2; j++)
          printf(" ");
      }
      printf(fmt, arr[r]);
      printf("\n");
    } /* or the slashes */
    else {
      int diff = lvl_keyline - line, slash = 0;
      for (int i = 0; i < (1 << ln) - 1 && slash < max_slash; i++) {
        if (slash < max_slash) {
          printf("/");
          slash++;
        }
        if (slash < max_slash) {
          for (int i = 0; i < 2 * diff; i++)
            printf(" ");
          printf("\\");
          slash++;
        }
        if (slash < max_slash)
          for (int i = 0; i < 2 * line; i++)
            printf(" ");
      }
      if (slash < max_slash) {
        printf("/");
        slash++;
      }
      if (slash < max_slash) {
        for (int i = 0; i < 2 * diff; i++)
          printf(" ");
        printf("\\");
        slash++;
      }
      printf("\n");
    }
    line--;
    if (is_keyline(line))
      d--, lvl_keyline = line;
  }
  printf("\n");
}
