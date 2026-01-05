#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  struct node *next;
  int val;
} node;

void ins_sort(node **);
node *push_sorted(node *, int);
void print_list(node *);
void free_list(node **ptr);

int main()
{
  [[gnu::cleanup(free_list)]] node *head = push_sorted(0, 0);
  for (int i = 1; i < 11; i++)
    push_sorted(head, i);
  print_list(head);
  ins_sort(&head);
  print_list(head);
  return 0;
}

void ins_sort(node **ptr)
{
  node *head = *ptr;
  if (!head)
    return;
  node *sorted = NULL;
  node *curr = head;
  while (curr) {
    node *next = curr->next;
    if (!sorted || curr->val < sorted->val) {
      curr->next = sorted;
      sorted = curr;
    } else {
      node *t = sorted;
      while (t->next && t->next->val < curr->val)
        t = t->next;
      curr->next = t->next;
      t->next = curr;
    }
    curr = next;
  }
  return;
}

node *push_sorted(node *head, int val)
{
  node *p = malloc(sizeof *p);
  if (!p)
    return head;
  p->val = val;
  if (!head || val < head->val) {
    p->next = head;
    return p;
  }
  node *q = head;
  while (q->next && val >= q->next->val)
    q = q->next;
  p->next = q->next;
  q->next = p;
  return head;
}

void print_list(node *head)
{
  for (; head; head = head->next)
    printf("%d->", head->val);
  printf("NULL\n");
}

void free_list(node **ptr)
{
  node *first = *ptr;
  if (!first)
    return;
  while (first) {
    node *t = first;
    first = first->next;
  }
  *ptr = 0;
}
