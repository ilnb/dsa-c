#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node {
  int key;
  node *next;
};

typedef struct {
  node *start, *end;
} hnode;

node *insert(node *, int);
node *delete(node *, int);
void insertHnode(hnode *, int);
void merge(node *, node *, hnode *);
node *freeList(node *);
void freeHnode(hnode *);
void display(node *);
void init(hnode *);

int main(void) {
  node *head1, *head2;
  for (int i = 1; i < 10; i += 2) {
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
  hnode h;
  init(&h);
  printf("Merged list: ");
  merge(head1, head2, &h);
  display(h.start);
  freeList(head1), freeList(head2), freeHnode(&h);
  return 0;
}

void init(hnode *h_ptr) {
  h_ptr->start = NULL;
  h_ptr->end = NULL;
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

void insertHnode(hnode *h_ptr, int val) {
  node *q = malloc(sizeof(node));
  q->key = val;
  q->next = NULL;
  if (!h_ptr->end) {
    h_ptr->start = q;
  } else {
    h_ptr->end->next = q;
  }
  h_ptr->end = q;
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

void freeHnode(hnode *h_ptr) {
  if (!h_ptr) {
    printf("Empty list.\n");
    return;
  }
  while (h_ptr->start) {
    node *q = h_ptr->start;
    h_ptr->start = h_ptr->start->next;
    free(q);
  }
  h_ptr->end = NULL;
}

void merge(node *head1, node *head2, hnode *merged) {
  while (head1 && head2) {
    if (head1->key < head2->key) {
      insertHnode(merged, head1->key);
      head1 = head1->next;
    } else {
      insertHnode(merged, head2->key);
      head2 = head2->next;
    }
  }
  while (head1) {
    insertHnode(merged, head1->key);
    head1 = head1->next;
  }
  while (head2) {
    insertHnode(merged, head2->key);
    head2 = head2->next;
  }
}
