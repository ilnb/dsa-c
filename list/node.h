#ifndef _NODE_H
#define _NODE_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  struct node *next;
  int val;
} node;

// insert val in a sorted list
static inline node *sorted_push(node *head, int val) {
  node *p = (node *)malloc(sizeof *p);
  if (!p)
    return head;
  p->val = val;
  if (!head || val < head->val) {
    p->next = head;
    return p;
  }
  node *q = head;
  while (q->next && val >= q->next->val)
    q = q->next;
  p->next = q->next;
  q->next = p;
  return head;
}

// delete first instance val from a sorted list
static inline node *sorted_pop(node *head, int val) {
  node **nptr = &head;
  while (*nptr && (*nptr)->val < val)
    nptr = &(*nptr)->next;
  if (*nptr && (*nptr)->val == val) {
    node *t = *nptr;
    *nptr = (*nptr)->next;
    free(t);
  }
  return head;
}

// insert val at the head of list
static inline node *push_front(node *head, int val) {
  node *p = (node *)malloc(sizeof *p);
  if (!p)
    return head;
  p->val = val;
  p->next = head;
  return p;
}

// insert val at the end of list
static inline node *push_back(node *head, int val) {
  node *p = (node *)malloc(sizeof *p);
  if (!p)
    return head;
  p->val = val;
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
static inline node *pop_node(node *head, int val) {
  node **nptr = &head;
  while (*nptr && (*nptr)->val != val)
    nptr = &(*nptr)->next;
  if (*nptr) {
    node *t = *nptr;
    *nptr = (*nptr)->next;
    free(t);
  }
  return head;
}

// deep copy list
static inline node *clone(node *head) {
  if (!head)
    return NULL;
  node *n = (node *)malloc(sizeof *n);
  n->val = head->val;
  n->next = NULL;
  node *e = n;
  head = head->next;
  while (head) {
    node *t = (node *)malloc(sizeof *t);
    t->val = head->val;
    e = e->next = t;
    head = head->next;
  }
  return n;
}

// print a list
static inline void print_list(node *head) {
  for (; head; head = head->next)
    printf("%d->", head->val);
  printf("NULL\n");
}

// returns and prints ngth of a list
static inline int len_list(node *head) {
  int n = 0;
  for (; head; head = head->next, ++n)
    ;
  return n;
}

// frees all nodes of a list
static inline void free_list(node **ptr) {
  node *first = *ptr;
  if (!first)
    return;
  while (first) {
    node *t = first;
    first = first->next;
  }
  *ptr = 0;
}

// frees mutliple lists
#define var_free_list(...)                                                                         \
  _var_free_list((node **[]){__VA_ARGS__}, sizeof((node **[]){__VA_ARGS__}) / sizeof(node **))

static inline void _var_free_list(node **lists[], size_t count) {
  for (size_t i = 0; i < count; i++)
    free_list(lists[i]);
}

typedef struct {
  node *start, *end;
  int len;
} hnode;

// insert at the start of headnode list
static inline void h_push_front(hnode *h, int val) {
  node *q = (node *)malloc(sizeof *q);
  if (!q)
    return;
  q->val = val;
  q->next = h->start;
  if (!h->start)
    h->end = q;
  h->start = q;
  h->len++;
}

// insert at the end of headnode list
static inline void h_push_back(hnode *h, int val) {
  node *q = (node *)malloc(sizeof *q);
  if (!q)
    return;
  q->val = val;
  q->next = NULL;
  if (!h->end)
    h->start = q;
  else
    h->end->next = q;
  h->end = q;
  h->len++;
}

// delete first instance of val from headnode list
static inline void h_del_node(hnode *h, int val) {
  if (!h->start)
    return;
  if (val == h->start->val) {
    node *t = h->start;
    h->start = t->next;
    free(t);
    if (!h->start)
      h->end = NULL;
    h->len--;
    return;
  }
  node *q = h->start;
  while (q->next) {
    if (q->next->val == val) {
      node *t = q->next;
      q->next = t->next;
      if (!q->next)
        h->end = q;
      free(t);
      h->len--;
      return;
    }
    q = q->next;
  }
}

// frees headnode list
static inline void free_hlist(hnode *h) {
  if (!h->start)
    return;
  while (h->start) {
    node *t = h->start;
    h->start = t->next;
    free(t);
  }
  memset(h, 0, sizeof *h);
}

// frees mutliple headnode lists
#define var_free_hlist(...)                                                                        \
  _var_free_hlist((hnode **[]){__VA_ARGS__}, sizeof(hnode * *[]){__VA_ARGS__}) / sizeof(hnode **)

static inline void _var_free_hlist(hnode **lists[], size_t count) {
  for (size_t i = 0; i < count; i++)
    free_hlist(*lists[i]);
}

typedef struct {
  node *front, *rear;
  int len;
} queue;

// enqueues val to the queue
static inline void enqueue(queue *q, int val) {
  node *t = (node *)malloc(sizeof *t);
  if (!t)
    return;
  t->val = val;
  t->next = NULL;
  if (!q->rear)
    q->front = t;
  else
    q->rear->next = t;
  q->rear = t;
  q->len++;
}

// dequeues from queue
static inline int dequeue(queue *q) {
  if (!q->front)
    return -1;
  node *t = q->front;
  int n = t->val;
  q->front = t->next;
  if (!q->front)
    q->rear = 0;
  free(t);
  q->len--;
  return n;
}

// prints the queue
static inline void print_queue(queue *q) {
  if (!q->front) {
    printf("The queue is empty.\n");
    return;
  }
  printf("FRONT->");
  for (; q->front; q->front = q->front->next)
    q->front = q->front->next;
  printf("\b\b<-REAR\n");
}

// frees queue
static inline void free_queue(queue *q) {
  if (!q->front)
    return;
  while (q->front) {
    node *t = q->front;
    q->front = t->next;
    free(t);
  }
  memset(q, 0, sizeof *q);
}

// frees mutliple queues
#define var_free_queue(...)                                                                        \
  _var_free_queue((queue *[]){__VA_ARGS__}, sizeof(queue *[]){__VA_ARGS__}) / sizeof(queue *)

static inline void _var_free_queue(queue *queues[], size_t count) {
  for (size_t i = 0; i < count; ++i)
    free_queue(queues[i]);
}

typedef struct stack {
  struct stack *next;
  int val;
} stack;

// pushes val to stack
static inline void push(stack **t, int val) {
  stack *q = (stack *)malloc(sizeof *q);
  if (!q)
    return;
  q->val = val;
  q->next = *t;
  *t = q;
}

// pops from stack
static inline int pop(stack **t) {
  if (!*t)
    return -1;
  stack *q = *t;
  int n = q->val;
  *t = (*t)->next;
  free(q);
  return n;
}

// peeks on the stack and returns
static inline int peek(stack *t) {
  if (!t)
    return -1;
  return t->val;
}

// prints the stack
static inline void print_stack(stack *t) {
  for (; t; t = t->next)
    printf("%d\n↓\n", t->val);
  printf("NULL\n");
}

// frees stack
static inline void free_stack(stack **ptr) {
  stack *first = *ptr;
  if (!first)
    return;
  while (first) {
    stack *t = first;
    first = first->next;
  }
  *ptr = 0;
}

// frees mutliple stacks
#define var_free_stack(...)                                                                        \
  _var_free_stack((stack **[]){__VA_ARGS__}, sizeof(stack * *[]){__VA_ARGS__}) / sizeof(stack **)

static inline void _var_free_stack(stack **stacks[], size_t count) {
  for (size_t i = 0; i < count; ++i)
    free_stack(stacks[i]);
}

#endif
