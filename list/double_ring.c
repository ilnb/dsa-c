#include <stdio.h>
#include <stdlib.h>

typedef struct dbnode {
  struct dbnode *prev;
  struct dbnode *next;
  int val;
} dbnode;

void menu();
dbnode *push_sorted(dbnode *, int);
dbnode *pop_sorted(dbnode *, int);
void print_ring(dbnode *);
void free_ring(dbnode **);

int main() {
  [[gnu::cleanup(free_ring)]] dbnode *ring = 0;
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

void menu() {
  printf("1. Insert a node\n");
  printf("2. Delete a node\n");
  printf("3. Print ring\n");
  printf("4. Free ring\n");
  printf("5. Exit\n");
}

void print_ring(dbnode *ring) {
  if (!ring) {
    printf("Empty.\n");
    return;
  }
  printf("HEAD  ");
  dbnode *t = ring;
  do {
    printf("%d  ", t->val);
    t = t->next;
  } while (t != ring);
  printf("HEAD\n");
}

dbnode *push_sorted(dbnode *ring, int val) {
  dbnode *q = malloc(sizeof *q);
  if (!q)
    return ring;
  q->val = val;
  if (!ring) {
    q->prev = q;
    q->next = q;
    return q;
  }
  dbnode *curr = ring;
  while (curr->next != ring && !(curr->val <= val && val < curr->next->val))
    curr = curr->next;
  q->next = curr->next;
  q->prev = curr;
  curr->next = curr->next->prev = q;
  return (val < ring->val) ? q : ring;
}

dbnode *pop_sorted(dbnode *ring, int val) {
  if (!ring)
    return ring;
  if (val == ring->val) {
    dbnode *t = ring;
    if (ring->next == ring) {
      free(t);
      return NULL;
    }
    dbnode *end = ring;
    while (end->next != ring)
      end = end->next;
    end->next = ring = t->next;
    t->next->prev = end;
    free(t);
    return ring;
  }
  dbnode *p = ring;
  while (p->next != ring) {
    if (p->next->val == val) {
      dbnode *t = p->next;
      p->next = t->next;
      t->next->prev = p;
      free(t);
      break;
    }
    p = p->next;
  }
  return ring;
}

void free_ring(dbnode **ptr) {
  dbnode *first = *ptr;
  dbnode *p = first;
  if (!p)
    return;
  do {
    dbnode *t = p;
    p = p->next;
    free(t);
  } while (p != first);
  *ptr = NULL;
}
