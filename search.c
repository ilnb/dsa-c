#include <stdio.h>
#include <stdlib.h>

int lSearch(int *, int, int);
int binSearch(int *, int, int);
int binSearchRec(int *, int, int, int);
int cmp(const void *a, const void *b) { return *(int *)a > *(int *)b ? 1 : 0; }
void printArr(int *, int);

int main(void) {
  int arr[5] = {3, 2, 4, 0, 1};
  printf("Unsorted array:\n");
  printArr(arr, 5);
  int n;
  printf("Enter the item to search: ");
  scanf("%d", &n);
  printf("Using linear search:\n");
  if (lSearch(arr, 5, n) != -1)
    printf("The item is found at index %d\n", lSearch(arr, 5, n));
  else
    printf("Item not found.\n");
  qsort(arr, 5, sizeof(int), cmp);
  printf("Sorted array:\n");
  printArr(arr, 5);
  printf("Using binary search:\n");
  if (binSearch(arr, 5, n) != -1)
    printf("The item is found at index %d\n", binSearch(arr, 5, n));
  else
    printf("Item not found.\n");
  return 0;
}

void printArr(int *arr, int len) {
  for (int i = 0; i < len; i++)
    printf("%d ", i[arr]);
  printf("\n");
}

int lSearch(int *arr, int len, int item) {
  for (int i = 0; i < len; i++)
    if (arr[i] == item)
      return i;
  return -1;
}

int binSearch(int *arr, int len, int item) {
  int low = 0, high = len - 1;
  while (low <= high) {
    int mid = (low + high) / 2;
    if (item == arr[mid])
      return mid;
    else if (arr[mid] > item)
      high = mid - 1;
    else
      low = mid + 1;
  }
  return -1;
}

int binSearchRec(int *arr, int low, int high, int item) {
  int mid = (low + high) / 2;
  while (low <= high) {
    if (arr[mid] == item)
      return mid;
    else if (arr[mid] > item)
      return binSearchRec(arr, low, mid - 1, item);
    else
      return binSearchRec(arr, mid + 1, high, item);
  }
  return -1;
}
