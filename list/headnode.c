#include "node.h"

void menu();

int main() {
  [[gnu::cleanup(free_hlist)]] hnode h = {0};
  int opt;
  do {
    menu();
    printf("What's on your mind? ");
    scanf("%d", &opt);
    switch (opt) {
    case 1: {
      printf("Enter what to insert: ");
      int val;
      scanf("%d", &val);
      h_push_front(&h, val);
      break;
    }
    case 2: {
      printf("Enter what to insert: ");
      int val;
      scanf("%d", &val);
      h_push_back(&h, val);
      break;
    }
    case 3: {
      printf("Enter what to delete: ");
      int val;
      scanf("%d", &val);
      h_del_node(&h, val);
      break;
    }
    case 4: {
      print_list(h.start);
      break;
    }
    case 5: {
      printf("Length of list is %d\n", h.len);
      break;
    }
    case 6:
      free_hlist(&h);
    case 7:
      break;
    default:
      printf("Invalid opt.\n");
    }
  } while (opt != 7);
  return 0;
}

void menu() {
  printf("1. Insert at the start\n");
  printf("2. Insert at the end\n");
  printf("3. Delete node\n");
  printf("4. Display list\n");
  printf("5. Display number of vals\n");
  printf("6. Free the list\n");
  printf("7. Exit\n");
}
