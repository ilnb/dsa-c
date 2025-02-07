#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node {
  int key;
  node *next;
};

typedef struct {
  node *front, *rear;
  int count;
} queue;

void menu();
void initialize(queue *);
void enqueue(queue *, int);
int dequeue(queue *);
void display(queue);
void displayCount(queue);
void freeQueue(queue *);

int main(void) {
  queue q;
  initialize(&q);
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
      if (n != -1) {
        printf("Value dequeued: %d.\n", n);
      }
      break;
    }
    case 3: {
      display(q);
      break;
    }
    case 4: {
      displayCount(q);
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

void initialize(queue *q) {
  q->front = NULL;
  q->rear = NULL;
  q->count = 0;
}

void enqueue(queue *q_ptr, int val) {
  node *t = malloc(sizeof(node));
  if (!t) {
    printf("Queue overflow.\n");
    return;
  }
  t->key = val;
  t->next = NULL;
  if (!q_ptr->rear) {
    q_ptr->front = t;
  } else {
    q_ptr->rear->next = t;
  }
  q_ptr->rear = t;
  q_ptr->count++;
}

int dequeue(queue *q_ptr) {
  if (!q_ptr->front) {
    printf("The queue is empty.\n");
    return -1;
  }
  node *t = q_ptr->front;
  int n = t->key;
  q_ptr->front = q_ptr->front->next;
  free(t);
  q_ptr->count--;
  return n;
}

void display(queue q) {
  if (!q.front) {
    printf("The queue is empty.\n");
    return;
  }
  printf("FRONT->");
  while (q.front) {
    printf("%d->", q.front->key);
    q.front = q.front->next;
  }
  printf("NULL\n");
}

void displayCount(queue q) {
  printf("The length of queue is %d.\n", q.count);
  return;
}

void freeQueue(queue *q_ptr) {
  if (!q_ptr->front) {
    printf("Empty list.\n");
    return;
  }
  while (q_ptr->front) {
    node *t = q_ptr->front;
    q_ptr->front = q_ptr->front->next;
    free(t);
  }
  q_ptr->rear = NULL;
  q_ptr->count = 0;
}
