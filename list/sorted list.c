#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node {
  int key;
  node *next;
};

void menu();
node *insert(node *, int);
node *delete(node *, int);
void display(node *);

int main(void) {
  node *head = NULL;
  int option;
  do {
    menu();
    printf("What's on your mind? ");
    scanf("%d", &option);
    switch (option) {
    case 1: {
      int val;
      printf("Enter the value you want to insert: ");
      scanf("%d", &val);
      head = insert(head, val);
      break;
    }
    case 2: {
      int val;
      printf("Enter the value you want to delete: ");
      scanf("%d", &val);
      head = delete (head, val);
      break;
    }
    case 3: {
      display(head);
      break;
    }
    case 4: {
      break;
    }
    default: {
      printf("Invalid option.\n");
    }
    }
  } while (option != 4);
}

void menu() {
  printf("1. Insert\n2. Delete\n3. Display\n4. Exit\n");
  return;
}

node *insert(node *head, int val) {
  node *p = malloc(sizeof(node));
  p->key = val;
  // new head
  if (!head || val < head->key) {
    p->next = head;
    head = p;
    return head;
  }
  // general
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
  // deleting head
  if (val == head->key) {
    node *t = head;
    head = head->next;
    free(t);
    return head;
  }
  // general
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
    printf("Empty list\n");
    return;
  }
  node *t = head;
  while (t) {
    printf("%d->", t->key);
    t = t->next;
  }
  printf("\n");
}
