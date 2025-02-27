#include "node.h"

node *interspace(node *, node *);

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

node *interspace(node *head1, node *head2) {
  if (!head1 && !head2) {
    return NULL;
  } else if (head1 && !head2) {
    return head1;
  } else if (!head1 && head2) {
    return head2;
  }
  node *merged = NULL;
  node *end, *p;
  if (!merged) {
    p = malloc(sizeof(node));
    p->key = head1->key;
    p->next = NULL;
    merged = p;
    head1 = head1->next;
    p = malloc(sizeof(node));
    p->key = head2->key;
    p->next = NULL;
    merged->next = p;
    end = p;
    head2 = head2->next;
  }
  while (head1 && head2) {
    node *p = malloc(sizeof(node));
    p->key = head1->key;
    p->next = NULL;
    end->next = p;
    end = p;
    head1 = head1->next;
    p = malloc(sizeof(node));
    p->key = head2->key;
    p->next = NULL;
    end->next = p;
    end = p;
    head2 = head2->next;
  }
  while (head1) {
    p = malloc(sizeof(node));
    p->key = head1->key;
    p->next = NULL;
    end->next = p;
    end = p;
    head1 = head1->next;
  }
  while (head2) {
    p = malloc(sizeof(node));
    p->key = head2->key;
    p->next = NULL;
    end->next = p;
    end = p;
    head2 = head2->next;
  }
  return merged;
}
