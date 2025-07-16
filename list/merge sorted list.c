#include "node.h"

void merge(node *, node *, hnode *);

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
  hnode h = {0};
  printf("Merged list: ");
  merge(head1, head2, &h);
  printList(h.start);
  varFreeList(2, &head1, &head2), freeHnode(&h);
  return 0;
}

void merge(node *head1, node *head2, hnode *merged) {
  while (head1 && head2) {
    if (head1->key < head2->key) {
      insertHEnd(merged, head1->key);
      head1 = head1->next;
    } else {
      insertHEnd(merged, head2->key);
      head2 = head2->next;
    }
  }
  for (; head1; head1 = head1->next)
    insertHEnd(merged, head1->key);
  for (; head2; head2 = head2->next)
    insertHEnd(merged, head2->key);
}
