#include "arr.h"
#include <string.h>

int main() {
  char **names = ARR(char *, 5);
  char ***lots_of_names = MAT(char *, 2, 2);
  char buf[30] = {0};
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) {
      printf("Enter name[%d][%d]: ", i, j);
      scanf("%s", buf);
      lots_of_names[i][j] = strdup(buf);
    }
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
      printf("%s\n", lots_of_names[i][j]);
  for (int i = 0; i < 5; i++) {
    printf("Enter name[%d]: ", i + 1);
    scanf("%s", buf);
    names[i] = strdup(buf);
  }
  for (int i = 0; i < 5; i++)
    printf("Name %d: %s\n", i + 1, names[i]);
  // free individual strings
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
      free(lots_of_names[i][j]);
  lots_of_names = freeMat(lots_of_names);
  for (int i = 0; i < 5; i++)
    free(names[i]);
  free(names);
  names = 0;
  return 0;
}
