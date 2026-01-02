#include "node.h"

// #define newEnd(end, val) ((end)->next = newNode(val), (end) = (end)->next)

node *interspace(node *, node *);
node *new_node(int);
node *new_end(node *, int);

int main(void) {
  node *head1 = sorted_push(0, 1);
  node *head2 = sorted_push(0, 0);
  for (int i = 3; i <= 10; i += 2) {
    sorted_push(head1, i);
    sorted_push(head2, i - 1);
  }
  sorted_pop(head1, 3);
  sorted_pop(head1, 7);
  sorted_pop(head2, 4);
  sorted_pop(head2, 6);
  printf("The first linked list: ");
  print_list(head1);
  printf("The second linked list: ");
  print_list(head2);
  node *merged = interspace(head1, head2);
  printf("Interspace merged list: ");
  print_list(merged);
  var_free_list(&head1, &head2, &merged);
  return 0;
}

node *new_node(int val) {
  node *p = malloc(sizeof *p);
  if (!p)
    return NULL;
  *p = (node){.val = val};
  return p;
}

node *new_end(node *end, int val) {
  node *p = new_node(val);
  if (!p)
    return end;
  end->next = p;
  return p;
}

node *interspace(node *head1, node *head2) {
  if (!head1 && !head2)
    return NULL;
  else if (!head1 || !head2)
    return clone(head1 ? head1 : head2);
  node *merged = new_node(head1->val);
  head1 = head1->next;
  node *end = merged;
  end = new_end(end, head2->val);
  head2 = head2->next;
  while (head1 || head2) {
    if (head1) {
      end = new_end(end, head1->val);
      head1 = head1->next;
    }
    if (head2) {
      end = new_end(end, head2->val);
      head2 = head2->next;
    }
  }
  return merged;
}
