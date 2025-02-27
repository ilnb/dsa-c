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
  int i = 0, j = 0, k = 0, *c = NULL;
  while (i < len1 && j < len2) {
    if (array1[i] < array2[j]) {
      c = realloc(c, sizeof(int) * (k + 1));
      c[k] = array1[i];
      k++, i++;
    } else {
      c = realloc(c, sizeof(int) * (k + 1));
      c[k] = array2[j];
      k++, j++;
    }
  }
  while (i < len1) {
    c = realloc(c, sizeof(int) * (k + 1));
    c[k] = array1[i];
    i++, k++;
  }
  while (j < len2) {
    c = realloc(c, sizeof(int) * (k + 1));
    c[k] = array2[j];
    j++, k++;
  }
  return c;
}
