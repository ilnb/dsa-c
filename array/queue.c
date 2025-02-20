#include <stdio.h>
#define MAX 20

typedef struct {
  int arr[MAX];
  int front;
  int rear;
} queue;

void menu();
void enqueue(queue *, int);
int dequeue(queue *);
void display(queue);
int isFull(queue);
int isEmpty(queue);

int main(void) {
  queue q;
  q.front = -1;
  q.rear = 0;
  while (1) {
    menu();
    printf("Enter an appropriate option: ");
    int option;
    scanf("%d", &option);
    switch (option) {
      case 1: {
        printf("Enter the value to be queued: ");
        int val;
        scanf("%d", &val);
        enqueue(&q, val);
        printf("The updated queue:\n");
        display(q);
        break;
      }
      case 2: {
        int i = dequeue(&q);
        if (i != -273) {
          printf("The value dequeued is %d.\n", i);
          printf("The updated queue:\n");
          display(q);
        }
        break;
      }
      case 3: {
        printf("The queue is:\n");
        display(q);
        break;
      }
      case 4: {
        break;
      }
      default: {
        printf("Invalid option.\n");
        break;
      }
    }
    if (option == 4) {
      break;
    }
  }
  return 0;
}

void menu() {
  printf("1. Inqueue\n");
  printf("2. Dequeue\n");
  printf("3. Display\n");
  printf("4. Exit\n");
  printf("What do you want to do? ");
}

void enqueue(queue *q, int val) {
  if (isFull(*q)) {
    printf("The queue is full");
  } else {
    q->arr[q->rear] = val;
    q->rear = (q->rear + 1) % MAX;
  }
}

int dequeue(queue *q) {
  if (isEmpty(*q)) {
    printf("The queue is empty.\n");
    return -273;
  } else {
    q->front = (q->front + 1) % MAX;
    return q->arr[q->front];
  }
}

void display(queue q) {
  if (isEmpty(q)) {
    printf("The queue is empty.\n");
    return;
  }
  int i = q.front + 1;
  while (i != q.rear) {
    printf("%d ", q.arr[i]);
    i = (i + 1) % MAX;
  }
  printf("\n");
}

int isFull(queue q) {
  if ((q.rear + 1) % MAX == q.front) {
    return 1;
  }
  return 0;
}

int isEmpty(queue q) {
  if (q.front + 1 == q.rear) {
    return 1;
  }
  return 0;
}
