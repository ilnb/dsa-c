#include <stdio.h>
#include <stdlib.h>

typedef struct dbnode {
  struct dbnode *prev;
  int key;
  struct dbnode *next;
} dbnode;

void menu();
dbnode *insertNode(dbnode *, int);
dbnode *deleteNode(dbnode *, int);
void printRing(dbnode *);
dbnode *freeRing(dbnode *);

int main() {
  dbnode *ring = 0;
  int option;
  do {
    menu();
    printf("What's on your mind? ");
    scanf("%d", &option);
    switch (option) {
      case 1: {
        printf("Enter the value you want to insert: ");
        int val;
        scanf("%d", &val);
        ring = insertNode(ring, val);
        break;
      }
      case 2: {
        printf("Enter the value you want to delete: ");
        int val;
        scanf("%d", &val);
        ring = deleteNode(ring, val);
        break;
      }
      case 3: {
        printRing(ring);
        break;
      }
      case 4:
        ring = freeRing(ring);
      case 5:
        break;
      default:
        printf("Invalid option\n");
    }
  } while (option != 5);
  ring = freeRing(ring);
  return 0;
}

void menu() {
  printf("1. Insert a node\n");
  printf("2. Delete a node\n");
  printf("3. Print ring\n");
  printf("4. Free ring\n");
  printf("5. Exit\n");
}

void printRing(dbnode *ring) {
  if (!ring) {
    printf("Empty.\n");
    return;
  }
  printf("HEAD<->");
  dbnode *t = ring;
  do {
    printf("%d<->", t->key);
    t = t->next;
  } while (t != ring);
  printf("HEAD\n");
}

dbnode *insertNode(dbnode *ring, int val) {
  dbnode *q = malloc(sizeof(*q));
  if (!q)
    return ring;
  q->key = val;
  if (!ring) {
    q->prev = q;
    q->next = q;
    return q;
  }
  dbnode *curr = ring;
  while (curr->next != ring && !(curr->key <= val && val < curr->next->key))
    curr = curr->next;
  q->next = curr->next;
  q->prev = curr;
  curr->next->prev = q;
  curr->next = q;
  return (val < ring->key) ? q : ring;
}

dbnode *deleteNode(dbnode *ring, int val) {
  if (!ring)
    return ring;
  if (val == ring->key) {
    dbnode *t = ring;
    if (ring->next == ring) {
      free(t);
      return NULL;
    }
    dbnode *end = ring;
    while (end->next != ring)
      end = end->next;
    end->next = t->next;
    t->next->prev = end;
    ring = t->next;
    free(t);
    return ring;
  }
  dbnode *p = ring;
  while (p->next != ring) {
    if (p->next->key == val) {
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

dbnode *freeRing(dbnode *ring) {
  if (!ring)
    return ring;
  dbnode *p = ring;
  do {
    dbnode *t = p;
    p = p->next;
    free(t);
  } while (p != ring);
  return NULL;
}
