#include "node.h"

void reverse(hnode *);

int main()
{
  [[gnu::cleanup(free_hlist)]] hnode h = {0};
  for (int i = 0; i < 5; i++)
    h_push_back(&h, i + 1);
  printf("List right now: ");
  print_list(h.start);
  printf("Address of start: %p\nAddress of end: %p\n", h.start, h.end);
  reverse(&h);
  printf("List reversed: ");
  print_list(h.start);
  printf("Address of start: %p\nAddress of end: %p\n", h.start, h.end);
  return 0;
}

void reverse(hnode *h)
{
  node *prev, *curr, *next;
  prev = NULL;
  curr = h->start;
  next = h->start->next;
  h->end = h->start;
  while (next) {
    curr->next = prev;
    prev = curr;
    curr = next;
    next = next->next;
  }
  curr->next = prev;
  h->start = curr;
}
