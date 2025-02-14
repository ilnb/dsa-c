#include "node.h"

node *inSort(node *);

int main(void) {
  node *head = NULL;
  head = insertStart(head, 2);
  head = insertStart(head, 1);
  head = insertStart(head, 5);
  head = insertStart(head, 3);
  head = insertStart(head, 4);
  printf("List right now: ");
  displayList(head);
  head = inSort(head);
  printf("Sorted list: ");
  displayList(head);
  head = freeList(head);
  return 0;
}

node *inSort(node *head) {
  if (!head) {
    return head;
  }
  node *p = head;
  while (p) {
    node *q, *t;
    q = p->next;
    t = p;
    while (q) {
      if (q->key < t->key) {
        t = q;
      }
      q = q->next;
    }
    int c = t->key;
    t->key = p->key;
    p->key = c;
    p = p->next;
  }
  return head;
}
