#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int key;
  struct node *next;
} node;

node *insert(node *, int);
void display(node *);
node *inSort(node *);
node *freeList(node *);

int main(void) {
  node *head = NULL;
  head = insert(head, 2);
  head = insert(head, 1);
  head = insert(head, 5);
  head = insert(head, 3);
  head = insert(head, 4);
  printf("List right now: ");
  display(head);
  head = inSort(head);
  printf("Sorted list: ");
  display(head);
  head = freeList(head);
  return 0;
}

node *insert(node *head, int val) {
  node *t = malloc(sizeof(node));
  t->key = val;
  t->next = head;
  head = t;
  return head;
}

void display(node *head) {
  if (!head) {
    printf("Empty list.\n");
    return;
  }
  while (head) {
    printf("%d->", head->key);
    head = head->next;
  }
  printf("NULL\n");
}

node *freeList(node *head) {
  if (!head) {
    printf("Empty list.\n");
    return head;
  }
  while (head) {
    node *t = head;
    head = head->next;
    free(t);
  }
  return head;
}

node *inSort(node *head) {
  if (!head) {
    return head;
  }
  node *p;
  p = head;
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
