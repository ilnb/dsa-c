#include "arr.h"
#include <string.h>

void inSort(int *, int);
void selSort(int *, int);
void bubSort(int *, int);
void merge(int *, int, int, int);
void mergeSort(int *, int, int);
void countingSort(int *, int);
int partition(int *, int, int);
void quickSort(int *, int, int);
void maxHeapify(int *, int, int);
void heapSort(int *, int);
void swap(int *, int *);

int main(void) {
  int *arr = malloc(sizeof(int) * 5);
  int *temp = malloc(sizeof(int) * 5);
  arr[0] = 3, arr[1] = 2, arr[2] = 4, arr[3] = 0, arr[4] = 1;
  memcpy(temp, arr, 5 * sizeof(int));
  printf("Unsorted array:\n");
  printArr(arr, 5);
  printf("Sorted by selection sort:\n");
  selSort(arr, 5);
  printArr(arr, 5);
  memcpy(arr, temp, 5 * sizeof(int));
  printf("Sorted by bubble sort:\n");
  bubSort(arr, 5);
  printArr(arr, 5);
  memcpy(arr, temp, 5 * sizeof(int));
  printf("Sorted by insertion sort:\n");
  inSort(arr, 5);
  printArr(arr, 5);
  memcpy(arr, temp, 5 * sizeof(int));
  printf("Sorted by merge sort:\n");
  mergeSort(arr, 0, 4);
  printArr(arr, 5);
  memcpy(arr, temp, 5 * sizeof(int));
  printf("Sorted by quick sort:\n");
  quickSort(arr, 0, 4);
  printArr(arr, 5);
  memcpy(arr, temp, 5 * sizeof(int));
  printf("Sorted by counting sort:\n");
  countingSort(arr, 5);
  printArr(arr, 5);
  memcpy(arr, temp, 5 * sizeof(int));
  printf("Sorted by heap sort:\n");
  heapSort(arr, 5);
  printArr(arr, 5);
  freeArrs(2, &arr, &temp);
  return 0;
}

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void inSort(int *arr, int len) {
  for (int i = 1; i < len; i++) {
    int j = i - 1, val = arr[i];
    while (j >= 0 && arr[j] > val) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = val;
  }
}

void bubSort(int *arr, int len) {
  for (int j = len - 1; j > 0; j--)
    for (int i = 0; i < j; i++)
      if (arr[i + 1] < arr[i])
        swap(arr + i, arr + i + 1);
}

void selSort(int *arr, int len) {
  for (int i = 0; i < len - 1; i++) {
    int min = i;
    for (int j = i + 1; j < len; j++)
      if (arr[min] > arr[j])
        min = j;
    swap(arr + min, arr + i);
  }
}

void countingSort(int *arr, int len) {
  int min = arr[0];
  int max = arr[0];
  for (int i = 1; i < len; i++) {
    if (min > arr[i])
      min = arr[i];
    if (max < arr[i])
      max = arr[i];
  }
  int countLen = max - min + 1;
  int *count = Arr(countLen);
  for (int i = 0; i < len; i++)
    count[arr[i] - min]++;
  int *t = Arr(countLen);
  t[0] = 0;
  for (int i = 1; i < countLen; i++)
    t[i] = t[i - 1] + count[i - 1];
  int *temp = Arr(len);
  for (int i = 0; i < len; i++)
    temp[t[arr[i] - min]++] = arr[i];
  for (int i = 0; i < len; i++)
    arr[i] = temp[i];
  freeArrs(3, &temp, &count, &t);
}

void merge(int *arr, int low, int mid, int high) {
  int n1 = mid - low + 1;
  int n2 = high - mid;
  int *arrLow = Arr(n1);
  int *arrHigh = Arr(n2);
  memcpy(arrLow, arr + low, n1 * sizeof(int));
  memcpy(arrHigh, arr + mid + 1, n2 * sizeof(int));
  int i = 0, j = 0, k = low;
  while (i < n1 && j < n2)
    arr[k++] = (arrLow[i] < arrHigh[j]) ? arrLow[i++] : arrHigh[j++];
  while (i < n1)
    arr[k++] = arrLow[i++];
  while (j < n2)
    arr[k++] = arrHigh[j++];
  freeArrs(2, &arrHigh, &arrLow);
}

void mergeSort(int *arr, int low, int high) {
  if (low < high) {
    int mid = (low + high) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
  }
}

int partition(int *arr, int low, int high) {
  int pivot = arr[high];
  int i = low - 1;
  for (int j = low; j < high; j++)
    if (arr[j] < pivot)
      swap(arr + ++i, arr + j);
  swap(arr + ++i, arr + high);
  return i;
}

void quickSort(int *arr, int low, int high) {
  if (low < high) {
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

void maxHeapify(int *arr, int size, int index) {
  while (1) {
    int lChild = 2 * index + 1;
    int rChild = 2 * index + 2;
    int pIndex = index;
    if (lChild < size && arr[lChild] > arr[pIndex])
      pIndex = lChild;
    if (rChild < size && arr[rChild] > arr[pIndex])
      pIndex = rChild;
    if (pIndex == index)
      break;
    swap(arr + index, arr + pIndex);
    index = pIndex;
  }
}

void heapSort(int *arr, int size) {
  int i = size / 2 - 1;
  while (i >= 0)
    maxHeapify(arr, size, i--);
  while (size) {
    swap(arr, arr + --size);
    maxHeapify(arr, size, 0);
  }
}
