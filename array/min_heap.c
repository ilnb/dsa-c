#include <stdio.h>
#include <stdlib.h>
#define MAX 30

static inline int ln2c(size_t);
static inline void swap(int *, int *);
void menu();
void mk_min_heap(int *, size_t);
void min_heapify(int *, size_t, int);
void push(int *, size_t *, int);
int pop_min(int *, size_t *);
int is_keyline(int *, size_t, int);
void print_heap(int *, size_t);

int main() {
  int arr[MAX];
  size_t n = 15;
  arr[0] = 4, arr[1] = 10, arr[2] = 1;
  arr[3] = 5, arr[4] = 3, arr[5] = 6, arr[6] = 2;
  arr[7] = 8, arr[8] = 10, arr[9] = 7, arr[10] = 12;
  arr[11] = 13, arr[12] = 11, arr[13] = 12;
  mk_min_heap(arr, n);
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
      int t = pop_min(arr, &n);
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

int ln2c(size_t n) {
  int v = 0;
  while (n) {
    n >>= 1;
    v++;
  }
  return v;
}

void swap(int *a, int *b) {
  int t = *b;
  *b = *a;
  *a = t;
}

void print_arr(int *arr, int n) {
  for (int i = 0; i < n; i++)
    printf("%3d", arr[i]);
  printf("\n");
}

void menu() {
  printf("1. Insert value\n");
  printf("2. Delete min value\n");
  printf("3. Print heap\n");
  printf("4. Exit\n");
}

void mk_min_heap(int *arr, size_t n) {
  int i = n / 2 - 1;
  while (i >= 0)
    min_heapify(arr, n, i--);
}

void min_heapify(int *arr, size_t n, int i) {
  while (1) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int p = i;
    if (l < n && arr[l] < arr[p])
      p = l;
    if (r < n && arr[r] < arr[p])
      p = r;
    if (p == i)
      break;
    swap(arr + i, arr + p);
    i = p;
  }
}

void push(int *arr, size_t *n, int val) {
  arr[(*n)++] = val;
  int i = *n - 1;
  while (i) {
    int p = (i - 1) / 2;
    if (arr[p] < arr[i])
      break;
    swap(arr + p, arr + i);
    i = p;
  }
}

int pop_min(int *arr, size_t *n) {
  if (*n) {
    int t = arr[0];
    swap(arr, arr + --*n);
    min_heapify(arr, *n, 0);
    return t;
  }
  return -1;
}

int is_keyline(int *keylines, size_t n, int line) {
  int d = ln2c(n);
  for (int i = d - 1; i >= 0; i--)
    if (line == keylines[i])
      return 1;
  return 0;
}

void print_heap(int *arr, size_t n) {
  if (!n)
    return;
  if (n == 1) {
    printf("%d\n", arr[0]);
    return;
  }
  int d = ln2c(n);
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
    int ln = ln2c(n) - d;
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
      size_t nr = 2 * r + 2;
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
