#include "node.h"

// #define newEnd(end, val) ((end)->next = newNode(val), (end) = (end)->next)

node *interspace(node *, node *);
node *newNode(int);
node *newEnd(node *, int);
node *copyList(node *);

int main(void) {
  node *head1 = NULL, *head2 = NULL;
  for (int i = 1; i <= 10; i += 2) {
    head1 = sortedInsert(head1, i);
    head2 = sortedInsert(head2, i - 1);
  }
  head1 = sortedDelete(head1, 3);
  head1 = sortedDelete(head1, 7);
  head2 = sortedDelete(head2, 4);
  head2 = sortedDelete(head2, 6);
  printf("The first linked list: ");
  displayList(head1);
  printf("The second linked list: ");
  displayList(head2);
  node *merged = interspace(head1, head2);
  printf("Interspace merged list: ");
  displayList(merged);
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
  node *p = malloc(sizeof(*p));
  if (!p)
    return end;
  p->key = val;
  end->next = p;
  return p;
}

node *copyList(node *head) {
  if (!head)
    return NULL;
  node *new = newNode(head->key);
  node *end = new;
  head = head->next;
  while (head) {
    end = newEnd(end, head->key);
    head = head->next;
  }
  return new;
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
