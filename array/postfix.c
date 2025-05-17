#include <stdio.h>
#include <string.h>

typedef struct stack {
  char arr[30];
  int top;
} stack;

void init(stack *);
void push(stack *, char);
char pop(stack *);
int icp(char);
int isp(char);
int isoperator(char);
int isoperand(char);
void infixtopostfix(char *, char *);
void infixtoprefix(char *, char *);
void rev(char *);
int evaluatePostfix(char *);
int compute(int, int, char);

int main() {
  char infix[30] = {0}, str[30] = {0};
  printf("Enter infix expression: ");
  scanf("%s", infix);
  /* int c;
   printf("Prefix or postfix [1/2]: ");
   scanf("%d", &c);
   switch (c) {
     case 1: {
       infixtoprefix(infix, str);
       printf("The prefix expression is: \n");
       printf("%s\n", str);
       break;
     }
     case 2: {
       infixtopostfix(infix, str);
       printf("The postfix expression is: \n");
       printf("%s\n", str);
       break;
     }
   }*/
  infixtopostfix(infix, str);
  int result = evaluatePostfix(str);
  printf("The result is %d\n", result);
  return 0;
}

void init(stack *s) {
  memset(s->arr, 0, 30);
  s->top = -1;
}

void push(stack *s, char c) {
  s->arr[++s->top] = c;
  return;
}

char pop(stack *s) { return s->arr[s->top--]; }

int isEmpty(stack s) { return s.top == -1; }

int icp(char c) {
  switch (c) {
    case '+':
      return 1;
    case '-':
      return 1;
    case '*':
      return 2;
    case '/':
      return 2;
    case '%':
      return 2;
    case '(':
      return 3;
    default:
      return -1;
  }
}

int isp(char c) {
  switch (c) {
    case '+':
      return 1;
    case '-':
      return 1;
    case '*':
      return 2;
    case '/':
      return 2;
    case '%':
      return 2;
    case '(':
      return 0;
    default:
      return -1;
  }
}

int isoperator(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '(');
}

int isoperand(char c) {
  return ('a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' || '0' <= c && c <= '9');
}

void infixtopostfix(char *infix, char *postfix) {
  stack s;
  init(&s);
  push(&s, '(');
  strcat(infix, ")");
  int i = 0, j = 0;
  while (infix[i] != '\0') {
    if (isoperand(infix[i]))
      postfix[j++] = infix[i++];
    else if (isoperator(infix[i])) {
      while (!isEmpty(s) && icp(infix[i]) <= isp(s.arr[s.top]))
        postfix[j++] = pop(&s);
      push(&s, infix[i++]);
    } else if (infix[i] == ')') {
      while (!isEmpty(s) && s.arr[s.top] != '(')
        postfix[j++] = pop(&s);
      if (!isEmpty(s))
        pop(&s);
      i++;
    }
  }
  postfix[j] = '\0';
}

void infixtoprefix(char *infix, char *prefix) {
  rev(infix);
  for (int i = 0; i < strlen(infix); i++) {
    if (infix[i] == '(')
      infix[i] = ')';
    else if (infix[i] == ')')
      infix[i] = '(';
  }
  infixtopostfix(infix, prefix);
  rev(prefix);
}

void rev(char *str) {
  int n = strlen(str);
  for (int i = 0; i < n / 2; i++) {
    int t = str[i];
    str[i] = str[n - i - 1];
    str[n - i - 1] = t;
  }
}

int value(char c) {
  if ('a' <= c && c <= 'z')
    return c - 64;
  return 0;
}

int evaluatePostfix(char *postfix) {
  int i = 0;
  stack s;
  init(&s);
  while (postfix[i]) {
    if (isoperand(postfix[i]))
      push(&s, value(postfix[i++]));
    else if (isoperator(postfix[i])) {
      int op1 = pop(&s);
      int op2 = pop(&s);
      int result = compute(op2, op1, postfix[i++]);
      push(&s, result);
    } else
      printf("Invalid.\n");
  }
  return s.arr[s.top];
}

int compute(int a, int b, char c) {
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
