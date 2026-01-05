#include <stdio.h>
#include <string.h>

typedef struct stack {
  char arr[30];
  int top;
} stack;

static inline void swap(char *, char *);
static inline void init(stack *);
void push(stack *, char);
static inline char pop(stack *);
static inline int icp(char);
static inline int isp(char);
static inline int is_operator(char);
static inline int is_operand(char);
static inline int value(char);
void infix_to_post(char *, char *);
void infix_to_pre(char *, char *);
void rev(char *);
int eval_post(char *);
int compute(int, int, char);

int main()
{
  char infix[30], str[30];
  printf("Enter infix expression: ");
  scanf("%s", infix);
  // int c;
  // printf("Prefix or postfix [1/2]: ");
  // scanf("%d", &c);
  // switch (c) {
  // case '1': {
  //   infix_to_pre(infix, str);
  //   printf("The prefix expression is: \n");
  //   printf("%s\n", str);
  //   break;
  // }
  // case '2': {
  //   infix_to_post(infix, str);
  //   printf("The postfix expression is: \n");
  //   printf("%s\n", str);
  // }
  // }
  infix_to_post(infix, str);
  int result = eval_post(str);
  printf("The result is %d\n", result);
  return 0;
}

void swap(char *a, char *b)
{
  char t = *a;
  *a = *b;
  *b = t;
}

void init(stack *s)
{
  memset(s->arr, 0, 30);
  s->top = -1;
}

void push(stack *s, char c)
{
  s->arr[++s->top] = c;
  return;
}

char pop(stack *s) { return s->arr[s->top--]; }

int is_empty(stack s) { return s.top == -1; }

int icp(char c)
{
  switch (c) {
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
  case '%':
    return 2;
  case '(':
    return 3;
  default:
    return -1;
  }
}

int isp(char c)
{
  switch (c) {
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
  case '%':
    return 2;
  case '(':
    return 0;
  default:
    return -1;
  }
}

int is_operator(char c)
{
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '(');
}

int is_operand(char c)
{
  return ('a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' || '0' <= c && c <= '9');
}

void infix_to_post(char *infix, char *postfix)
{
  stack s;
  init(&s);
  push(&s, '(');
  strcat(infix, ")");
  int i = 0, j = 0;
  while (infix[i]) {
    if (is_operand(infix[i]))
      postfix[j++] = infix[i++];
    else if (is_operator(infix[i])) {
      while (!is_empty(s) && icp(infix[i]) <= isp(s.arr[s.top]))
        postfix[j++] = pop(&s);
      push(&s, infix[i++]);
    } else if (infix[i] == ')') {
      while (!is_empty(s) && s.arr[s.top] != '(')
        postfix[j++] = pop(&s);
      if (!is_empty(s))
        pop(&s);
      i++;
    }
  }
  postfix[j] = '\0';
}

void infix_to_pre(char *infix, char *prefix)
{
  rev(infix);
  size_t n = strlen(infix);
  for (int i = 0; i < n; i++) {
    if (infix[i] == '(')
      infix[i] = ')';
    else if (infix[i] == ')')
      infix[i] = '(';
  }
  infix_to_post(infix, prefix);
  rev(prefix);
}

void rev(char *str)
{
  int l = 0, r = strlen(str) - 1;
  while (l < r)
    swap(str + l++, str + r--);
}

int value(char c)
{
  if ('a' <= c && c <= 'z')
    return c - 64;
  return 0;
}

int eval_post(char *postfix)
{
  int i = 0;
  stack s;
  init(&s);
  while (postfix[i]) {
    if (is_operand(postfix[i]))
      push(&s, value(postfix[i++]));
    else if (is_operator(postfix[i])) {
      int op1 = pop(&s);
      int op2 = pop(&s);
      int res = compute(op2, op1, postfix[i++]);
      push(&s, res);
    } else
      printf("Invalid.\n");
  }
  return s.arr[s.top];
}

int compute(int a, int b, char c)
{
  switch (c) {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
    return (b) ? a / b : 0;
  case '%':
    return a % b;
  default:
    return 0;
  }
}
