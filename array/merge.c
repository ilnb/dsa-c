#include "arr.h"

int *merge(int *, int, int *, int);

int main(void) {
  int arr1[3] = {2, 5, 8};
  int arr2[2] = {0, 4};
  int *c = merge(arr1, 3, arr2, 2);
  printArr(c, 5);
  free(c);
  c = NULL;
  return 0;
}

int *merge(int *array1, int len1, int *array2, int len2) {
  int i = 0, j = 0, k = 0;
  int *c = malloc((len1 + len2) * sizeof(*c));
  while (i < len1 && j < len2)
    c[k++] = (array1[i] < array2[j]) ? array1[i++] : array2[j++];
  while (i < len1)
    c[k++] = array1[i++];
  while (j < len2)
    c[k++] = array2[j++];
  return c;
}
