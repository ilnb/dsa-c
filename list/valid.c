#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define match_brac(c1, c2)                                                                         \
  ((c1 == '[' && c2 == ']') || (c1 == '{' && c2 == '}') || (c1 == '(' && c2 == ')'))

typedef struct stack {
  struct stack *next;
  char val;
} stack;

int valid_check(char *);
void push(stack **, char);
char pop(stack **);

int main()
{
  printf("Enter the expression: ");
  char str[50] = {0};
  scanf("%s", str);
  int valid = valid_check(str);
  if (valid)
    printf("Valid expression.\n");
  else
    printf("Invalid expression.\n");
  return 0;
}

void push(stack **s, char c)
{
  stack *q = malloc(sizeof *q);
  q->val = c;
  q->next = *s;
  *s = q;
}

char pop(stack **s)
{
  if (!*s)
    return 0;
  stack *t = *s;
  char c = t->val;
  *s = (*s)->next;
  free(t);
  return c;
}

int valid_check(char *str)
{
  stack *s = NULL;
  for (int i = 0; i < strlen(str); i++) {
    if (str[i] == '(' || str[i] == '{' || str[i] == '[')
      push(&s, str[i]);
    else if (str[i] == ')' || str[i] == '}' || str[i] == ']') {
      if (!s)
        return 0;
      char c = pop(&s);
      if (!match_brac(c, str[i]))
        return 0;
    }
  }
  return s ? 0 : 1;
}
