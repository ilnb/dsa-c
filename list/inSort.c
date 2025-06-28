#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int key;
  struct node *next;
} node;

node *inSort(node *);
node *sortedInsert(node *, int);
void printList(node *);

int main() {
  node *head = sortedInsert(0, 0);
  for (int i = 1; i < 11; i++)
    sortedInsert(head, i);
  printList(head);
  head = inSort(head);
  printList(head);
  return 0;
}

node *inSort(node *head) {
  if (!head)
    return head;
  node *sorted = NULL;
  node *curr = head;
  while (curr) {
    node *next = curr->next;
    if (!sorted || curr->key < sorted->key) {
      curr->next = sorted;
      sorted = curr;
    } else {
      node *t = sorted;
      while (t->next && t->next->key < curr->key)
        t = t->next;
      curr->next = t->next;
      t->next = curr;
    }
    curr = next;
  }
  return sorted;
}

node *sortedInsert(node *head, int val) {
  node *p = (node *)malloc(sizeof(node));
  if (!p)
    return head;
  p->key = val;
  if (!head || val < head->key) {
    p->next = head;
    return p;
  }
  node *q = head;
  while (q->next && val >= q->next->key)
    q = q->next;
  p->next = q->next;
  q->next = p;
  return head;
}

void printList(node *head) {
  while (head) {
    printf("%d->", head->key);
    head = head->next;
  }
  printf("NULL\n");
}
