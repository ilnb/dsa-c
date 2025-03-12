#include <stdio.h>
#include <stdlib.h>

typedef struct pnode {
  int key;
  int rank; // less is high
  struct pnode *next;
} pnode;

void menu();
void pEnqueue(pnode **, int, int);
pnode pDequeue(pnode **);
void displayPlist(pnode *);
pnode *freePlist(pnode *);

int main() {
  pnode *head = NULL;
  int option;
  while (1) {
    menu();
    printf("What do you want to do? ");
    scanf("%d", &option);
    switch (option) {
      case 1: {
        int val, priority;
        printf("Enter the value to be insert: ");
        scanf("%d", &val);
        printf("Enter the priority: ");
        scanf("%d", &priority);
        pEnqueue(&head, val, priority);
        break;
      }
      case 2: {
        pnode n = pDequeue(&head);
        if (!n.next) {
          printf("The value dequeued : %d\n", n.key);
          printf("Its priority: %d\n", n.rank);
        } else
          printf("Empty list\n");
        break;
      }
      case 3: {
        displayPlist(head);
        break;
      }
      case 4: {
        goto quit;
      }
      case 5:
        break;
      default:
        printf("Invalid option\n");
    }
  }
quit:
  head = freePlist(head);
  return 0;
}

void menu() {
  printf("1. Insert a node\n");
  printf("2. Delete a node\n");
  printf("3. Display priority list\n");
  printf("4. Free list\n");
  printf("5. Exit\n");
}

void pEnqueue(pnode **hptr, int val, int pri) {
  pnode *q = malloc(sizeof(*q));
  if (!q)
    return;
  *q = (pnode){val, pri};
  if (!*hptr || (*hptr)->rank > pri) {
    q->next = *hptr;
    *hptr = q;
    return;
  }
  pnode *p = *hptr;
  while (p->next && pri >= p->next->rank)
    p = p->next;
  q->next = p->next;
  p->next = q;
}

pnode pDequeue(pnode **hptr) {
  if (!*hptr)
    return (pnode){0, 0, 0};
  pnode *t = *hptr;
  *hptr = (*hptr)->next;
  return *t;
}

void displayPlist(pnode *head) {
  if (!head) {
    printf("Empty list\n");
    return;
  }
  printf("\n(key, rank) pairs:\n");
  while (head) {
    printf("(%d, %d)->", head->key, head->rank);
    head = head->next;
  }
  printf("NULL\n");
}

pnode *freePlist(pnode *head) {
  while (head) {
    pnode *t = head;
    head = head->next;
    free(t);
  }
  return NULL;
}
