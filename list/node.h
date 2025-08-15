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
    e = e->next = t;
    head = head->next;
  }
  return n;
}

// print a list
void printList(node *head) {
  for (; head; head = head->next)
    printf("%d->", head->key);
  printf("NULL\n");
}

// returns and prints length of a list
int lengthList(node *head) {
  int n = 0;
  for (; head; head = head->next)
    ++n;
  return n;
}

// frees all nodes of a list
node *freeList(node *head) {
  while (head) {
    node *t = head;
    head = head->next;
    free(t);
  }
  return NULL;
}

// frees mutliple lists
#define varFreeList(...)                                                       \
  __varFreeList((node **[]){__VA_ARGS__},                                      \
                sizeof((node **[]){__VA_ARGS__}) / sizeof(node **))

void __varFreeList(node **lists[], size_t count) {
  for (size_t i = 0; i < count; i++)
    *lists[i] = freeList(*lists[i]);
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
inline int printHCount(hnode h) { return h.count; }

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

// frees mutliple headnode lists
#define varFreeHnode(...)                                                      \
  __varFreeHnode((hnode **[]){__VA_ARGS__},                                    \
                 sizeof((hnode **[]){__VA_ARGS__}) / sizeof(hnode **))

void __varFreeHnode(hnode **lists[], size_t count) {
  for (size_t i = 0; i < count; i++)
    freeHnode(*lists[i]);
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
  for (; q.front; q.front = q.front->next)
    q.front = q.front->next;
  printf("\b\b<-REAR\n");
}

// returns and prints length of queue
inline int printQCount(queue q) { return q.count; }

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
#define varFreeQueue(...)                                                      \
  __varFreeQueue((queue *[]){__VA_ARGS__},                                     \
                 sizeof((queue *[]){__VA_ARGS__}) / sizeof(queue *))

void __varFreeQueue(queue *queues[], size_t count) {
  for (size_t i = 0; i < count; ++i)
    freeQueue(queues[i]);
}

typedef struct stack {
  int key;
  struct stack *next;
} stack;

// pushes val to stack
void push(stack **t, int val) {
  stack *q = (stack *)malloc(sizeof(*q));
  if (!q)
    return;
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
inline int peek(stack *t) {
  if (!t)
    return -1;
  return t->key;
}

// prints the stack
void printStack(stack *t) {
  for (; t; t = t->next)
    printf("%d\n↓\n", t->key);
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
#define varFreeStack(...)                                                      \
  __varFreeStack((stack **[]){__VA_ARGS__},                                    \
                 sizeof((stack **[]){__VA_ARGS__}) / sizeof(stack **))

void __varFreeStack(stack **stacks[], size_t count) {
  for (size_t i = 0; i < count; ++i)
    *stacks[i] = freeStack(*stacks[i]);
}

#endif
