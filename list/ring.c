#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  struct node *next;
  int val;
} node;

void menu();
node *push_sorted(node *, int);
node *pop_sorted(node *, int);
void print_ring(node *);
void free_ring(node **);

int main()
{
  [[gnu::cleanup(free_ring)]] node *ring = 0;
  int opt;
  do {
    menu();
    printf("What's on your mind? ");
    scanf("%d", &opt);
    switch (opt) {
    case 1: {
      printf("Enter the value you want to insert: ");
      int val;
      scanf("%d", &val);
      ring = push_sorted(ring, val);
      break;
    }
    case 2: {
      printf("Enter the value you want to delete: ");
      int val;
      scanf("%d", &val);
      ring = pop_sorted(ring, val);
      break;
    }
    case 3: {
      print_ring(ring);
      break;
    }
    case 4:
      free_ring(&ring);
    case 5:
      break;
    default:
      printf("Invalid opt\n");
    }
  } while (opt != 5);
  return 0;
}

void menu()
{
  printf("1. Insert a node\n");
  printf("2. Delete a node\n");
  printf("3. Print ring\n");
  printf("4. Free ring\n");
  printf("5. Exit\n");
}

void print_ring(node *ring)
{
  if (!ring) {
    printf("Empty.\n");
    return;
  }
  printf("HEAD->");
  node *t = ring;
  do {
    printf("%d->", t->val);
    t = t->next;
  } while (t != ring);
  printf("HEAD\n");
}

node *push_sorted(node *ring, int val)
{
  node *q = malloc(sizeof(node));
  if (!q)
    return ring;
  q->val = val;
  if (!ring) {
    q->next = q;
    return q;
  }
  node *curr = ring;
  while (curr->next != ring && !(curr->val <= val && val < curr->next->val))
    curr = curr->next;
  q->next = curr->next;
  curr->next = q;
  return (val < ring->val) ? q : ring;
}

node *pop_sorted(node *ring, int val)
{
  if (!ring)
    return ring;
  if (val == ring->val) {
    node *t = ring;
    if (ring->next == ring) {
      free(t);
      return NULL;
    } else {
      node *end = ring;
      while (end->next != ring)
        end = end->next;
      ring = t->next;
      end->next = ring;
      free(t);
      return ring;
    }
  }
  node *p = ring;
  while (p->next != ring) {
    if (val == p->next->val) {
      node *t = p->next;
      p->next = t->next;
      free(t);
    } else if (val > p->next->val)
      p = p->next;
    else
      break;
  }
  return ring;
}

void free_ring(node **ring)
{
  node *first = *ring;
  node *p = first;
  if (!first)
    return;
  do {
    node *t = p;
    p = p->next;
    free(t);
  } while (p != first);
}
