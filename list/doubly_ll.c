#include <stdio.h>
#include <stdlib.h>

typedef struct dbnode {
  struct dbnode *prev;
  struct dbnode *next;
  int val;
} dbnode;

void menu(void);
dbnode *push_sorted(dbnode *, int);
dbnode *pop_sorted(dbnode *, int);
void print_list(dbnode *);
int list_len(dbnode *);
void free_list(dbnode **);

int main(void) {
  [[gnu::cleanup(free_list)]] dbnode *head = 0;
  int opt = 0;
  do {
    menu();
    printf("What's on your mind? ");
    scanf("%d", &opt);
    switch (opt) {
    case 1: {
      printf("Enter the value to insert: ");
      int val;
      scanf("%d", &val);
      head = push_sorted(head, val);
      break;
    }
    case 2: {
      printf("Enter value to delete: ");
      int val;
      scanf("%d", &val);
      head = pop_sorted(head, val);
      break;
    }
    case 3: {
      print_list(head);
      break;
    }
    case 4: {
      int n = list_len(head);
      printf("The ngth of the list is: %d\n", n);
      break;
    }
    case 5:
      free_list(&head);
    case 6:
      break;
    default:
      printf("Invalid opt.\n");
    }
  } while (opt != 6);
  return 0;
}

void menu(void) {
  printf("1. Insert a node\n");
  printf("2. Delete a node\n");
  printf("3. Display list.\n");
  printf("4. ngth of list\n");
  printf("5. Free the list\n");
  printf("6. Exit\n");
}

dbnode *push_sorted(dbnode *head, int val) {
  dbnode *q = malloc(sizeof *q);
  if (!q)
    return head;
  q->val = val;
  if (!head || val < head->val) {
    q->next = head;
    q->prev = NULL;
    if (head)
      head->prev = q;
    return q;
  }
  dbnode *p = head;
  while (p->next && val >= p->next->val)
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
//   while (t && t->val != val)
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

dbnode *pop_sorted(dbnode *head, int val) {
  if (!head)
    return head;
  dbnode **nptr = &head;
  while (*nptr && (*nptr)->val < val)
    nptr = &(*nptr)->next;
  if (*nptr && (*nptr)->val == val) {
    dbnode *t = *nptr;
    *nptr = t->next;
    if (t->next)
      t->next->prev = t->prev;
    free(t);
  }
  return head;
}

int list_len(dbnode *head) {
  int n = 0;
  for (; head; head = head->next)
    n++;
  return n;
}

void print_list(dbnode *head) {
  if (!head) {
    printf("Empty list.\n");
    return;
  }
  printf("NULL<-");
  for (; head->next; head = head->next)
    printf("%d  ", head->val);
  printf("%d->NULL\n", head->val);
}

void free_list(dbnode **head) {
  dbnode *first = *head;
  if (!first)
    return;
  while (first) {
    dbnode *p = first;
    first = first->next;
    free(p);
  }
  *head = NULL;
}
