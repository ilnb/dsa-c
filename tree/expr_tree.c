#include <stdio.h>
#include <stdlib.h>

typedef struct bst {
  struct bst *left;
  struct bst *right;
  int val;
} bst;

static inline bst *new_node(int val) {
  bst *t = malloc(sizeof *t);
  *t = (bst){.val = val};
  return t;
}

void inorder_bst(bst *root) {
  if (!root)
    return;
  int n = root->left && root->right;
  if (n)
    printf("(");
  inorder_bst(root->left);
  printf("%c", root->val);
  inorder_bst(root->right);
  if (n)
    printf(")");
  printf("\n");
}

int main() {
  bst *root = new_node('-');
  root->left = new_node('3');
  root->right = new_node('*');
  bst *r = root->right;
  r->left = new_node('2');
  r->right = new_node('x');
  inorder_bst(root);
  return 0;
}
