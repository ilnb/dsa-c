#include <stdio.h>
#include <stdlib.h>
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
}

void preorderPrint(tree *root) {
  if (!root)
    return;
  printf("%d ", root->key);
  preorderPrint(root->left);
  preorderPrint(root->right);
}

void postorderPrint(tree *root) {
  if (!root)
    return;
  postorderPrint(root->left);
  postorderPrint(root->right);
  printf("%d ", root->key);
}

int sameTree(tree *root1, tree *root2) {
  if (!root1 && !root2)
    return 1;
  if (!root1 || !root2)
    return 0;
  int ptsame = root1->key == root2->key;
  int lsame = sameTree(root1->left, root2->left);
  int rsame = sameTree(root1->right, root2->right);
  return ptsame && lsame && rsame;
}

int mirrorTree(tree *root1, tree *root2) {
  if (!root1 && !root2)
    return 1;
  if (!root1 || !root2)
    return 0;
  int ptsame = root1->key == root2->key;
  int lmirror = sameTree(root1->left, root2->right);
  int rmirror = sameTree(root1->right, root2->left);
  return ptsame && lmirror && rmirror;
}

tree *copyTree(tree *root) {
  if (!root)
    return NULL;
  tree *new = malloc(sizeof(tree));
  new->key = root->key;
  new->left = copyTree(root->left);
  new->right = copyTree(root->right);
  return new;
}
