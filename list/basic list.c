#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node {
  int key;
  node *next;
};

void printList(node *);
int lengthList(node *);
node *getNode(int);
node *insertAtHead(node *, int);
node *insertAtTail(node *, int);
node *insertAtPos(node *, int, int);
node *removeAtHead(node *);
node *removeAtTail(node *);
node *removeAtPos(node *, int, int);
node *freeList(node *);
node *split(node **);
int findInList(node *, int);

int main(void) {
  node *head = NULL;
  printf("How many nodes?: ");
  int n, data;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    printf("Enter element %d: ", i);
    scanf("%d", &data);
    head = insertAtHead(head, data);
  }
  printf("%d\n", lengthList(head));
  free(head);
  head = NULL;
  return 0;
}

void printList(node *head) {
  if (!head) {
    printf("The list is empty!\n");
    return;
  }
  printf("List printed:\n");
  node *current = head;
  while (current) {
    printf("%d->", current->key);
    current = current->next;
  }
  printf("\n");
}

int lengthList(node *head) {
  int l = 0;
  node *current = head;
  while (current) {
    // increment at each node
    l++;
    // move forward
    current = current->next;
  }
  // free
  free(current);
  return l;
}

int findInList(node *head, int data) {
  node *current = head;
  int index = 0;
  while (current) {
    index++;
    if (current->key == data)
      return index;
    current = current->next;
  }
  free(current);
  return 0;
}

// single node generator to get things started
node *getNode(int data) {
  node *temp = malloc(sizeof(node));
  temp->key = data;
  return temp;
}

// which can then be used for insertions
node *insertAtHead(node *head, int data) {
  // get the data
  node *new = getNode(data);
  // juggle the arrows
  new->next = head;
  head = new;
  return head;
}

node *insertAtTail(node *head, int data) {
  node *new = getNode(data);
  // we have nothing to begin with
  if (!head)
    return new;
  node *current = head;
  // reach the last node
  while (current->next)
    current = current->next;
  // new node is the new last
  current->next = new;
  return head;
}

node *insertAtPos(node *head, int data, int position) {
  if (position < 1) {
    printf("Invalid position\n");
    return head;
  }
  // inserting at head
  else if (position == 1) {
    node *temp = getNode(data);
    temp->next = head;
    head = temp;
    return head;
  } else {
    node *prev = head;
    // numbering starts with head=1
    // and so on. inserting at n
    // shifts the nodes from n and
    // further to right.
    //
    // getting to position just
    // before insertion point
    for (int i = 1; i < position - 1 && prev; i++)
      prev = prev->next;
    if (!prev) {
      // position out of the list
      printf("Invalid position\n");
      return head;
    }
    // insertion
    node *new = getNode(data);
    new->next = prev->next;
    prev->next = new;
    return head;
  }
}

node *removeAtHead(node *head) {
  if (!head) {
    printf("The list is empty!\n");
    return head;
  }
  node *current = head;
  // head moves forward
  head = head->next;
  // the now unnecessary node gets deleted
  free(current);
  return head;
}

node *removeAtTail(node *head) {
  if (!head) {
    printf("The list is empty!\n");
    return head;
  }
  node *current = head;
  // reaching the 2nd last node
  while (current->next->next)
    current = current->next;
  // last node deleted
  free(current->next);
  // tail is set
  current->next = NULL;
  return head;
}

node *removeAtPos(node *head, int data, int position) {
  if (!head) {
    printf("The list is empty!\n");
    return head;
  }
  if (position < 1) {
    printf("Invalid position");
    return head;
  } else if (position == 1) {
    // at head case
    node *current = head;
    head = head->next;
    free(current);
    return head;
  } else {
    node *current = head;
    // reaching node just before removal point
    for (int i = 1; i < position - 1 && current; i++)
      current = current->next;
    // out of range
    if (!current || !current->next)
      return head;
    // save the to be deleted in temp
    node *temp = current->next;
    // shift to the next node
    current->next = current->next->next;
    // delete the saved node
    free(temp);
    return head;
  }
}

node *freeList(node *head) {
  while (head) {
    node *temp = head;
    head = head->next;
    free(temp);
  }
  return head;
}

node *split(node **head) {
  int len = lengthList(*head);
  node *temp = *head;
  for (int i = 0; i < len / 2 - 1; i++) {
    temp = temp->next;
    *head = (*head)->next;
  }
  return temp;
}
