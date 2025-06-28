#include "node.h"

// #define newEnd(end, val) ((end)->next = newNode(val), (end) = (end)->next)

node *interspace(node *, node *);
node *newNode(int);
node *newEnd(node *, int);

int main(void) {
  node *head1 = sortedInsert(0, 1);
  node *head2 = sortedInsert(0, 0);
  for (int i = 3; i <= 10; i += 2) {
    sortedInsert(head1, i);
    sortedInsert(head2, i - 1);
  }
  sortedDelete(head1, 3);
  sortedDelete(head1, 7);
  sortedDelete(head2, 4);
  sortedDelete(head2, 6);
  printf("The first linked list: ");
  printList(head1);
  printf("The second linked list: ");
  printList(head2);
  node *merged = interspace(head1, head2);
  printf("Interspace merged list: ");
  printList(merged);
  varFreeList(3, &head1, &head2, &merged);
  return 0;
}

node *newNode(int val) {
  node *p = malloc(sizeof(*p));
  if (!p)
    return NULL;
  p->key = val;
  p->next = NULL;
  return p;
}

node *newEnd(node *end, int val) {
  node *p = newNode(val);
  if (!p)
    return end;
  end->next = p;
  return p;
}

node *interspace(node *head1, node *head2) {
  if (!head1 && !head2)
    return NULL;
  else if (!head1 || !head2)
    return copyList(head1 ? head1 : head2);
  node *merged = newNode(head1->key);
  head1 = head1->next;
  node *end = merged;
  end = newEnd(end, head2->key);
  head2 = head2->next;
  while (head1 || head2) {
    if (head1) {
      end = newEnd(end, head1->key);
      head1 = head1->next;
    }
    if (head2) {
      end = newEnd(end, head2->key);
      head2 = head2->next;
    }
  }
  return merged;
}
