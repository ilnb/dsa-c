#include "node.h"

node *bubSort(node *);

int main(void) {
  node *head = insertStart(0, 2);
  head = insertStart(head, 1);
  head = insertStart(head, 5);
  head = insertStart(head, 3);
  head = insertStart(head, 4);
  printf("List right now: ");
  printList(head);
  head = bubSort(head);
  printf("Sorted list: ");
  printList(head);
  head = freeList(head);
  return 0;
}

node *bubSort(node *head) {
  if (!head)
    return head;
  node *p = head;
  while (p->next) {
    node *q = p->next;
    while (q) {
      if (p->key > q->key) {
        int t = p->key;
        p->key = q->key;
        q->key = t;
      }
      q = q->next;
    }
    p = p->next;
  }
  return head;
}

/* for (int i = 0; i < n - 1; i++)
 *   for (int j = i + 1; j < n; j++)
 *     if (arr[i] > arr[j])
 *       swap(arr + i, arr + j);
 */
