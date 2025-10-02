#include <stdio.h>

void printMenu();
int search(int *, int, int);
void insert(int *, int *, int);
void delete(int *, int *, int);
void update(int *, int, int);
void printArr(int *, int);

int main(void) {
  int arr[50] = {2, 3, 5, 1, 6}, n = 5, option = 0;
  while (1) {
    printMenu();
    printf("Enter the option: ");
    scanf("%d", &option);
    switch (option) {
      case 1: {
        printArr(arr, n);
        break;
      }
      case 2: {
        printf("Enter the value: ");
        int val;
        scanf("%d", &val);
        if (search(arr, n, val) == -1)
          printf("Value not found\n");
        else
          printf("Value found at index: %d\n", search(arr, n, val));
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
        int index, val;
        printf("Enter the index to be updated: ");
        scanf("%d", &index);
        printf("Enter the new value: ");
        scanf("%d", &val);
        update(arr, index, val);
        break;
      }
      case 6:
        break;
      default:
        printf("Option not found!\n");
        break;
    }
    if (option == 6)
      break;
  }
  return 0;
}

void printMenu() {
  printf("1. Print the array\n");
  printf("2. Search a value\n");
  printf("3. Insert a value\n");
  printf("4. Delete the value at an index\n");
  printf("5. Update the value at an index\n");
  printf("6. Exit\n");
}

int search(int *arr, int size, int value) {
  for (int i = 0; i < size; i++)
    if (arr[i] == value)
      return i;
  return -1;
}

void insert(int *arr, int *size, int value) { arr[(*size)++] = value; }

void delete(int *arr, int *size, int index) {
  for (int i = index; i < *size; i++)
    arr[i] = arr[i + 1];
  --*size;
}

void update(int *arr, int index, int value) { arr[index] = value; }

void printArr(int *arr, int size) {
  printf("The array is:\n");
  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}
