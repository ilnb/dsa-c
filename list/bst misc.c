#include <stdio.h>
typedef struct tree {
  int key;
  struct tree *left, *right;
} tree;

int heightTree(tree *root) {
  if (!root)
    return 0;
  int hl = heightTree(root->left);
  int hr = heightTree(root->right);
  return 1 + (hl > hr ? hl : hr);
}

int nodeCount(tree *root) {
  if (!root)
    return 0;
  return 1 + nodeCount(root->left) + nodeCount(root->right);
}

int minValue(tree *root) {
  if (!root)
    return -69;
  while (root->left)
    root = root->left;
  return root->key;
}

int maxValue(tree *root) {
  if (!root)
    return -69;
  while (root->right)
    root = root->right;
  return root->key;
}

void inorderPrint(tree *root) {
  if (!root)
    return;
  inorderPrint(root->left);
  printf("%d ", root->key);
  inorderPrint(root->right);
  printf("\n");
}

void preorderPrint(tree *root) {
  if (!root)
    return;
  printf("%d ", root->key);
  preorderPrint(root->left);
  preorderPrint(root->right);
  printf("\n");
}

void postorderPrint(tree *root) {
  if (!root)
    return;
  postorderPrint(root->left);
  postorderPrint(root->right);
  printf("%d ", root->key);
  printf("\n");
}
