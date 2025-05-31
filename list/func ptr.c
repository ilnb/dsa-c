#include "node.h"

typedef node *(*FUNC)(node *, int);

// returns insert (ins) / delete (del) function
FUNC choice(char *choice);
// node *(*choice(char *choice))(node *, int);

int main() {
  node *head = NULL;
  for (int i = 0; i < 11; i++)
    head = (*choice("ins"))(head, i);
  displayList(head);
  for (int i = 0; i < 11; i += 2)
    head = (*choice("del"))(head, i);
  displayList(head);
  head = freeList(head);
  return 0;
}

FUNC choice(char *str) {
  if (!strcmp(str, "ins"))
    return sortedInsert;
  else if (!strcmp(str, "del"))
    return sortedDelete;
  return NULL;
}
