#include <stdio.h>
#include <string.h>

int lSearch(int *, int, int);
int binSearch(int *, int, int);
int binSearchRec(int *, int, int, int);
void inSort(int *, int);
void printArr(int *, int);

int main(void) {
  int arr[] = {3, 2, 4, 0, 1};
  printf("Unsorted array:\n");
  printArr(arr, 5);
  int n;
  printf("Enter the item to search: ");
  scanf("%d", &n);
  printf("Using linear search:\n");
  if (lSearch(arr, 5, n) != -1)
    printf("The item is found at index %d\n", lSearch(arr, 5, n));
  inSort(arr, 5);
  printf("Sorted array:\n");
  printArr(arr, 5);
  printf("Using binary search:\n");
  if (binSearch(arr, 5, n) != -1)
    printf("The item is found at index %d\n", binSearch(arr, 5, n));
  return 0;
}

void printArr(int *arr, int len) {
  for (int i = 0; i < len; i++)
    printf("%d ", i[arr]);
  printf("\n");
}

int lSearch(int *arr, int len, int item) {
  for (int i = 0; i < len; i++) {
    if (arr[i] == item)
      return i;
  }
  printf("Item not found.\n");
  return -1;
}

int binSearch(int *arr, int len, int item) {
  int low = 0, high = len - 1;
  while (low <= high) {
    int mid = (low + high) / 2;
    if (arr[mid] < item)
      low = mid + 1;
    else if (arr[mid] > item)
      high = mid - 1;
    else
      return mid;
  }
  printf("Item not found.\n");
  return -1;
}

int binSearchRec(int *arr, int low, int high, int item) {
  int mid = (low + high) / 2;
  while (low <= high) {
    if (arr[mid] < item)
      return binSearchRec(arr, mid + 1, high, item);
    else if (arr[mid] > item)
      return binSearchRec(arr, low, mid - 1, item);
    else
      return mid;
  }
  printf("Item not found.\n");
  return -1;
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
