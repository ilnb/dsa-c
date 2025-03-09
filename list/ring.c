#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int key;
  struct node *next;
} node;

void menu();
node *insertNode(node *, int);
node *deleteNode(node *, int);
void printRing(node *);
node *freeRing(node *);

int main() {
  node *ring = 0;
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
      case 4: {
        ring = freeRing(ring);
        break;
      }
      case 5: {
        break;
      }
      default: {
        printf("Invalid option\n");
      }
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

void printRing(node *ring) {
  if (!ring) {
    printf("Empty.\n");
    return;
  }
  printf("HEAD->");
  node *t = ring;
  do {
    printf("%d->", t->key);
    t = t->next;
  } while (t != ring);
  printf("HEAD\n");
}

node *insertNode(node *ring, int val) {
  node *q = malloc(sizeof(node));
  if (!q) {
    printf("Out of memory\n");
    return ring;
  }
  q->key = val;
  if (!ring) {
    q->next = q;
    return q;
  }
  node *curr = ring;
  while (curr->next != ring && !(curr->key <= val && val < curr->next->key))
    curr = curr->next;
  q->next = curr->next;
  curr->next = q;
  return (val < ring->key) ? q : ring;
}

node *deleteNode(node *ring, int val) {
  if (!ring)
    return ring;
  if (val == ring->key) {
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
    if (val == p->next->key) {
      node *t = p->next;
      p->next = t->next;
      free(t);
    } else if (val > p->next->key)
      p = p->next;
    else
      break;
  }
  return ring;
}

node *freeRing(node *ring) {
  if (!ring)
    return ring;
  node *p = ring;
  do {
    node *t = p;
    p = p->next;
    free(t);
  } while (p != ring);
  return NULL;
}
