#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  struct node *next;
  int val;
} node;

node *bin_search(node *, node *, int);
node *push_sorted(node *, int);
void free_list(node **);

int main() {
  [[gnu::cleanup(free_list)]] node *head = NULL;
  for (int i = 0; i < 9; i++)
    head = push_sorted(head, i);
  printf("What do you wanna search for? ");
  int n;
  scanf("%d", &n);
  node *f = bin_search(head, NULL, n);
  f ? printf("Node found.\n") : printf("Node not found.\n");
  return 0;
}

node *push_sorted(node *head, int val) {
  node *p = malloc(sizeof *p);
  if (!p) {
    printf("Out of memory.\n");
    return head;
  }
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

node *bin_search(node *head, node *end, int val) {
  if (!head)
    return NULL;
  else if (head->val == val)
    return head;
  else if (head != end) {
    node *fast = head->next, *slow = head;
    while (fast && fast != end) {
      fast = fast->next;
      if (fast && fast != end) {
        slow = slow->next;
        fast = fast->next;
      }
    }
    if (slow->val == val)
      return slow;
    else if (slow->val < val)
      return bin_search(slow->next, fast, val);
    else
      return bin_search(head, slow, val);
  }
  return NULL;
}

void free_list(node **ptr) {
  node *first = *ptr;
  if (!first)
    return;
  while (first) {
    node *t = first;
    first = first->next;
  }
  *ptr = 0;
}
