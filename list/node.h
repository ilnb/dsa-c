#ifndef _NODE_H
#define _NODE_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  int key;
  struct node *next;
} node;

node *sortedInsert(node *head, int val) {
  node *p = (node *)malloc(sizeof(node));
  p->key = val;
  if (!head || val < head->key) {
    p->next = head;
    return p;
  }
  node *q = head;
  while (q->next && val >= q->next->key) {
    q = q->next;
  }
  p->next = q->next;
  q->next = p;
  return head;
}

node *sortedDelete(node *head, int val) {
  if (!head) {
    printf("Empty list.\n");
    return head;
  }
  node **nptr = &head;
  while (*nptr && (*nptr)->key < val) {
    nptr = &(*nptr)->next;
  }
  if (*nptr && (*nptr)->key == val) {
    node *t = *nptr;
    *nptr = (*nptr)->next;
    free(t);
  }
  return head;
  /*if (val == head->key) {
    node *t = head;
    head = head->next;
    free(t);
    return head;
  }
  node *p = head;
  while (p->next) {
    if (val == p->next->key) {
      node *t = p->next;
      p->next = t->next;
      free(t);
      break;
    } else if (val > p->next->key) {
      p = p->next;
    } else {
      break;
    }
  }
  return head;*/
}

node *insertStart(node *head, int val) {
  node *p = (node *)malloc(sizeof(node));
  p->key = val;
  p->next = head;
  return p;
}

node *insertEnd(node *head, int val) {
  node *p = (node *)malloc(sizeof(node));
  p->key = val;
  p->next = NULL;
  node *q = head;
  while (q && q->next) {
    q = q->next;
  }
  q->next = p;
  return head;
}

node *deleteNode(node *head, int val) {
  if (!head) {
    printf("Empty list.\n");
    return head;
  }
  node **nptr = &head;
  while (*nptr && (*nptr)->key != val) {
    nptr = &(*nptr)->next;
  }
  if (*nptr) {
    node *t = *nptr;
    *nptr = (*nptr)->next;
    free(t);
  }
  return head;
}

void displayList(node *head) {
  if (!head) {
    printf("Empty list.\n");
    return;
  }
  while (head) {
    printf("%d->", head->key);
    head = head->next;
  }
  printf("NULL\n");
}

int lengthList(node *head) {
  if (!head) {
    return 0;
  }
  int n = 0;
  while (head) {
    n++;
    head = head->next;
  }
  return n;
}

node *freeList(node *head) {
  if (!head) {
    printf("Empty list.\n");
    return head;
  }
  while (head) {
    node *t = head;
    head = head->next;
    free(t);
  }
  return NULL;
}

void varFreeList(int count, ...) {
  va_list ptr;
  va_start(ptr, count);
  for (int i = 0; i < count; i++) {
    node **t = va_arg(ptr, node **);
    *t = freeList(*t);
  }
  va_end(ptr);
}

typedef struct {
  node *start, *end;
  int count;
} hnode;

void initHnode(hnode *h) {
  memset(h, 0, sizeof(hnode));
  return;
}

void insertHStart(hnode *h_ptr, int val) {
  node *q = (node *)malloc(sizeof(node));
  if (!q) {
    printf("Out of memory.\n");
  }
  q->key = val;
  q->next = h_ptr->start;
  if (!h_ptr->start) {
    h_ptr->end = q;
  }
  h_ptr->start = q;
  h_ptr->count++;
}

void insertHEnd(hnode *h_ptr, int val) {
  node *q = (node *)malloc(sizeof(node));
  if (!q) {
    printf("Out of memory.\n");
  }
  q->key = val;
  q->next = NULL;
  if (!h_ptr->end) {
    h_ptr->start = q;
  } else {
    h_ptr->end->next = q;
  }
  h_ptr->end = q;
  h_ptr->count++;
}

void deleteHnode(hnode *h_ptr, int val) {
  if (!h_ptr->start) {
    printf("Empty list.\n");
    return;
  }
  if (val == h_ptr->start->key) {
    node *t = h_ptr->start;
    h_ptr->start = t->next;
    free(t);
    h_ptr->count--;
    return;
  }
  node *q = h_ptr->start;
  while (q->next) {
    if (q->next->key == val) {
      node *t = q->next;
      q->next = t->next;
      free(t);
      h_ptr->count--;
      return;
    }
    q = q->next;
  }
}

int displayHCount(hnode h) {
  printf("The length is %d.\n", h.count);
  return h.count;
}

void freeHnode(hnode *h_ptr) {
  if (!h_ptr->start) {
    printf("Empty list.");
    return;
  }
  while (h_ptr->start) {
    node *t = h_ptr->start;
    h_ptr->start = t->next;
    free(t);
  }
  memset(h_ptr, 0, sizeof(hnode));
}

void varFreeHnode(int count, ...) {
  va_list ptr;
  va_start(ptr, count);
  for (int i = 0; i < count; i++) {
    freeHnode(va_arg(ptr, hnode *));
  }
}

typedef struct {
  node *front, *rear;
  int count;
} queue;

void initQueue(queue *q) {
  q->front = NULL;
  q->rear = NULL;
  q->count = 0;
}

void enqueue(queue *q_ptr, int val) {
  node *t = (node *)malloc(sizeof(node));
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
  q_ptr->front = t->next;
  free(t);
  q_ptr->count--;
  return n;
}

void displayQueue(queue q) {
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

void displayQCount(queue q) {
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
    q_ptr->front = t->next;
    free(t);
  }
  memset(q_ptr, 0, sizeof(queue));
}

void varFreeQueue(int count, ...) {
  va_list ptr;
  va_start(ptr, count);
  for (int i = 0; i < count; i++) {
    free(va_arg(ptr, queue *));
  }
}

typedef struct stack {
  int key;
  struct stack *next;
} stack;

void push(stack **t, int val) {
  stack *q = (stack *)malloc(sizeof(stack));
  if (!q) {
    printf("Stack overflow.\n");
    return;
  }
  q->key = val;
  q->next = *t;
  *t = q;
  return;
}

int pop(stack **t) {
  if (!*t) {
    printf("Stack is empty.\n");
    return -1;
  }
  stack *q = *t;
  int n = q->key;
  *t = (*t)->next;
  free(q);
  return n;
}

int peek(stack *t) {
  if (!t) {
    printf("Stack is empty.\n");
    return -1;
  }
  return t->key;
}

void displayStack(stack *t) {
  while (t) {
    printf("%d\n", t->key);
    printf("↓\n");
    t = t->next;
  }
  printf("NULL\n");
}

stack *freeStack(stack *top) {
  if (!top) {
    printf("Empty list.\n");
    return top;
  }
  while (top) {
    stack *t = top;
    top = top->next;
    free(t);
  }
  return top;
}

void varFreeStack(int count, ...) {
  va_list ptr;
  va_start(ptr, count);
  for (int i = 0; i < count; i++) {
    stack **t = va_arg(ptr, stack **);
    *t = freeStack(*t);
  }
}

#endif
