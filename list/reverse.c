#include "node.h"

void reverse(hnode *);

int main(void) {
  hnode h;
  initHnode(&h);
  for (int i = 0; i < 5; i++) {
    insertHEnd(&h, i + 1);
  }
  printf("List right now: ");
  displayList(h.start);
  printf("Address of start: %p\nAddress of end: %p\n", h.start, h.end);
  reverse(&h);
  printf("List reversed: ");
  displayList(h.start);
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
