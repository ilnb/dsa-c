#include <stdio.h>
#include <stdlib.h>

typedef struct bst {
  struct bst *left;
  struct bst *right;
  int val;
} bst;

void menu();
bst *new_node(int);
bst *push_node(bst *, int);
bst *pop_node(bst *, int);
bst *search(bst *, int);
bst *free_bst(bst *);
int min_val_bst(bst *);
int inorder(bst *);

int main() {
  bst *root = NULL;
  int opt = 0;
  do {
    menu();
    printf("What do you want to do? ");
    scanf("%d", &opt);
    switch (opt) {
    case 1: {
      printf("Enter the value: ");
      int val;
      scanf("%d", &val);
      root = push_node(root, val);
      break;
    }
    case 2: {
      printf("Enter the value: ");
      int val;
      scanf("%d", &val);
      root = pop_node(root, val);
      break;
    }
    case 3: {
      printf("Inorder: ");
      int n = inorder(root);
      if (!n)
        printf("Empty bst.\n");
      else
        printf("\n");
      break;
    }
    case 4: {
      root = free_bst(root);
      break;
    }
    case 5: {
      printf("Enter the value: ");
      int val;
      scanf("%d", &val);
      bst *n = search(root, val);
      if (n)
        printf("Value found.\n");
      else
        printf("Value not found.\n");
      break;
    }
    case 6:
      break;
    default:
      printf("Invalid opt.\n");
    }
  } while (opt != 6);
}

void menu() {
  printf("1. Insert a new node\n");
  printf("2. Delete a node\n");
  printf("3. Print the bst\n");
  printf("4. Free the bst\n");
  printf("5. Search a value\n");
  printf("6. Exit\n");
}

bst *new_node(int val) {
  bst *q = malloc(sizeof *q);
  *q = (bst){.val = val};
  return q;
}

bst *push_node(bst *root, int val) {
  bst *t = new_node(val);
  if (!root)
    return t;
  bst *p = root;
  while (1) {
    if (p->left && val < p->val)
      p = p->left;
    else if (p->right && val > p->val)
      p = p->right;
    else
      break;
  }
  val < p->val ? (p->left = t) : (p->right = t);
  return root;
}

bst *pop_node(bst *root, int val) {
  if (!root)
    return root;
  bst *q = NULL, *p = root;
  while (p && val != p->val) {
    if (val < p->val) {
      q = p;
      p = p->left;
    } else if (val > p->val) {
      q = p;
      p = p->right;
    } else
      break;
  }
  if (!p)
    return root;
  // case 1: root or leaf nodes
  if (!p->left && !p->right) {
    if (!q) {
      free(p);
      return NULL;
    }
    p == q->left ? (q->left = NULL) : (q->right = NULL);
    free(p);
    return root;
  }
  // case 2: single child
  if (!p->left || !p->right) {
    bst *r = p->left ? p->left : p->right;
    if (!q) {
      free(p);
      return r;
    }
    p == q->left ? (q->left = r) : (q->right = r);
    free(p);
    return root;
  }
  // case 3: two childs
  // left can be used to,
  // with the max element
  int n = min_val_bst(root->right);
  p->val = n;
  p->right = pop_node(p->right, n);
  return root;
}

bst *search(bst *root, int val) {
  if (!root)
    return NULL;
  if (val == root->val)
    return root;
  else if (val > root->val)
    return search(root->right, val);
  else
    return search(root->left, val);
}

bst *free_bst(bst *root) {
  if (!root)
    return NULL;
  free_bst(root->left);
  free_bst(root->right);
  free(root);
  return NULL;
}

int inorder(bst *root) {
  if (!root)
    return 0;
  inorder(root->left);
  printf("%d ", root->val);
  inorder(root->right);
  return 1;
}

int min_val_bst(bst *root) {
  if (!root)
    return -69;
  while (root->left)
    root = root->left;
  return root->val;
}
