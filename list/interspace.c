#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;

struct node {
  int key;
  node *next;
};

node *insert(node *, int);
node *delete(node *, int);
node *freeList(node *);
void display(node *);
node *interspace(node *, node *);

int main(void) {
  node *head1 = NULL, *head2 = NULL;
  for (int i = 1; i <= 10; i += 2) {
    head1 = insert(head1, i);
    head2 = insert(head2, i - 1);
  }
  head1 = delete (head1, 3);
  head1 = delete (head1, 7);
  head2 = delete (head2, 4);
  head2 = delete (head2, 6);
  printf("The first linked list: ");
  display(head1);
  printf("The second linked list: ");
  display(head2);
  node *merged = interspace(head1, head2);
  printf("Interspace merged list: ");
  display(merged);
  freeList(head1), freeList(head2), freeList(merged);
  return 0;
}

node *insert(node *head, int val) {
  node *p = malloc(sizeof(node));
  p->key = val;
  if (!head || val < head->key) {
    p->next = head;
    head = p;
    return head;
  }
  node *q = head;
  while (q->next && val >= q->next->key) {
    q = q->next;
  }
  p->next = q->next;
  q->next = p;
  return head;
}

node *delete(node *head, int val) {
  if (!head) {
    printf("Empty list.\n");
    return head;
  }
  if (val == head->key) {
    node *t = head;
    head = head->next;
    free(t);
    return head;
  }
  node *p = head;
  while (p->next) {
    if (val == p->next->key) {
      node *t = p->next;
      p->next = t->next;
      free(t);
      break;
    } else if (val > p->next->key) {
      p = p->next;
    } else {
      break;
    }
  }
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

node *interspace(node *head1, node *head2) {
  if (!head1 && !head2) {
    return NULL;
  } else if (head1 && !head2) {
    return head1;
  } else if (!head1 && head2) {
    return head2;
  }
  node *merged = NULL;
  node *end;
  if (!merged) {
    node *p = malloc(sizeof(node));
    p->key = head1->key;
    p->next = NULL;
    merged = p;
    head1 = head1->next;
    node *q = malloc(sizeof(node));
    q->key = head2->key;
    q->next = NULL;
    merged->next = q;
    end = q;
    head2 = head2->next;
  }
  while (head1 && head2) {
    node *p = malloc(sizeof(node));
    p->key = head1->key;
    p->next = NULL;
    end->next = p;
    end = p;
    head1 = head1->next;
    node *q = malloc(sizeof(node));
    q->key = head2->key;
    q->next = NULL;
    end->next = q;
    end = q;
    head2 = head2->next;
  }
  while (head1) {
    node *p = malloc(sizeof(node));
    p->key = head1->key;
    p->next = NULL;
    end->next = p;
    end = p;
    head1 = head1->next;
  }
  while (head2) {
    node *q = malloc(sizeof(node));
    q->key = head2->key;
    q->next = NULL;
    end->next = q;
    end = q;
    head2 = head2->next;
  }
  return merged;
}
