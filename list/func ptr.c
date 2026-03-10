#include "node.h"

typedef node *(*FUNC)(node *, int);

// returns insert (ins) / delete (del) function
FUNC choice(char *choice);
// node *(*choice(char *choice))(node *, int);

int main() {
  [[gnu::cleanup(free_list)]] node *head = NULL;
  for (int i = 0; i < 11; i++)
    head = (*choice("ins"))(head, i);
  print_list(head);
  for (int i = 0; i < 11; i += 2)
    head = (*choice("del"))(head, i);
  print_list(head);
  return 0;
}

FUNC choice(char *str) {
  if (!strncmp(str, "ins", strlen(str)))
    return sorted_push;
  else if (!strncmp(str, "del", strlen(str)))
    return sorted_pop;
  return NULL;
}
