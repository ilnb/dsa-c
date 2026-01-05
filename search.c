#include <stdio.h>
#include <stdlib.h>

int linear_search(int *, int, int);
int bin_search(int *, int, int);
int bin_search_rec(int *, int, int, int);
int gt(const void *a, const void *b) { return *(int *)a > *(int *)b ? 1 : 0; }
void print_arr(int *, int);

int main(void) {
  int arr[5] = {3, 2, 4, 0, 1};
  printf("Unsorted array:\n");
  print_arr(arr, 5);
  int n;
  printf("Enter the item to search: ");
  scanf("%d", &n);
  printf("Using linear search: ");
  int ret = linear_search(arr, 5, n);
  if (ret != -1)
    printf("found at index %d\n", ret);
  else
    printf("not found.\n");
  qsort(arr, 5, sizeof(int), gt);
  printf("Sorted array:\n");
  print_arr(arr, 5);
  printf("Using binary search: ");
  ret = bin_search(arr, 5, n);
  if (ret != -1)
    printf("found at index %d\n", ret);
  else
    printf("not found.\n");
  return 0;
}

void print_arr(int *arr, int n) {
  for (int i = 0; i < n; i++)
    printf("%d ", i[arr]);
  printf("\n");
}

int linear_search(int *arr, int n, int x) {
  for (int i = 0; i < n; i++)
    if (arr[i] == x)
      return i;
  return -1;
}

int bin_search(int *arr, int n, int x) {
  int l = 0, h = n - 1;
  while (l <= h) {
    int m = (l + h) / 2;
    if (x == arr[m])
      return m;
    else if (arr[m] > x)
      h = m - 1;
    else
      l = m + 1;
  }
  return -1;
}

int bin_search_rec(int *arr, int l, int h, int x) {
  int m = (l + h) / 2;
  while (l <= h) {
    if (arr[m] == x)
      return m;
    else if (arr[m] > x)
      return bin_search_rec(arr, l, m - 1, x);
    else
      return bin_search_rec(arr, m + 1, h, x);
  }
  return -1;
}
