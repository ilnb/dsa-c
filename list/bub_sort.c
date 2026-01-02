#include "node.h"

node *bub_sort(node *);

int main(void) {
  [[gnu::cleanup(free_list)]] node *head = push_front(0, 2);
  head = push_front(head, 1);
  head = push_front(head, 5);
  head = push_front(head, 3);
  head = push_front(head, 4);
  printf("List right now: ");
  print_list(head);
  head = bub_sort(head);
  printf("Sorted list: ");
  print_list(head);
  return 0;
}

node *bub_sort(node *head) {
  if (!head)
    return head;
  node *p = head;
  while (p->next) {
    node *q = p->next;
    while (q) {
      if (p->val > q->val) {
        int t = p->val;
        p->val = q->val;
        q->val = t;
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
