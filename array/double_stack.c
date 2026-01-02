#include <stdio.h>
#define MAX 30

typedef struct {
  int arr[MAX], top1, top2;
} db_stack;

void menu();
void init(db_stack *);
void push1(db_stack *, int);
void push2(db_stack *, int);
int pop1(db_stack *);
int pop2(db_stack *);
void display1(db_stack *);
void display2(db_stack *);

int main(void) {
  db_stack d;
  init(&d);
  int opt;
  do {
    menu();
    printf("What do you want to do? ");
    scanf("%d", &opt);
    switch (opt) {
    case 1: {
      printf("What do you want to push? ");
      int val;
      scanf("%d", &val);
      push1(&d, val);
      break;
    }
    case 2: {
      if (d.top1 + 1 == d.top2) {
        printf("Stack is full\n");
        break;
      }
      printf("What do you want to push? ");
      int val;
      scanf("%d", &val);
      push2(&d, val);
      break;
    }
    case 3: {
      int val = pop1(&d);
      if (val > -1) {
        printf("The popped value: %d\n", val);
        break;
      }
    }
    case 4: {
      int val = pop2(&d);
      if (val > -1) {
        printf("The popped value: %d\n", val);
        break;
      }
    }
    case 5: {
      display1(&d);
      break;
    }
    case 6: {
      display2(&d);
      break;
    }
    case 7:
      break;
    default: {
      printf("Invalid option");
      break;
    }
    }
  } while (opt != 7);
  return 0;
}

void menu() {
  printf("1. Push into first stack\n");
  printf("2. Push into second stack\n");
  printf("3. Pop from first stack\n");
  printf("4. Pop from second stack\n");
  printf("5. Display first stack\n");
  printf("6. Display second stack\n");
  printf("7. Exit\n");
}

void init(db_stack *d) {
  d->top1 = -1;
  d->top2 = MAX;
}

void push1(db_stack *d, int val) {
  d->arr[++d->top1] = val;
  return;
}

void push2(db_stack *d, int val) {
  d->arr[--d->top2] = val;
  return;
}

int pop1(db_stack *d) {
  if (d->top1 == -1) {
    printf("Empty stack\n");
    return -1;
  }
  return d->arr[d->top1--];
}

int pop2(db_stack *d) {
  if (d->top2 == MAX) {
    printf("Empty stack\n");
    return -1;
  }
  return d->arr[d->top2++];
}

void display1(db_stack *d) {
  if (d->top1 == -1) {
    printf("Empty stack\n");
    return;
  }
  for (int i = d->top1; i > -1; i--)
    printf("%d\n", d->arr[i]);
}

void display2(db_stack *d) {
  if (d->top2 == MAX) {
    printf("Empty stack\n");
    return;
  }
  for (int i = d->top2; i < MAX; i++)
    printf("%d\n", d->arr[i]);
}
