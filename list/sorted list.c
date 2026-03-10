#include "node.h"

void menu() {
  printf("1. Insert\n2. Delete\n3. Display\n4. Free list\n5. Exit\n");
  return;
}

int main() {
  [[gnu::cleanup(free_list)]] node *head = NULL;
  int opt;
  do {
    menu();
    printf("What's on your mind? ");
    scanf("%d", &opt);
    switch (opt) {
    case 1: {
      int val;
      printf("Enter the value you want to insert: ");
      scanf("%d", &val);
      head = sorted_push(head, val);
      break;
    }
    case 2: {
      int val;
      printf("Enter the value you want to delete: ");
      scanf("%d", &val);
      head = sorted_pop(head, val);
      break;
    }
    case 3: {
      print_list(head);
      break;
    }
    case 4:
      free_list(&head);
    case 5:
      break;
    default:
      printf("Invalid opt.\n");
    }
  } while (opt != 5);
  return 0;
}
