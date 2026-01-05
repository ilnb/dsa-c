#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct bst {
  struct bst *left, *right;
  int val;
} bst;

int height_bst(bst *root) {
  if (!root)
    return 0;
  int hl = height_bst(root->left);
  int hr = height_bst(root->right);
  return 1 + (hl > hr ? hl : hr);
}

int node_count(bst *root) {
  if (!root)
    return 0;
  return 1 + node_count(root->left) + node_count(root->right);
}

int min_val_bst(bst *root) {
  if (!root)
    return INT_MAX;
  while (root->left)
    root = root->left;
  return root->val;
}

int max_val_bst(bst *root) {
  if (!root)
    return INT_MIN;
  while (root->right)
    root = root->right;
  return root->val;
}

void inorder_bst(bst *root) {
  if (!root)
    return;
  inorder_bst(root->left);
  printf("%d ", root->val);
  inorder_bst(root->right);
}

void preorder_bst(bst *root) {
  if (!root)
    return;
  printf("%d ", root->val);
  preorder_bst(root->left);
  preorder_bst(root->right);
}

void postorder_bst(bst *root) {
  if (!root)
    return;
  postorder_bst(root->left);
  postorder_bst(root->right);
  printf("%d ", root->val);
}

int is_same_bst(bst *root1, bst *root2) {
  if (!root1 && !root2)
    return 1;
  if (!root1 || !root2)
    return 0;
  int ptsame = root1->val == root2->val;
  int lsame = is_same_bst(root1->left, root2->left);
  int rsame = is_same_bst(root1->right, root2->right);
  return ptsame && lsame && rsame;
}

int same_struct_bst(bst *root1, bst *root2) {
  if (!root1 && !root2)
    return 1;
  if (!root1 || !root2)
    return 0;
  int l = same_struct_bst(root1->left, root2->left);
  int r = same_struct_bst(root1->right, root2->right);
  return l && r;
}

int mirror_bst(bst *root1, bst *root2) {
  if (!root1 && !root2)
    return 1;
  if (!root1 || !root2)
    return 0;
  int ptsame = root1->val == root2->val;
  int lmirror = mirror_bst(root1->left, root2->right);
  int rmirror = mirror_bst(root1->right, root2->left);
  return ptsame && lmirror && rmirror;
}

bst *copy_bst(bst *root) {
  if (!root)
    return NULL;
  bst *new = malloc(sizeof(bst));
  new->val = root->val;
  new->left = copy_bst(root->left);
  new->right = copy_bst(root->right);
  return new;
}

int __valid_bst(bst *root, int min, int max) {
  if (!root)
    return 1;
  if (root->val <= min || root->val >= max)
    return 0;
  int l = __valid_bst(root->left, min, root->val);
  int r = __valid_bst(root->right, root->val, max);
  return l && r;
}

#define valid_bst(root) __valid_bst(root, INT_MIN, INT_MAX)

int _valid_bst(bst *root) { return __valid_bst(root, INT_MIN, INT_MAX); }
