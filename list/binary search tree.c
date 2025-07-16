#include <stdio.h>
#include <stdlib.h>

typedef struct bst {
  int key;
  struct bst *left;
  struct bst *right;
} bst;

void menu();
bst *newNode(int);
bst *insertNode(bst *, int);
bst *deleteNode(bst *, int);
bst *searchInBst(bst *, int);
bst *freeBst(bst *);
int minValue(bst *);
int inorderPrint(bst *);

int main() {
  bst *root = NULL;
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
          printf("Empty bst.\n");
        else
          printf("\n");
        break;
      }
      case 4: {
        root = freeBst(root);
        break;
      }
      case 5: {
        printf("Enter the value: ");
        int val;
        scanf("%d", &val);
        bst *n = searchInBst(root, val);
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
  printf("3. Print the bst\n");
  printf("4. Free the bst\n");
  printf("5. Search a value\n");
  printf("6. Exit\n");
}

bst *newNode(int val) {
  bst *q = malloc(sizeof(*q));
  *q = (bst){val};
  return q;
}

bst *insertNode(bst *root, int val) {
  bst *t = newNode(val);
  if (!root)
    return t;
  bst *p = root;
  while (1) {
    if (p->left && val < p->key)
      p = p->left;
    else if (p->right && val > p->key)
      p = p->right;
    else
      break;
  }
  val < p->key ? (p->left = t) : (p->right = t);
  return root;
}

bst *deleteNode(bst *root, int val) {
  if (!root)
    return root;
  bst *q = NULL, *p = root;
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
  int n = minValue(root->right);
  p->key = n;
  p->right = deleteNode(p->right, n);
  return root;
}

bst *searchInBst(bst *root, int val) {
  if (!root)
    return NULL;
  if (val == root->key)
    return root;
  else if (val > root->key)
    return searchInBst(root->right, val);
  else
    return searchInBst(root->left, val);
}

bst *freeBst(bst *root) {
  if (!root)
    return NULL;
  freeBst(root->left);
  freeBst(root->right);
  free(root);
  return NULL;
}

int inorderPrint(bst *root) {
  if (!root)
    return 0;
  inorderPrint(root->left);
  printf("%d ", root->key);
  inorderPrint(root->right);
  return 1;
}

int minValue(bst *root) {
  if (!root)
    return -69;
  while (root->left)
    root = root->left;
  return root->key;
}
