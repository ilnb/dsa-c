#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 30

static inline void swap(int *, int *);
void print_arr(int *, int);
void menu();
void mk_max_heap(int *, int);
void max_heapify(int *, int, int);
void push(int *, int *, int);
int pop_max(int *, int *);
int is_keyline(int *, int, int);
void print_heap(int *, int);

int main() {
  int arr[MAX], n = 15;
  arr[0] = 4, arr[1] = 10, arr[2] = 1;
  arr[3] = 5, arr[4] = 3, arr[5] = 6, arr[6] = 2;
  arr[7] = 8, arr[8] = 10, arr[9] = 7, arr[10] = 12;
  arr[11] = 13, arr[12] = 11, arr[13] = 12;
  mk_max_heap(arr, n);
  int opt;
  do {
    menu();
    printf("What do you want to do? ");
    scanf("%d", &opt);
    switch (opt) {
    case 1: {
      printf("Enter the value to enter: ");
      int val;
      scanf("%d", &val);
      push(arr, &n, val);
      break;
    }
    case 2: {
      int t = pop_max(arr, &n);
      if (t != -1)
        printf("The number deleted is %d\n", t);
      break;
    }
    case 3:
      print_heap(arr, n);
    case 4:
      break;
    default:
      printf("Invalid option\n");
    }
  } while (opt != 4);
}

void swap(int *a, int *b) {
  int t = *b;
  *b = *a;
  *a = t;
}

void print_arr(int *arr, int len) {
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

void mk_max_heap(int *arr, int n) {
  int i = n / 2 - 1;
  while (i >= 0)
    max_heapify(arr, n, i--);
}

void max_heapify(int *arr, int n, int i) {
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

void push(int *arr, int *n_p, int val) {
  arr[(*n_p)++] = val;
  int i = *n_p - 1;
  while (i) {
    int pIndex = (i - 1) / 2;
    if (arr[pIndex] > arr[i])
      break;
    swap(arr + pIndex, arr + i);
    i = pIndex;
  }
}

int pop_max(int *arr, int *n) {
  if (*n) {
    int t = arr[0];
    swap(arr, arr + --*n);
    max_heapify(arr, *n, 0);
    return t;
  }
  return -1;
}

int is_keyline(int *keylines, int n, int line) {
  int depth = 1 + (int)log2(n);
  for (int i = depth - 1; i >= 0; i--)
    if (line == keylines[i])
      return 1;
  return 0;
}

void print_heap(int *arr, int n) {
  if (!n)
    return;
  if (n == 1) {
    printf("%d\n", arr[0]);
    return;
  }
  int d = 1 + (int)log2(n);
  int *keylines = calloc(d, sizeof(int));
  for (int i = 1; i < d; i++)
    keylines[i] = 3 * (1 << (i - 1)) - 1;
  int line = d >= 2 ? 3 * (1 << (d - 2)) - 1 : ((d == 1) ? 3 : 1);
  while (line >= 0 && d) {
    // print initial spaces
    if (d == 2)
      printf(" ");
    else if (d > 2)
      for (int i = 0; i < line; i++)
        printf(" ");
    int ln = 1 + (int)log2(n) - d;
    int max_slash;
    // print the values
    if (is_keyline(keylines, n, line)) {
      if (d == 2)
        printf(" ");
      int l = 0, r = 0;
      if (ln) {
        l = (1 << ln) - 1;
        r = 2 * l;
        if (r >= n)
          r = n - 1;
      }
      int nr = 2 * r + 2;
      if (nr >= n)
        nr = n - 1;
      max_slash = nr - r;
      for (int i = l; i < r; i++) {
        printf("%2d", arr[i]);
        for (int j = 0; j < 3 * (1 << (d - 1)) - 2; j++)
          printf(" ");
      }
      printf("%2d\n", arr[r]);
    }
    // or the slashes
    else {
      int diff = keylines[d - 1] - line, slash = 0;
      for (int i = 0; i < (1 << ln) - 1 && slash < max_slash; i++) {
        if (slash < max_slash) {
          printf("/");
          slash++;
        }
        if (slash < max_slash) {
          for (int i = 0; i < 2 * diff; i++)
            printf(" ");
          printf("\\");
          slash++;
        }
        if (slash < max_slash)
          for (int i = 0; i < 2 * line; i++)
            printf(" ");
      }
      if (slash < max_slash) {
        printf("/");
        slash++;
      }
      if (slash < max_slash) {
        for (int i = 0; i < 2 * diff; i++)
          printf(" ");
        printf("\\");
        slash++;
      }
      printf("\n");
    }
    line--;
    if (is_keyline(keylines, n, line))
      d--;
  }
  printf("\n");
  free(keylines);
}
