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

int *merge(int *arr1, int len1, int *arr2, int len2) {
  int i = 0, j = 0, k = 0;
  int *c = ARR(int, len1 + len2);
  while (i < len1 && j < len2)
    c[k++] = (arr1[i] < arr2[j]) ? arr1[i++] : arr2[j++];
  while (i < len1)
    c[k++] = arr1[i++];
  while (j < len2)
    c[k++] = arr2[j++];
  return c;
}
