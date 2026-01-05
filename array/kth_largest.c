// this is the bad super slow
#include "arr.h"

#define swap(type, a, b)                                                                           \
  do {                                                                                             \
    type t = a;                                                                                    \
    a = b;                                                                                         \
    b = t;                                                                                         \
  } while (0)

void bub_sort(int *arr, int n) {
  for (int j = n - 1; j > 0; j--)
    for (int i = 0; i < j; i++)
      if (arr[i + 1] > arr[i])
        swap(int, arr[i], arr[i + 1]);
}

void insert(int *arr, int n, int val) {
  int i = 0;
  while (i < n && arr[i] > val)
    i++;
  for (int j = n - 1; j >= i; j--)
    arr[j + 1] = arr[j];
  arr[i] = val;
}

int kth_largest(int *arr, int n, int k) {
  [[gnu::cleanup(_free_arr)]] int *t = ARR(int, k);
  for (int i = 0; i < k; i++)
    t[i] = arr[i];
  bub_sort(t, k);
  for (int i = k; i < n; i++)
    if (arr[i] > t[k - 1])
      insert(t, k, arr[i]);
  int x = t[k - 1];
  return x;
}

int main() {
  int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i = 0; i < 10; i++)
    printf("%d ", kth_largest(arr, 10, i + 1));
  printf("\n");
}
