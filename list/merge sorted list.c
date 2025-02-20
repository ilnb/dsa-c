#include "node.h"

void merge(node *, node *, hnode *);

int main(void) {
  node *head1, *head2;
  for (int i = 1; i < 10; i += 2) {
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
  hnode h = {0};
  printf("Merged list: ");
  merge(head1, head2, &h);
  displayList(h.start);
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
  while (head1) {
    insertHEnd(merged, head1->key);
    head1 = head1->next;
  }
  while (head2) {
    insertHEnd(merged, head2->key);
    head2 = head2->next;
  }
}
