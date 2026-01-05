#include "node.h"

void merge(node *, node *, hnode *);

int main()
{
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
  [[gnu::cleanup(free_hlist)]] hnode h = {0};
  printf("Merged list: ");
  merge(head1, head2, &h);
  print_list(h.start);
  var_free_list(&head1, &head2);
  return 0;
}

void merge(node *head1, node *head2, hnode *merged)
{
  while (head1 && head2) {
    if (head1->val < head2->val) {
      h_push_back(merged, head1->val);
      head1 = head1->next;
    } else {
      h_push_back(merged, head2->val);
      head2 = head2->next;
    }
  }
  for (; head1; head1 = head1->next)
    h_push_back(merged, head1->val);
  for (; head2; head2 = head2->next)
    h_push_back(merged, head2->val);
}
