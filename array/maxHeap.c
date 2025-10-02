#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 30

inline void swap(int *, int *);
void printArr(int *, int);
void menu();
void makeMaxHeap(int *, int);
void maxHeapify(int *, int, int);
void insert(int *, int *, int);
int deleteMax(int *, int *);
int isKeyLine(int *, int, int);
void printHeap(int *, int);

int main() {
  int arr[MAX], size = 15;
  arr[0] = 4, arr[1] = 10, arr[2] = 1;
  arr[3] = 5, arr[4] = 3, arr[5] = 6, arr[6] = 2;
  arr[7] = 8, arr[8] = 10, arr[9] = 7, arr[10] = 12;
  arr[11] = 13, arr[12] = 11, arr[13] = 12;
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
      case 3:
        printHeap(arr, size);
      case 4:
        break;
      default:
        printf("Invalid option\n");
    }
  } while (option != 4);
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

void maxHeapify(int *arr, int size, int idx) {
  while (1) {
    int l = 2 * idx + 1;
    int r = 2 * idx + 2;
    int p = idx;
    if (l < size && arr[l] > arr[p])
      p = l;
    if (r < size && arr[r] > arr[p])
      p = r;
    if (p == idx)
      break;
    swap(arr + idx, arr + p);
    idx = p;
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

int isKeyLine(int *keyLines, int size, int line) {
  int depth = 1 + (int)log2(size);
  for (int i = depth - 1; i >= 0; i--)
    if (line == keyLines[i])
      return 1;
  return 0;
}

void printHeap(int *arr, int size) {
  if (size == 1) {
    printf("%d\n", arr[0]);
    return;
  }
  int depth = 1 + (int)log2(size);
  int *keyLines = calloc(depth, sizeof(int));
  for (int i = 1; i < depth; i++)
    keyLines[i] = 3 * (1 << (i - 1)) - 1;
  int line = depth >= 2 ? 3 * (1 << (depth - 2)) - 1 : ((depth == 1) ? 3 : 1);
  while (line >= 0 && depth) {
    // print initial spaces
    if (depth == 2)
      printf(" ");
    else if (depth > 2)
      for (int i = 0; i < line; i++)
        printf(" ");
    int ln = 1 + (int)log2(size) - depth;
    int maxSlash;
    // print the values
    if (isKeyLine(keyLines, size, line)) {
      if (depth == 2)
        printf(" ");
      int lIndex = 0, rIndex = 0;
      if (ln) {
        lIndex = (1 << ln) - 1;
        rIndex = 2 * lIndex;
        if (rIndex >= size)
          rIndex = size - 1;
      }
      int nrIndex = 2 * rIndex + 2;
      if (nrIndex >= size)
        nrIndex = size - 1;
      maxSlash = nrIndex - rIndex;
      for (int i = lIndex; i < rIndex; i++) {
        printf("%2d", arr[i]);
        for (int j = 0; j < 3 * (1 << (depth - 1)) - 2; j++)
          printf(" ");
      }
      printf("%2d\n", arr[rIndex]);
    }
    // or the slashes
    else {
      int diff = keyLines[depth - 1] - line, slash = 0;
      for (int i = 0; i < (1 << ln) - 1 && slash < maxSlash; i++) {
        if (slash < maxSlash) {
          printf("/");
          slash++;
        }
        for (int i = 0; i < 2 * diff && slash < maxSlash; i++)
          printf(" ");
        if (slash < maxSlash) {
          printf("\\");
          slash++;
        }
        for (int i = 0; i < 2 * line && slash < maxSlash; i++)
          printf(" ");
      }
      if (slash < maxSlash) {
        printf("/");
        slash++;
      }
      for (int i = 0; i < 2 * diff && slash < maxSlash; i++)
        printf(" ");
      if (slash < maxSlash) {
        printf("\\");
        slash++;
      }
      printf("\n");
    }
    line--;
    if (isKeyLine(keyLines, size, line))
      depth--;
  }
  printf("\n");
  free(keyLines);
}
