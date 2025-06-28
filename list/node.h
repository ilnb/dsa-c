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

// insert val in a sorted list
node *sortedInsert(node *head, int val) {
  node *p = (node *)malloc(sizeof(*p));
  if (!p)
    return head;
  p->key = val;
  if (!head || val < head->key) {
    p->next = head;
    return p;
  }
  node *q = head;
  while (q->next && val >= q->next->key)
    q = q->next;
  p->next = q->next;
  q->next = p;
  return head;
}

// delete first instance val from a sorted list
node *sortedDelete(node *head, int val) {
  if (!head)
    return head;
  node **nptr = &head;
  while (*nptr && (*nptr)->key < val)
    nptr = &(*nptr)->next;
  if (*nptr && (*nptr)->key == val) {
    node *t = *nptr;
    *nptr = (*nptr)->next;
    free(t);
  }
  return head;
}

// insert val at the head of list
node *insertStart(node *head, int val) {
  node *p = (node *)malloc(sizeof(*p));
  if (!p)
    return head;
  p->key = val;
  p->next = head;
  return p;
}

// insert val at the end of list
node *insertEnd(node *head, int val) {
  node *p = (node *)malloc(sizeof(*p));
  if (!p)
    return head;
  p->key = val;
  p->next = NULL;
  if (!head)
    return p;
  node *q = head;
  while (q->next)
    q = q->next;
  q->next = p;
  return head;
}

// delete first instance of val from list
node *deleteNode(node *head, int val) {
  if (!head)
    return head;
  node **nptr = &head;
  while (*nptr && (*nptr)->key != val)
    nptr = &(*nptr)->next;
  if (*nptr) {
    node *t = *nptr;
    *nptr = (*nptr)->next;
    free(t);
  }
  return head;
}

// deep copy list
node *copyList(node *head) {
  if (!head)
    return NULL;
  node *n = (node *)malloc(sizeof(*n));
  n->key = head->key;
  n->next = NULL;
  node *e = n;
  head = head->next;
  while (head) {
    node *t = (node *)malloc(sizeof(*t));
    t->key = head->key;
    e->next = t;
    e = t;
    head = head->next;
  }
  return n;
}

// print a list
void printList(node *head) {
  while (head) {
    printf("%d->", head->key);
    head = head->next;
  }
  printf("NULL\n");
}

// returns and prints length of a list
int lengthList(node *head) {
  int n = 0;
  while (head) {
    n++;
    head = head->next;
  }
  return n;
}

// free all nodes of a list
node *freeList(node *head) {
  while (head) {
    node *t = head;
    head = head->next;
    free(t);
  }
  return NULL;
}

// free mutliple lists
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

// insert at the start of headnode list
void insertHStart(hnode *h_ptr, int val) {
  node *q = (node *)malloc(sizeof(*q));
  if (!q)
    return;
  q->key = val;
  q->next = h_ptr->start;
  if (!h_ptr->start)
    h_ptr->end = q;
  h_ptr->start = q;
  h_ptr->count++;
}

// insert at the end of headnode list
void insertHEnd(hnode *h_ptr, int val) {
  node *q = (node *)malloc(sizeof(*q));
  if (!q)
    return;
  q->key = val;
  q->next = NULL;
  if (!h_ptr->end)
    h_ptr->start = q;
  else
    h_ptr->end->next = q;
  h_ptr->end = q;
  h_ptr->count++;
}

// delete first instance of val from headnode list
void deleteHnode(hnode *h_ptr, int val) {
  if (!h_ptr->start)
    return;
  if (val == h_ptr->start->key) {
    node *t = h_ptr->start;
    h_ptr->start = t->next;
    free(t);
    if (!h_ptr->start)
      h_ptr->end = NULL;
    h_ptr->count--;
    return;
  }
  node *q = h_ptr->start;
  while (q->next) {
    if (q->next->key == val) {
      node *t = q->next;
      q->next = t->next;
      if (!q->next)
        h_ptr->end = q;
      free(t);
      h_ptr->count--;
      return;
    }
    q = q->next;
  }
}

// returns and prints length of headnode list
int printHCount(hnode h) {
  printf("The length is %d.\n", h.count);
  return h.count;
}

// frees headnode list
void freeHnode(hnode *h_ptr) {
  if (!h_ptr->start)
    return;
  while (h_ptr->start) {
    node *t = h_ptr->start;
    h_ptr->start = t->next;
    free(t);
  }
  memset(h_ptr, 0, sizeof(hnode));
}

// frees mutliple heanode lists
void varFreeHnode(int count, ...) {
  va_list ptr;
  va_start(ptr, count);
  for (int i = 0; i < count; i++)
    freeHnode(va_arg(ptr, hnode *));
  va_end(ptr);
}

typedef struct {
  node *front, *rear;
  int count;
} queue;

// enqueues val to the queue
void enqueue(queue *q_ptr, int val) {
  node *t = (node *)malloc(sizeof(*t));
  if (!t)
    return;
  t->key = val;
  t->next = NULL;
  if (!q_ptr->rear)
    q_ptr->front = t;
  else
    q_ptr->rear->next = t;
  q_ptr->rear = t;
  q_ptr->count++;
}

// dequeues from queue
int dequeue(queue *q_ptr) {
  if (!q_ptr->front)
    return -1;
  node *t = q_ptr->front;
  int n = t->key;
  q_ptr->front = t->next;
  if (!q_ptr->front)
    q_ptr->rear = 0;
  free(t);
  q_ptr->count--;
  return n;
}

// prints the queue
void printQueue(queue q) {
  if (!q.front) {
    printf("The queue is empty.\n");
    return;
  }
  printf("FRONT->");
  while (q.front) {
    printf("%d->", q.front->key);
    q.front = q.front->next;
  }
  printf("\b\b<-REAR\n");
}

// returns and prints length of queue
int printQCount(queue q) {
  printf("The length of queue is %d.\n", q.count);
  return q.count;
}

// frees queue
void freeQueue(queue *q_ptr) {
  if (!q_ptr->front)
    return;
  while (q_ptr->front) {
    node *t = q_ptr->front;
    q_ptr->front = t->next;
    free(t);
  }
  memset(q_ptr, 0, sizeof(queue));
}

// frees mutliple queues
void varFreeQueue(int count, ...) {
  va_list ptr;
  va_start(ptr, count);
  for (int i = 0; i < count; i++)
    free(va_arg(ptr, queue *));
  va_end(ptr);
}

typedef struct stack {
  int key;
  struct stack *next;
} stack;

// pushes val to stack
void push(stack **t, int val) {
  stack *q = (stack *)malloc(sizeof(*q));
  if (!q) {
    printf("Stack overflow.\n");
    return;
  }
  q->key = val;
  q->next = *t;
  *t = q;
}

// pops from stack
int pop(stack **t) {
  if (!*t)
    return -1;
  stack *q = *t;
  int n = q->key;
  *t = (*t)->next;
  free(q);
  return n;
}

// peeks on the stack and returns
int peek(stack *t) {
  if (!t)
    return -1;
  return t->key;
}

// prints the stack
void printStack(stack *t) {
  while (t) {
    printf("%d\n", t->key);
    printf("↓\n");
    t = t->next;
  }
  printf("NULL\n");
}

// frees stack
stack *freeStack(stack *top) {
  while (top) {
    stack *t = top;
    top = top->next;
    free(t);
  }
  return NULL;
}

// frees mutliple stacks
void varFreeStack(int count, ...) {
  va_list ptr;
  va_start(ptr, count);
  for (int i = 0; i < count; i++) {
    stack **t = va_arg(ptr, stack **);
    *t = freeStack(*t);
  }
  va_end(ptr);
}

#endif
