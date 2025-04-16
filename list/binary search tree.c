#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
  struct tree *left;
  int key;
  struct tree *right;
} tree;

void menu();
tree *newNode(int);
tree *insertNode(tree *, int);
tree *deleteNode(tree *, int);
tree *searchInTree(tree *, int);
tree *freeTree(tree *);
int minValue(tree *);
int inorderPrint(tree *);

int main() {
  tree *root = NULL;
  int option = 0;
  do {
    menu();
    printf("What do you want to do? ");
    scanf("%d", &option);
    switch (option) {
      case 1: {
        printf("Enter the value: ");
        int val;
        scanf("%d", &val);
        root = insertNode(root, val);
        break;
      }
      case 2: {
        printf("Enter the value: ");
        int val;
        scanf("%d", &val);
        root = deleteNode(root, val);
        break;
      }
      case 3: {
        printf("Inorder: ");
        int n = inorderPrint(root);
        if (!n)
          printf("Empty tree.\n");
        else
          printf("\n");
        break;
      }
      case 4: {
        root = freeTree(root);
        break;
      }
      case 5: {
        printf("Enter the value: ");
        int val;
        scanf("%d", &val);
        tree *n = searchInTree(root, val);
        if (n)
          printf("Value found.\n");
        else
          printf("Value not found.\n");
        break;
      }
      case 6:
        break;
      default:
        printf("Invalid option.\n");
    }
  } while (option != 6);
}

void menu() {
  printf("1. Insert a new node\n");
  printf("2. Delete a node\n");
  printf("3. Print the tree\n");
  printf("4. Free the tree\n");
  printf("5. Search a value\n");
  printf("6. Exit\n");
}

tree *newNode(int val) {
  tree *q = malloc(sizeof(*q));
  q->key = val;
  q->left = NULL;
  q->right = NULL;
  return q;
}

tree *insertNode(tree *root, int val) {
  tree *t = newNode(val);
  if (!root)
    return t;
  tree *p = root;
  while (1) {
    if (p->left && val < p->key)
      p = p->left;
    else if (p->right && val > p->key)
      p = p->right;
    else
      break;
  }
  if (val < p->key)
    p->left = t;
  else
    p->right = t;
  return root;
}

tree *deleteNode(tree *root, int val) {
  if (!root)
    return root;
  tree *q = NULL, *p = root;
  while (p && val != p->key) {
    if (val < p->key) {
      q = p;
      p = p->left;
    } else if (val > p->key) {
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
    if (p == q->left)
      q->left = NULL;
    else
      q->right = NULL;
    free(p);
    return root;
  }
  // case 2: single child
  if (!p->left || !p->right) {
    tree *r;
    r = p->left ? p->left : p->right;
    if (!q) {
      free(p);
      return r;
    }
    if (p == q->left)
      q->left = r;
    else
      q->right = r;
    free(p);
    return root;
  }
  // case 3: two childs
  // left can be used to,
  // with the max element
  int n = minValue(root->right);
  p->key = n;
  p->right = deleteNode(p->right, n);
  return root;
}

tree *searchInTree(tree *root, int val) {
  if (!root)
    return NULL;
  if (val < root->key)
    return searchInTree(root->left, val);
  else if (val > root->key)
    return searchInTree(root->right, val);
  else
    return root;
}

tree *freeTree(tree *root) {
  if (!root)
    return NULL;
  freeTree(root->left);
  freeTree(root->right);
  free(root);
  return NULL;
}

int inorderPrint(tree *root) {
  if (!root) {
    return 0;
  }
  inorderPrint(root->left);
  printf("%d ", root->key);
  inorderPrint(root->right);
  return 1;
}

int minValue(tree *root) {
  if (!root)
    return -69;
  while (root->left)
    root = root->left;
  return root->key;
}
