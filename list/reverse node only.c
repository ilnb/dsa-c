#include <stdio.h>

typedef struct node {
  struct node *next;
  int val;
} node;

node *reverse(node *head)
{
  node *prev, *curr, *next;
  prev = NULL;
  curr = head;
  next = head->next;
  while (next) {
    curr->next = prev;
    prev = curr;
    curr = next;
    next = next->next;
  }
  curr->next = prev;
  return curr;
}
