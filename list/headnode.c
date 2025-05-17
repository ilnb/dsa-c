#include "node.h"

void menu();

int main(void) {
  hnode h = {0};
  int option;
  do {
    menu();
    printf("What's on your mind? ");
    scanf("%d", &option);
    switch (option) {
      case 1: {
        printf("Enter what to insert: ");
        int val;
        scanf("%d", &val);
        insertHStart(&h, val);
        break;
      }
      case 2: {
        printf("Enter what to insert: ");
        int val;
        scanf("%d", &val);
        insertHEnd(&h, val);
        break;
      }
      case 3: {
        printf("Enter what to delete: ");
        int val;
        scanf("%d", &val);
        deleteHnode(&h, val);
        break;
      }
      case 4: {
        displayList(h.start);
        break;
      }
      case 5: {
        displayHCount(h);
        break;
      }
      case 6:
        freeHnode(&h);
      case 7:
        break;
      default:
        printf("Invalid option.\n");
    }
  } while (option != 7);
  freeHnode(&h);
  return 0;
}

void menu() {
  printf("1. Insert at the start\n");
  printf("2. Insert at the end\n");
  printf("3. Delete node\n");
  printf("4. Display list\n");
  printf("5. Display number of keys\n");
  printf("6. Free the list\n");
  printf("7. Exit\n");
}
