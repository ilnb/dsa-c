#include <stdio.h>

void print_menu();
int search(int *, int, int);
void insert(int *, int *, int);
void delete(int *, int *, int);
void update(int *, int, int);
void print_arr(int *, int);

int main()
{
  int arr[50] = {2, 3, 5, 1, 6}, n = 5, opt = 0;
  while (1) {
    print_menu();
    printf("Enter the option: ");
    scanf("%d", &opt);
    switch (opt) {
    case 1: {
      print_arr(arr, n);
      break;
    }
    case 2: {
      printf("Enter the value: ");
      int val;
      scanf("%d", &val);
      int ret = search(arr, n, val);
      if (ret == -1)
        printf("Value not found\n");
      else
        printf("Value found at index: %d\n", ret);
      break;
    }
    case 3: {
      printf("Enter the value to be inserted: ");
      int val;
      scanf("%d", &val);
      insert(arr, &n, val);
      break;
    }
    case 4: {
      printf("Enter the index to be deleted: ");
      int index;
      scanf("%d", &index);
      delete(arr, &n, index);
      break;
    }
    case 5: {
      int i, val;
      printf("Enter the index to be updated: ");
      scanf("%d", &i);
      printf("Enter the new value: ");
      scanf("%d", &val);
      update(arr, i, val);
      break;
    }
    case 6:
      break;
    default:
      printf("Option not found!\n");
      break;
    }
    if (opt == 6)
      break;
  }
  return 0;
}

void print_menu()
{
  printf("1. Print the array\n");
  printf("2. Search a value\n");
  printf("3. Insert a value\n");
  printf("4. Delete the value at an index\n");
  printf("5. Update the value at an index\n");
  printf("6. Exit\n");
}

int search(int *arr, int n, int val)
{
  for (int i = 0; i < n; i++)
    if (arr[i] == val)
      return i;
  return -1;
}

void insert(int *arr, int *n, int val) { arr[(*n)++] = val; }

void delete(int *arr, int *n, int i)
{
  if (i >= *n)
    return;
  for (int i = i; i < *n; i++)
    arr[i] = arr[i + 1];
  --*n;
}

void update(int *arr, int i, int val) { arr[i] = val; }

void print_arr(int *arr, int n)
{
  printf("The array is:\n");
  for (int i = 0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");
}
