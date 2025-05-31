#include "node.h"

typedef node *(*FUNC)(node *, int);

FUNC choice(char *);

int main() {
  node *head = NULL;
  for (int i = 0; i < 11; i++)
    head = (*choice("insert"))(head, i);
  displayList(head);
  for (int i = 0; i < 11; i += 2)
    head = (*choice("delete"))(head, i);
  displayList(head);
  return 0;
}

FUNC choice(char *str) {
  if (!strcmp(str, "insert"))
    return sortedInsert;
  else if (!strcmp(str, "delete"))
    return sortedDelete;
  return NULL;
}
