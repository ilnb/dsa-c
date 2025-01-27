#include "arr.h"

void countSort(int *, int);

int main(void) {
  int *arr = Arr(10);
  arr[0] = 3, arr[1] = 3, arr[2] = 5, arr[3] = 1, arr[4] = 0, arr[5] = 2,
  arr[6] = 3, arr[7] = 1, arr[8] = 5, arr[9] = 4;
  printf("Unsorted array:\n");
  printArr(arr, 10);
  countSort(arr, 10);
  printf("Sorted array:\n");
  printArr(arr, 10);
  return 0;
}

void countSort(int *arr, int len) {
  int min = arr[0];
  int max = arr[0];
  for (int i = 1; i < len; i++) {
    if (min > arr[i]) {
      min = arr[i];
    }
    if (max < arr[i]) {
      max = arr[i];
    }
  }
  int countLen = max - min + 1;
  int *count = Arr(countLen);
  for (int i = 0; i < len; i++) {
    count[arr[i] - min]++;
  }
  int *t = Arr(countLen);
  t[0] = 0;
  for (int i = 0; i < countLen; i++) {
    t[i] = t[i - 1] + count[i - 1];
  }
  int *temp = Arr(len);
  for (int i = 0; i < len; i++) {
    temp[t[arr[i] - min]++] = arr[i];
  }
  for (int i = 0; i < len; i++) {
    arr[i] = temp[i];
  }
  free(temp), free(count), free(t);
  temp = count = t = 0;
}
