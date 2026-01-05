#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define is_char(c) ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9')

char *rev_words(char *s) {
  if (!s)
    return s;
  char *t = s;
  int count = 0;
  unsigned long len = strlen(t);
  while (*t) {
    if (is_char(*t))
      count++, t++;
    while (is_char(*t))
      t++;
    while (*t == ' ')
      t++;
  }
  t = s;
  struct {
    char *start;
    int n;
  } *data = malloc(count * sizeof *data);
  int i = 0;
  while (*t) {
    if (is_char(*t)) {
      data[i].start = t;
      int n = 0;
      while (is_char(*t))
        n++, t++;
      data[i].n = n;
      while (*t == ' ')
        t++;
      i++;
    } else {
      while (*t == ' ')
        t++;
    }
  }
  t = s;
  int size = 0;
  for (i = 0; i < count; i++)
    size += data[i].n + 1;
  char *rev = malloc(size * sizeof *rev), *p;
  *rev = 0;
  p = rev;
  for (i = count - 1; i; i--) {
    strncat(p, data[i].start, data[i].n);
    p += data[i].n;
    strcat(p, " ");
    p += 1;
  }
  strncat(p, data[i].start, data[i].n);
  free(data);
  return rev;
}

int main() {
  char *s1 = rev_words("  hello galz  ");
  char *s2 = rev_words("are you crazies");
  printf("%s\n", s1);
  printf("%s\n", s2);
  free(s1), free(s2);
  return 0;
}
