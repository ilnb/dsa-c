#include <stdio.h>

void printMenu();
int search(int *, int, int);
void insertValue(int *, int *, int);
void deleteIndex(int *, int *, int);
void updateIndex(int *, int, int, int);
void print(int *, int);

int main(void) {
  int arr[50] = {1, 2, 3, 4, 5}, n = 5, option = 0;
  while (1) {
    printMenu();
    printf("Enter the option: ");
    scanf("%d", &option);
    switch (option) {
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
        insertValue(arr, &n, val);
        break;
      }
      case 4: {
        printf("Enter the index to be deleted: ");
        int i;
        scanf("%d", &i);
        deleteIndex(arr, &n, i);
        break;
      }
      case 5: {
        int val, i;
        printf("Enter the index to be updated: ");
        scanf("%d", &i);
        printf("Enter the new value: ");
        scanf("%d", &val);
        updateIndex(arr, n, i, val);
        break;
      }
      case 6:
        break;
      default:
        printf("Option not found!\n");
        break;
    }
    if (option == 6) {
      break;
    }
  }
  return 0;
}

void printMenu() {
  printf("1. Print the array\n");
  printf("2. Search a value\n");
  printf("3. Insert a value\n");
  printf("4. Delete a value\n");
  printf("5. Update the value at an index\n");
  printf("6. Exit\n");
}

void print(int *arr, int len) {
  printf("The array is:\n");
  for (int i = 0; i < len; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

int search(int *arr, int len, int value) {
  int low = 0, high = len - 1;
  int mid = (low + high) / 2;
  while (low <= len) {
    if (value < arr[mid])
      len = mid - 1;
    else if (value > arr[mid])
      low = mid + 1;
    else {
      printf("Value found at index: %d\n", mid);
      return mid;
    }
  }
  printf("Value not found\n");
  return -1;
}

void insertValue(int *arr, int *lenPtr, int value) {
  if (value > arr[*lenPtr - 1]) {
    // largest number
    arr[*lenPtr] = value;
    ++*lenPtr;
  } else {
    int i = 0;
    for (int j = 1; j < *lenPtr; j++) {
      if (arr[j - 1] <= value && value < arr[j]) {
        // find the appropriate position
        i = j;
        break;
      }
    }
    // shift the values to right,
    // starting from the end
    for (int j = *lenPtr; j > i; j--)
      arr[j] = arr[j - 1];
    // put the value
    arr[i] = value;
    ++*lenPtr;
  }
}

void deleteIndex(int *arr, int *lenPtr, int index) {
  if (index == *lenPtr - 1) {
    // largest entry
    --*lenPtr;
    return;
  }
  for (int j = index; j < *lenPtr - 1; j++) {
    // shift the values to left
    arr[j] = arr[j + 1];
  }
  --*lenPtr;
}

void updateIndex(int *arr, int len, int index, int value) {
  int val = arr[index];
  deleteIndex(arr, &len, index);
  insertValue(arr, &len, val);
}
