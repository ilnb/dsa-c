#include "node.h"

void menu();

int main(void) {
  queue q = {0};
  int option;
  do {
    menu();
    printf("What's on your mind? ");
    scanf("%d", &option);
    switch (option) {
      case 1: {
        printf("Enter the value to be enqueued: ");
        int val;
        scanf("%d", &val);
        enqueue(&q, val);
        break;
      }
      case 2: {
        int n = dequeue(&q);
        if (n != -1)
          printf("Value dequeued: %d.\n", n);
        else
          printf("Empty queue.\n");
        break;
      }
      case 3: {
        displayQueue(q);
        break;
      }
      case 4: {
        displayQCount(q);
        break;
      }
      case 5: {
        freeQueue(&q);
        break;
      }
      case 6: {
        break;
      }
      default: {
        printf("Invalid option.\n");
      }
    }
  } while (option != 6);
  freeQueue(&q);
  return 0;
}

void menu() {
  printf("1. Enqueue\n");
  printf("2. Dequeue\n");
  printf("3. Display\n");
  printf("4. Display count\n");
  printf("5. Free the queue\n");
  printf("6. Exit\n");
}
