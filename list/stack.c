#include "node.h"

void menu();

int main(void) {
  stack *top = NULL;
  int option;
  do {
    menu();
    printf("What's on your mind? ");
    scanf("%d", &option);
    switch (option) {
      case 1: {
        printf("Enter the value to push: ");
        int val;
        scanf("%d", &val);
        push(&top, val);
        break;
      }
      case 2: {
        int n = pop(&top);
        if (n != -1)
          printf("Value popped is %d.\n", n);
        else
          printf("Empty stack\n");
        break;
      }
      case 3: {
        int n = peek(top);
        if (n != -1)
          printf("Value at the top is %d.\n", n);
        else
          printf("Empty stack\n");
        break;
      }
      case 4: {
        printStack(top);
        break;
      }
      case 5:
        top = freeStack(top);
      case 6:
        break;
      default:
        printf("Invalid option.\n");
    }
  } while (option != 5);
  top = freeStack(top);
  return 0;
}

void menu() {
  printf("1. Push\n");
  printf("2. Pop\n");
  printf("3. Peek\n");
  printf("4. Display\n");
  printf("5. Free stack\n");
  printf("6. Exit\n");
}
