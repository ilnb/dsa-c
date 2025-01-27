#include "arr.h"

void inSort(int *, int);
void selSort(int *, int);
void bubSort(int *, int);
void merge(int *, int, int, int);
void mergeSort(int *, int, int);
void countingSort(int *, int);
int partition(int *, int, int);
void quickSort(int *, int, int);
int *copy(int *);
void swap(int *, int *);

int main(void) {
  int *arr = malloc(sizeof(int) * 5);
  int *temp = malloc(sizeof(int) * 5);
  arr[0] = 3, arr[1] = 2, arr[2] = 4, arr[3] = 0, arr[4] = 1;
  temp = copy(arr);
  printf("Unsorted array:\n");
  printArr(arr, 5);
  printf("Sorted by selection sort:\n");
  selSort(arr, 5);
  printArr(arr, 5);
  arr = copy(temp);
  printf("Sorted by bubble sort:\n");
  bubSort(arr, 5);
  printArr(arr, 5);
  arr = copy(temp);
  printf("Sorted by insertion sort:\n");
  inSort(arr, 5);
  printArr(arr, 5);
  arr = copy(temp);
  printf("Sorted by merge sort:\n");
  mergeSort(arr, 0, 4);
  printArr(arr, 5);
  arr = copy(temp);
  printf("Sorted by quick sort:\n");
  quickSort(arr, 0, 4);
  printArr(arr, 5);
  arr = copy(temp);
  printf("Sorted by counting sort:\n");
  countingSort(arr, 5);
  printArr(arr, 5);
  free(arr);
  arr = temp = NULL;
  return 0;
}

int *copy(int *arr) { return arr; }

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
  for (int j = len - 1; j > 0; j--) {
    for (int i = 0; i < j; i++) {
      if (arr[i + 1] < arr[i]) {
        swap(arr + i, arr + i + 1);
      }
    }
  }
}

void selSort(int *arr, int len) {
  for (int i = 0; i < len - 1; i++) {
    int min = i;
    for (int j = i + 1; j < len; j++) {
      if (arr[min] > arr[j]) {
        min = j;
      }
    }
    if (min != i) {
      swap(arr + min, arr + i);
    }
  }
}

void merge(int *arr, int low, int mid, int high) {
  int n1 = mid - low + 1;
  int n2 = high - mid;
  int *arrLow = malloc(sizeof(int) * n1);
  int *arrHigh = malloc(sizeof(int) * n2);
  for (int i = 0; i < n1; i++) {
    arrLow[i] = arr[low + i];
  }
  for (int i = 0; i < n2; i++) {
    arrHigh[i] = arr[mid + 1 + i];
  }
  int i = 0, j = 0, k = low;
  while (i < n1 && j < n2) {
    if (arrLow[i] < arrHigh[j]) {
      arr[k] = arrLow[i];
      i++, k++;
    } else {
      arr[k] = arrHigh[j];
      j++, k++;
    }
  }
  if (i < n1) {
    while (i < n1) {
      arr[k] = arrLow[i];
      i++, k++;
    }
  } else if (j < n2) {
    while (j < n2) {
      arr[k] = arrHigh[j];
      j++, k++;
    }
  }
  free(arrLow), free(arrHigh);
  arrLow = arrHigh = NULL;
}

void countingSort(int *arr, int len) {
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
  for (int i = 0; i < countLen; i++) {
    count[i] = 0;
  }
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
  for (int j = low; j < high; j++) {
    if (arr[j] < pivot) {
      i++;
      swap(arr + i, arr + j);
    }
  }
  swap(arr + i + 1, arr + high);
  return i + 1;
}

void quickSort(int *arr, int low, int high) {
  if (low < high) {
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}
