#include "node.h"

void menu();

int main() {
  [[gnu::cleanup(free_queue)]] queue q = {0};
  int opt;
  do {
    menu();
    printf("What's on your mind? ");
    scanf("%d", &opt);
    switch (opt) {
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
      print_queue(&q);
      break;
    }
    case 4: {
      printf("Length of queue is %d\n", q.len);
      break;
    }
    case 5:
      free_queue(&q);
    case 6:
      break;
    default:
      printf("Invalid opt.\n");
    }
  } while (opt != 6);
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
