#include <stdio.h>
#include <stdlib.h>

typedef struct stack stack;

struct stack {
  int key;
  stack *next;
};

void menu();
void push(stack **, int);
int pop(stack **);
int peek(stack *);
void display(stack *t);
stack *freeStack(stack *);

int main(void) {
  stack *top = NULL;
  int option;
  do {
    menu();
    printf("What's on your mind? ");
    scanf("%d", &option);
    switch (option) {
    case 1: {
      printf("Enter the value to push: ");
      int val;
      scanf("%d", &val);
      push(&top, val);
      break;
    }
    case 2: {
      int n = pop(&top);
      if (n != -1) {
        printf("Value popped is %d.\n", n);
      }
      break;
    }
    case 3: {
      int n = peek(top);
      if (n != -1) {
        printf("Value at the top is %d.\n", n);
      }
      break;
    }
    case 4: {
      display(top);
      break;
    }
    case 5: {
      top = freeStack(top);
      break;
    }
    case 6: {
      break;
    }
    default: {
      printf("Invalid option.\n");
    }
    }
  } while (option != 5);
  top = freeStack(top);
  return 0;
}

void menu() {
  printf("1. Push\n");
  printf("2. Pop\n");
  printf("3. Peek\n");
  printf("4. Display\n");
  printf("5. Free stack\n");
  printf("6. Exit\n");
}

void push(stack **t, int val) {
  stack *q = malloc(sizeof(stack));
  if (!q) {
    printf("Stack overflow.\n");
    return;
  }
  q->key = val;
  q->next = *t;
  *t = q;
  return;
}

int pop(stack **t) {
  if (!*t) {
    printf("Stack is empty.\n");
    return -1;
  }
  stack *q = *t;
  int n = q->key;
  *t = (*t)->next;
  free(q);
  return n;
}

int peek(stack *t) {
  if (!t) {
    printf("Stack is empty.\n");
    return -1;
  }
  return t->key;
}

void display(stack *t) {
  while (t) {
    printf("%d\n", t->key);
    printf("↓\n");
    t = t->next;
  }
  printf("NULL\n");
}

stack *freeStack(stack *top) {
  if (!top) {
    printf("Empty list.\n");
    return top;
  }
  while (top) {
    stack *t = top;
    top = top->next;
    free(t);
  }
  return top;
}
