#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define isChar(c) ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9')

char *reverseWords(char *s) {
  if (!s)
    return s;
  char *t = s;
  int count = 0, length = strlen(t);
  while (*t) {
    if (isChar(*t))
      count++, t++;
    while (isChar(*t))
      t++;
    while (*t == ' ')
      t++;
  }
  t = s;
  struct {
    char *start;
    int len;
  } *data = malloc(sizeof(*data) * count);
  int i = 0;
  while (*t) {
    if (isChar(*t)) {
      data[i].start = t;
      data[i].len = 0;
      while (isChar(*t)) {
        data[i].len++;
        t++;
      }
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
    size += data[i].len + 1;
  char *rev = calloc(size, sizeof(char));
  for (i = count - 1; i; i--) {
    strncat(rev, data[i].start, data[i].len);
    strcat(rev, " ");
  }
  strncat(rev, data[i].start, data[i].len);
  free(data);
  return rev;
}

int main() {
  char *s1 = reverseWords("  hello galz  ");
  char *s2 = reverseWords("are you crazies");
  printf("%s\n", s1);
  printf("%s\n", s2);
  free(s1), free(s2);
  return 0;
}
