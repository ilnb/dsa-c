#include <stdio.h>
#include <stdlib.h>

typedef struct bst {
  int key;
  struct bst *left;
  struct bst *right;
} bst;

bst *newNode(int val) {
  bst *t = malloc(sizeof(bst));
  *t = (bst){val};
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
  printf("\n");
}

int main() {
  bst *root = newNode('-');
  root->left = newNode('3');
  root->right = newNode('*');
  bst *r = root->right;
  r->left = newNode('2');
  r->right = newNode('x');
  inOrder(root);
  return 0;
}
