#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node {
  int key;
  node *next;
};

typedef struct {
  node *start, *end;
  int count;
} hnode;

void menu();
void initialize(hnode *);
void insertAtStart(hnode *, int);
void insertAtEnd(hnode *, int);
void deleteNode(hnode *, int);
void display(hnode);
void displayCount(hnode);

int main(void) {
  hnode h;
  initialize(&h);
  int option;
  do {
    menu();
    printf("What's on your mind? ");
    scanf("%d", &option);
    switch (option) {
    case 1: {
      printf("Enter what to insert: ");
      int val;
      scanf("%d", &val);
      insertAtStart(&h, val);
      break;
    }
    case 2: {
      printf("Enter what to insert: ");
      int val;
      scanf("%d", &val);
      insertAtEnd(&h, val);
      break;
    }
    case 3: {
      printf("Enter what to delete: ");
      int val;
      scanf("%d", &val);
      deleteNode(&h, val);
      break;
    }
    case 4: {
      display(h);
      break;
    }
    case 5: {
      displayCount(h);
      break;
    }
    case 6: {
      break;
    }
    default: {
      printf("Invalid option.\n");
    }
    }
  } while (option != 6);
  return 0;
}

void menu() {
  printf("1. Insert at the start\n");
  printf("2. Insert at the end\n");
  printf("3. Delete node\n");
  printf("4. Display list\n");
  printf("5. Display number of keys\n");
  printf("6. Exit\n");
}

void initialize(hnode *h) {
  h->start = NULL;
  h->end = NULL;
  h->count = 0;
}

void insertAtStart(hnode *h_ptr, int val) {
  node *q = malloc(sizeof(node));
  q->key = val;
  q->next = h_ptr->start;
  if (!h_ptr->start) {
    h_ptr->end = q;
  }
  h_ptr->start = q;
  h_ptr->count++;
}

void insertAtEnd(hnode *h_ptr, int val) {
  node *q = malloc(sizeof(node));
  q->key = val;
  q->next = NULL;
  if (!h_ptr->end) {
    h_ptr->start = q;
  }
  h_ptr->end->next = q;
  h_ptr->end = q;
  h_ptr->count++;
}

void deleteNode(hnode *h_ptr, int val) {
  if (!h_ptr->start) {
    printf("Empty list.\n");
    return;
  }
  if (val == h_ptr->start->key) {
    node *t = h_ptr->start;
    h_ptr->start = h_ptr->start->next;
    free(t);
    h_ptr->count--;
    return;
  }
  node *q = h_ptr->start;
  while (q->next) {
    if (q->next->key == val) {
      node *t = q->next;
      q->next = t->next;
      free(t);
      h_ptr->count--;
      return;
    }
    q = q->next;
  }
  printf("Node not found.\n");
}

void display(hnode h) {
  while (h.start) {
    printf("%d->", h.start->key);
    h.start = h.start->next;
  }
  printf("NULL\n");
}

void displayCount(hnode h) {
  printf("The length is %d.\n", h.count);
  return;
}
