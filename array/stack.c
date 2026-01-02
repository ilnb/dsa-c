#include <stdio.h>
#define MAX 20

typedef struct {
  int arr[MAX];
  int top;
} stack;

void menu();
void push(stack *, int);
int pop(stack *);
int peek(stack *);
void display(stack *);

int main(void) {
  stack s;
  s.top = -1;
  while (1) {
    menu();
    int opt = 0;
    printf("What do you want to do? ");
    scanf("%d", &opt);
    switch (opt) {
    case 1: {
      int val;
      printf("\nEnter the value to be pushed: ");
      scanf("%d", &val);
      push(&s, val);
      printf("\nThe stack is:\n");
      display(&s);
      break;
    }
    case 2: {
      int i = pop(&s);
      printf("\nThe number popped: %d\n", i);
      if (i != -273) {
        printf("The updated stack:\n");
        display(&s);
      }
      break;
    }
    case 3: {
      int i = peek(&s);
      printf("The value at the top is %d.\n", i);
      break;
    }
    case 4:
      display(&s);
    case 5:
      break;
    default:
      printf("\nInvalid option\n");
      break;
    }
    if (opt == 5)
      break;
  }
  return 0;
}

void menu() {
  printf("1. Push\n");
  printf("2. Pop\n");
  printf("3. Peek\n");
  printf("4. Display\n");
  printf("5. Exit\n");
}

void push(stack *s, int val) {
  if (s->top == MAX - 1) {
    printf("\nStack is full\n.");
    return;
  }
  s->arr[++s->top] = val;
}

int pop(stack *s) {
  if (s->top == -1) {
    printf("\nStack is empty.\n");
    return -273;
  } else
    return s->arr[s->top--];
}

int peek(stack *s) {
  if (s->top == -1) {
    printf("The stack is empty\n");
    return -273;
  }
  return s->arr[s->top];
}

void display(stack *s) {
  if (s->top == -1) {
    printf("The stack is empty\n");
    return;
  }
  for (int i = s->top; i > -1; i--)
    printf("%d\n", s->arr[i]);
  printf("\n");
}
