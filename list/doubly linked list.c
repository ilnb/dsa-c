#include <stdio.h>
#include <stdlib.h>

typedef struct dbnode {
  struct dbnode *prev;
  int key;
  struct dbnode *next;
} dbnode;

void menu(void);
dbnode *sortedInsert(dbnode *, int);
dbnode *sortedDelete(dbnode *, int);
void printList(dbnode *);
int lengthList(dbnode *);
dbnode *freeList(dbnode *);

int main(void) {
  dbnode *head = 0;
  int option = 0;
  do {
    menu();
    printf("What's on your mind? ");
    scanf("%d", &option);
    switch (option) {
      case 1: {
        printf("Enter the value to insert: ");
        int val;
        scanf("%d", &val);
        head = sortedInsert(head, val);
        break;
      }
      case 2: {
        printf("Enter value to delete: ");
        int val;
        scanf("%d", &val);
        head = sortedDelete(head, val);
        break;
      }
      case 3: {
        printList(head);
        break;
      }
      case 4: {
        int n = lengthList(head);
        printf("The length of the list is: %d\n", n);
        break;
      }
      case 5:
        head = freeList(head);
      case 6:
        break;
      default:
        printf("Invalid option.\n");
    }
  } while (option != 6);
  head = freeList(head);
  return 0;
}

void menu(void) {
  printf("1. Insert a node\n");
  printf("2. Delete a node\n");
  printf("3. Display list.\n");
  printf("4. Length of list\n");
  printf("5. Free the list\n");
  printf("6. Exit\n");
}

dbnode *sortedInsert(dbnode *head, int val) {
  dbnode *q = malloc(sizeof(dbnode));
  if (!q)
    return head;
  q->key = val;
  if (!head || val < head->key) {
    q->next = head;
    q->prev = NULL;
    if (head)
      head->prev = q;
    return q;
  }
  dbnode *p = head;
  while (p->next && val >= p->next->key)
    p = p->next;
  q->next = p->next;
  q->prev = p;
  if (p->next)
    p->next->prev = q;
  p->next = q;
  return head;
}

// dbnode *sortedDelete(dbnode *head, int val) {
//   dbnode *t = head;
//   while (t && t->key != val)
//     t = t->next;
//   if (!t) return head;
//   if (t->prev)
//     t->prev->next = t->next;
//   else
//     head = t->next;
//   if (t->next)
//     t->next->prev = t->prev;
//   free(t);
//   return head;
// }

dbnode *sortedDelete(dbnode *head, int val) {
  if (!head)
    return head;
  dbnode **nptr = &head;
  while (*nptr && (*nptr)->key < val)
    nptr = &(*nptr)->next;
  if (*nptr && (*nptr)->key == val) {
    dbnode *t = *nptr;
    *nptr = t->next;
    if (t->next)
      t->next->prev = t->prev;
    free(t);
  }
  return head;
}

int lengthList(dbnode *head) {
  int n = 0;
  for (; head; head = head->next)
    n++;
  return n;
}

void printList(dbnode *head) {
  if (!head) {
    printf("Empty list.\n");
    return;
  }
  printf("NULL<-");
  for (; head->next; head = head->next)
    printf("%d  ", head->key);
  printf("%d->NULL\n", head->key);
}

dbnode *freeList(dbnode *head) {
  if (!head)
    return head;
  while (head) {
    dbnode *p = head;
    head = head->next;
    free(p);
  }
  return NULL;
}
