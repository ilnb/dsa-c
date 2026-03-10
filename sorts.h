#ifndef _SORT_H
#define _SORT_H

#include "arr.h"
#include <string.h>

static inline void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

static inline void ins_sort(int *arr, int n) {
  for (int i = 1; i < n; i++) {
    int j = i - 1, val = arr[i];
    while (j >= 0 && arr[j] > val) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = val;
  }
}

static inline void bub_sort(int *arr, int n) {
  for (int j = n - 1; j > 0; j--)
    for (int i = 0; i < j; i++)
      if (arr[i + 1] < arr[i])
        swap(arr + i, arr + i + 1);
}

static inline void sel_sort(int *arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    int min = i;
    for (int j = i + 1; j < n; j++)
      if (arr[min] > arr[j])
        min = j;
    swap(arr + min, arr + i);
  }
}

static inline void counting_sort(int *arr, int n) {
  int min = arr[0];
  int max = arr[0];
  for (int i = 1; i < n; i++) {
    if (min > arr[i])
      min = arr[i];
    if (max < arr[i])
      max = arr[i];
  }
  int cn = max - min + 1;
  int *count = ARR(int, cn);
  for (int i = 0; i < n; i++)
    count[arr[i] - min]++;
  int *t = ARR(int, cn);
  t[0] = 0;
  for (int i = 1; i < cn; i++)
    t[i] = t[i - 1] + count[i - 1];
  int *tmp = ARR(int, n);
  for (int i = 0; i < n; i++)
    tmp[t[arr[i] - min]++] = arr[i];
  for (int i = 0; i < n; i++)
    arr[i] = tmp[i];
  free_arrs(&tmp, &count, &t);
}

static inline void merge(int *arr, int l, int h) {
  int m = l + (h - l) / 2;
  int n1 = m - l + 1;
  int n2 = h - m;
  int *arr_l = ARR(int, n1);
  int *arr_h = ARR(int, n2);
  memcpy(arr_l, arr + l, n1 * sizeof(int));
  memcpy(arr_h, arr + m + 1, n2 * sizeof(int));
  int i = 0, j = 0, k = l;
  while (i < n1 && j < n2)
    arr[k++] = (arr_l[i] < arr_h[j]) ? arr_l[i++] : arr_h[j++];
  while (i < n1)
    arr[k++] = arr_l[i++];
  while (j < n2)
    arr[k++] = arr_h[j++];
  free_arrs(&arr_h, &arr_l);
}

static inline void merge_sort(int *arr, int l, int h) {
  if (l < h) {
    int m = (l + h) / 2;
    merge_sort(arr, l, m);
    merge_sort(arr, m + 1, h);
    merge(arr, l, h);
  }
}

// Hoare partitioning scheme
static inline int partition(int *arr, int l, int h) {
  int pivot = arr[l + rand() % (h - l + 1)];
  int i = l - 1, j = h + 1;
  while (1) {
    do {
      i++;
    } while (arr[i] < pivot);
    do {
      j--;
    } while (arr[j] > pivot);
    if (i >= j)
      break;
    swap(arr + i, arr + j);
  }
  return j;
}

static inline void quick_sort(int *arr, int l, int h) {
  if (l < h) {
    int pi = partition(arr, l, h);
    quick_sort(arr, l, pi);
    quick_sort(arr, pi + 1, h);
  }
}

static inline void max_heapify(int *arr, int n, int i) {
  while (1) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int p = i;
    if (l < n && arr[l] > arr[p])
      p = l;
    if (r < n && arr[r] > arr[p])
      p = r;
    if (p == i)
      break;
    swap(arr + i, arr + p);
    i = p;
  }
}

static inline void heap_sort(int *arr, int n) {
  int i = n / 2 - 1;
  while (i >= 0)
    max_heapify(arr, n, i--);
  while (n) {
    swap(arr, arr + --n);
    max_heapify(arr, n, 0);
  }
}

#endif /* _SORT_H */
