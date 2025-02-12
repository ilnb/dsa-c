#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node {
  int key;
  node *next;
};

typedef struct {
  node *start, *end;
  int count;
} hnode;

void display(hnode);
void initialize(hnode *);
void insert(hnode *, int);
void reverse(hnode *);

int main(void) {
  hnode h;
  initialize(&h);
  for (int i = 0; i < 5; i++) {
    insert(&h, i + 1);
  }
  printf("List right now: ");
  display(h);
  printf("Address of start: %p\nAddress of end: %p\n", h.start, h.end);
  reverse(&h);
  printf("List reversed: ");
  display(h);
  printf("Address of start: %p\nAddress of end: %p\n", h.start, h.end);
  return 0;
}

void reverse(hnode *h_ptr) {
  node *prev, *curr, *next;
  prev = NULL;
  curr = h_ptr->start;
  next = h_ptr->start->next;
  h_ptr->end = h_ptr->start;
  while (next) {
    curr->next = prev;
    prev = curr;
    curr = next;
    next = next->next;
  }
  curr->next = prev;
  h_ptr->start = curr;
}

void display(hnode h) {
  while (h.start) {
    printf("%d->", h.start->key);
    h.start = h.start->next;
  }
  printf("NULL\n");
}

void insert(hnode *h_ptr, int val) {
  node *q = malloc(sizeof(node));
  q->key = val;
  q->next = h_ptr->start;
  if (!h_ptr->start) {
    h_ptr->end = q;
  }
  h_ptr->start = q;
  h_ptr->count++;
}

void initialize(hnode *h_ptr) {
  h_ptr->start = NULL;
  h_ptr->end = NULL;
  h_ptr->count = 0;
}
