#include <stdio.h>

void print_menu();
int search(int *, int, int);
void insert_val(int *, int *, int);
void delete_idx(int *, int *, int);
void update_idx(int *, int, int, int);
void print(int *, int);

int main()
{
  int arr[50] = {1, 2, 3, 4, 5}, n = 5, opt = 0;
  while (1) {
    print_menu();
    printf("Enter the option: ");
    scanf("%d", &opt);
    switch (opt) {
    case 1:
      print(arr, n);
      break;
    case 2: {
      printf("Enter the value: ");
      int val;
      scanf("%d", &val);
      search(arr, n, val);
      break;
    }
    case 3: {
      printf("Enter the value to be inserted: ");
      int val;
      scanf("%d", &val);
      insert_val(arr, &n, val);
      break;
    }
    case 4: {
      printf("Enter the index to be deleted: ");
      int i;
      scanf("%d", &i);
      delete_idx(arr, &n, i);
      break;
    }
    case 5: {
      int val, i;
      printf("Enter the index to be updated: ");
      scanf("%d", &i);
      printf("Enter the new value: ");
      scanf("%d", &val);
      update_idx(arr, n, i, val);
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
  printf("4. Delete a value\n");
  printf("5. Update the value at an index\n");
  printf("6. Exit\n");
}

void print(int *arr, int n)
{
  printf("The array is:\n");
  for (int i = 0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

int search(int *arr, int n, int val)
{
  int low = 0, high = n - 1;
  int mid = (low + high) / 2;
  while (low <= n) {
    if (val == arr[mid]) {
      printf("Value found at index: %d\n", mid);
      return mid;
    } else if (val > arr[mid])
      low = mid + 1;
    else
      n = mid - 1;
  }
  printf("Value not found\n");
  return -1;
}

void insert_val(int *arr, int *n, int val)
{
  if (val > arr[*n - 1]) {
    // largest number
    arr[*n] = val;
    ++*n;
  } else {
    int i = 0;
    for (int j = 1; j < *n; j++) {
      if (arr[j - 1] <= val && val < arr[j]) {
        // find the appropriate position
        i = j;
        break;
      }
    }
    // shift the values to right,
    // starting from the end
    for (int j = *n; j > i; j--)
      arr[j] = arr[j - 1];
    // put the value
    arr[i] = val;
    ++*n;
  }
}

void delete_idx(int *arr, int *n, int i)
{
  // invalid index
  if (i >= *n)
    return;
  if (i == *n - 1) {
    // largest entry
    --*n;
    return;
  }
  // shift the values to left
  for (int j = i; j < *n - 1; j++)
    arr[j] = arr[j + 1];
  --*n;
}

void update_idx(int *arr, int n, int i, int val)
{
  if (i >= n)
    return;
  delete_idx(arr, &n, i);
  insert_val(arr, &n, val);
}
