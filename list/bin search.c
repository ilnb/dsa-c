#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int key;
  struct node *next;
} node;

node *binSearch(node *, node *, int);
node *sortedInsert(node *, int);

int main() {
  node *head = NULL;
  for (int i = 0; i < 9; i++)
    head = sortedInsert(head, i);
  printf("What do you wanna search for? ");
  int n;
  scanf("%d", &n);
  node *f = binSearch(head, NULL, n);
  f ? printf("Node found.\n") : printf("Node not found.\n");
  return 0;
}

node *sortedInsert(node *head, int val) {
  node *p = (node *)malloc(sizeof(node));
  if (!p) {
    printf("Out of memory.\n");
    return head;
  }
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

node *binSearch(node *head, node *end, int val) {
  if (!head)
    return NULL;
  else if (head->key == val)
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
    if (slow->key == val)
      return slow;
    else if (slow->key < val)
      return binSearch(slow->next, fast, val);
    else
      return binSearch(head, slow, val);
  }
  return NULL;
}
