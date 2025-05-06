#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct bst {
  int key;
  struct bst *left, *right;
} bst;

int heightBst(bst *root) {
  if (!root)
    return 0;
  int hl = heightBst(root->left);
  int hr = heightBst(root->right);
  return 1 + (hl > hr ? hl : hr);
}

int nodeCount(bst *root) {
  if (!root)
    return 0;
  return 1 + nodeCount(root->left) + nodeCount(root->right);
}

int minValue(bst *root) {
  if (!root)
    return -69;
  while (root->left)
    root = root->left;
  return root->key;
}

int maxValue(bst *root) {
  if (!root)
    return -69;
  while (root->right)
    root = root->right;
  return root->key;
}

void inorderPrint(bst *root) {
  if (!root)
    return;
  inorderPrint(root->left);
  printf("%d ", root->key);
  inorderPrint(root->right);
}

void preorderPrint(bst *root) {
  if (!root)
    return;
  printf("%d ", root->key);
  preorderPrint(root->left);
  preorderPrint(root->right);
}

void postorderPrint(bst *root) {
  if (!root)
    return;
  postorderPrint(root->left);
  postorderPrint(root->right);
  printf("%d ", root->key);
}

int sameBst(bst *root1, bst *root2) {
  if (!root1 && !root2)
    return 1;
  if (!root1 || !root2)
    return 0;
  int ptsame = root1->key == root2->key;
  int lsame = sameBst(root1->left, root2->left);
  int rsame = sameBst(root1->right, root2->right);
  return ptsame && lsame && rsame;
}

int sameStructure(bst *root1, bst *root2) {
  if (!root1 && !root2)
    return 1;
  if (!root1 || !root2)
    return 0;
  int l = sameStructure(root1->left, root2->left);
  int r = sameStructure(root1->right, root2->right);
  return l && r;
}

int mirrorBst(bst *root1, bst *root2) {
  if (!root1 && !root2)
    return 1;
  if (!root1 || !root2)
    return 0;
  int ptsame = root1->key == root2->key;
  int lmirror = sameBst(root1->left, root2->right);
  int rmirror = sameBst(root1->right, root2->left);
  return ptsame && lmirror && rmirror;
}

bst *copyBst(bst *root) {
  if (!root)
    return NULL;
  bst *new = malloc(sizeof(bst));
  new->key = root->key;
  new->left = copyBst(root->left);
  new->right = copyBst(root->right);
  return new;
}

int isValidBstHelper(bst *root, int min, int max) {
  if (!root)
    return 1;
  if (root->key <= min || root->key >= max)
    return 0;
  int l = isValidBstHelper(root->left, min, root->key);
  int r = isValidBstHelper(root->right, root->key, max);
  return l && r;
}

int validBst(bst *root) { return isValidBstHelper(root, INT_MIN, INT_MAX); }
