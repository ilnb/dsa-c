#include <stdio.h>
#include <stdlib.h>
typedef struct bst {
  struct bst *left;
  int key;
  struct bst *right;
} bst;

bst *newNode(int val) {
  bst *t = malloc(sizeof(bst));
  t->key = val;
  t->left = t->right = 0;
  return t;
}

void inOrder(bst *root) {
  if (!root)
    return;
  int n = root->left && root->right;
  if (n)
    printf("(");
  inOrder(root->left);
  printf("%c", root->key);
  inOrder(root->right);
  if (n)
    printf(")");
}

int main() {
  bst *root = newNode('-');
  root->left = newNode('3');
  root->right = newNode('*');
  bst *r = root->right;
  r->left = newNode('2');
  r->right = newNode('x');
  inOrder(root);
  printf("\n");
  return 0;
}
