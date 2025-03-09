#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack {
  char key;
  struct stack *next;
} stack;

int validcheck(char *);
void push(stack **, char);
char pop(stack **);
int matchBrac(char, char);

int main() {
  printf("Enter the expression: ");
  char str[50] = {0};
  scanf("%s", str);
  int valid = validcheck(str);
  if (valid)
    printf("Valid expression.\n");
  else
    printf("Invalid expression.\n");
  return 0;
}

void push(stack **s_ptr, char c) {
  stack *q = malloc(sizeof(*q));
  q->key = c;
  q->next = *s_ptr;
  *s_ptr = q;
}

char pop(stack **s_ptr) {
  if (!*s_ptr)
    return 0;
  stack *s = *s_ptr;
  char c = s->key;
  *s_ptr = (*s_ptr)->next;
  free(s);
  return c;
}

int validcheck(char *str) {
  stack *s = {0};
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] == '(' || str[i] == '{' || str[i] == '[')
      push(&s, str[i]);
    else if (str[i] == ')' || str[i] == '}' || str[i] == ']') {
      if (!s)
        return 0;
      char c = pop(&s);
      if (!matchBrac(c, str[i]))
        return 0;
    }
  }
  return s ? 0 : 1;
}

int matchBrac(char c1, char c2) {
  if (c1 == '[' && c2 == ']')
    return 1;
  if (c1 == '{' && c2 == '}')
    return 1;
  if (c1 == '(' && c2 == ')')
    return 1;
  return 0;
}
