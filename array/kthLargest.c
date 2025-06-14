// this is the bad super slow
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void bubSort(int *arr, int len) {
  for (int j = len - 1; j > 0; j--)
    for (int i = 0; i < j; i++)
      if (arr[i + 1] > arr[i])
        swap(arr + i, arr + i + 1);
}

void revInsert(int *arr, int n, int val) {
  int i = 0;
  while (i < n && arr[i] > val)
    i++;
  for (int j = n - 1; j >= i; j--)
    arr[j + 1] = arr[j];
  arr[i] = val;
}

int kthLargest(int *arr, int n, int k) {
  int *t = malloc(sizeof(int) * k);
  for (int i = 0; i < k; i++)
    t[i] = arr[i];
  bubSort(t, k);
  for (int i = k; i < n; i++)
    if (arr[i] > t[k - 1])
      revInsert(t, k, arr[i]);
  int x = t[k - 1];
  free(t);
  return x;
}

int main() {
  int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i = 0; i < 10; i++)
    printf("%d ", kthLargest(arr, 10, i + 1));
  printf("\n");
}
