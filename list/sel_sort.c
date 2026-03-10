#include "node.h"

node *sel_sort(node *);

int main() {
  [[gnu::cleanup(free_list)]] node *head = push_front(0, 2);
  head = push_front(head, 1);
  head = push_front(head, 5);
  head = push_front(head, 3);
  head = push_front(head, 4);
  printf("List right now: ");
  print_list(head);
  head = sel_sort(head);
  printf("Sorted list: ");
  print_list(head);
  return 0;
}

node *sel_sort(node *head) {
  if (!head)
    return head;
  node *p = head;
  while (p) {
    node *q, *t;
    q = p->next;
    t = p;
    while (q) {
      if (q->val < t->val)
        t = q;
      q = q->next;
    }
    int c = t->val;
    t->val = p->val;
    p->val = c;
    p = p->next;
  }
  return head;
}
