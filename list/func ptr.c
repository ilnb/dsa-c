#include "node.h"

typedef node *(*FUNC)(node *, int);

// returns insert (ins) / delete (del) function
FUNC choice(char *choice);
// node *(*choice(char *choice))(node *, int);

int main() {
  node *head = NULL;
  for (int i = 0; i < 11; i++)
    head = (*choice("ins"))(head, i);
  printList(head);
  for (int i = 0; i < 11; i += 2)
    head = (*choice("del"))(head, i);
  printList(head);
  head = freeList(head);
  return 0;
}

FUNC choice(char *str) {
  if (!strncmp(str, "ins", strlen(str)))
    return sortedInsert;
  else if (!strncmp(str, "del", strlen(str)))
    return sortedDelete;
  return NULL;
}
