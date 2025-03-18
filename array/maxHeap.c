#include <stdio.h>
#define MAX 30

void swap(int *, int *);
void printArr(int *, int);
void menu();
void makeMaxHeap(int *, int);
void maxHeapify(int *, int, int);
void insert(int *, int *, int);
int deleteMax(int *, int *);

int main() {
  int arr[MAX], size = 10;
  arr[0] = 4, arr[1] = 9, arr[2] = 1;
  arr[3] = 5, arr[4] = 3, arr[5] = 6, arr[6] = 2;
  arr[7] = 8, arr[8] = 10, arr[9] = 7;
  makeMaxHeap(arr, size);
  int option;
  do {
    menu();
    printf("What do you want to do? ");
    scanf("%d", &option);
    switch (option) {
      case 1: {
        printf("Enter the value to enter: ");
        int val;
        scanf("%d", &val);
        insert(arr, &size, val);
        break;
      }
      case 2: {
        int n = deleteMax(arr, &size);
        if (n != -1)
          printf("The number deleted is %d\n", n);
        break;
      }
      case 3: {
        printArr(arr, size);
        break;
      }
      case 4:
        break;
      default:
        printf("Invalid option\n");
    }
  } while (option != 4);
}

void menu() {
  printf("1. Insert value\n");
  printf("2. Delete max value\n");
  printf("3. Print heap\n");
  printf("4. Exit\n");
}

void makeMaxHeap(int *arr, int size) {
  int i = size / 2 - 1;
  while (i >= 0)
    maxHeapify(arr, size, i--);
}

void maxHeapify(int *arr, int size, int index) {
  int lChild = 2 * index + 1;
  int rChild = 2 * index + 2;
  int pIndex = index;
  if (lChild < size && arr[lChild] > arr[pIndex])
    pIndex = lChild;
  if (rChild < size && arr[rChild] > arr[pIndex])
    pIndex = rChild;
  if (pIndex != index) {
    swap(arr + index, arr + pIndex);
    maxHeapify(arr, size, pIndex);
  }
}

void insert(int *arr, int *size_p, int val) {
  arr[(*size_p)++] = val;
  int i = *size_p - 1;
  while (i) {
    int pIndex = (i - 1) / 2;
    if (arr[pIndex] > arr[i])
      break;
    swap(arr + pIndex, arr + i);
    i = pIndex;
  }
}

int deleteMax(int *arr, int *size_p) {
  if (*size_p) {
    int n = arr[0];
    swap(arr, arr + --*size_p);
    maxHeapify(arr, *size_p, 0);
    return n;
  }
  return -1;
}

void swap(int *a, int *b) {
  int t = *b;
  *b = *a;
  *a = t;
}

void printArr(int *arr, int len) {
  for (int i = 0; i < len; i++)
    printf("%3d", arr[i]);
  printf("\n");
}
