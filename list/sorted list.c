#include "node.h"

void menu() {
  printf("1. Insert\n2. Delete\n3. Display\n4. Free list\n5. Exit\n");
  return;
}

int main(void) {
  node *head = NULL;
  int option;
  do {
    menu();
    printf("What's on your mind? ");
    scanf("%d", &option);
    switch (option) {
      case 1: {
        int val;
        printf("Enter the value you want to insert: ");
        scanf("%d", &val);
        head = sortedInsert(head, val);
        break;
      }
      case 2: {
        int val;
        printf("Enter the value you want to delete: ");
        scanf("%d", &val);
        head = sortedDelete(head, val);
        break;
      }
      case 3: {
        displayList(head);
        break;
      }
      case 4:
        head = freeList(head);
      case 5:
        break;
      default:
        printf("Invalid option.\n");
    }
  } while (option != 5);
  head = freeList(head);
  return 0;
}
