#include "arr.h"

typedef struct {
  int row, col, val;
} sparse;

sparse *createSparse(int **, int, int);
void printFromSparse(sparse *);
sparse *addSparse(sparse *, sparse *);
sparse *transSparse(sparse *);
sparse *mulSparse(sparse *, sparse *);

int main(void) {
  int **mat1 = Mat(3, 3);
  mat1[0][0] = 1, mat1[1][0] = 2, mat1[2][2] = 1;
  sparse *sparseMat1 = createSparse(mat1, 3, 3);
  printf("Parent matrix of the first sparse matrix:\n");
  printFromSparse(sparseMat1);
  sparse *trans = transSparse(sparseMat1);
  printf("Trans of it is:\n");
  printFromSparse(trans);
  int **mat2 = Mat(3, 3);
  mat2[0][2] = 1, mat2[1][0] = -2, mat2[2][0] = 1;
  sparse *sparseMat2 = createSparse(mat2, 3, 3);
  printf("Parent matrix of the second sparse matrix:\n");
  printFromSparse(sparseMat2);
  sparse *sparseMat3 = addSparse(sparseMat1, sparseMat2);
  printf("Matrix after adding the parent matrices:\n");
  printFromSparse(sparseMat3);
  freeMat(mat1, 3), freeMat(mat2, 3);
  mat1 = mat2 = NULL;
  freeArrs(4, &sparseMat1, &sparseMat2, &sparseMat3, &trans);
  return 0;
}

sparse *createSparse(int **mat, int row, int col) {
  int count = 0;
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (mat[i][j] != 0)
        count++;
    }
  }
  if (!count) {
    printf("No non-zero data found.\n");
    return NULL;
  }
  sparse *sparseMat = malloc(sizeof(sparse) * (count + 1));
  sparseMat[0] = (sparse){row, col, count};
  int k = 1;
  for (int i = 0; i < row; i++) {
    if (k <= count) {
      for (int j = 0; j < col; j++) {
        if (k <= count && mat[i][j])
          sparseMat[k++] = (sparse){i, j, mat[i][j]};
      }
    }
  }
  return sparseMat;
}

void printFromSparse(sparse *sparseMat) {
  int k = 1;
  for (int i = 0; i < sparseMat[0].row; i++) {
    for (int j = 0; j < sparseMat[0].col; j++) {
      if (k <= sparseMat[0].val && i == sparseMat[k].row &&
          j == sparseMat[k].col)
        printf("%3d", sparseMat[k++].val);
      else
        printf("%3d", 0);
    }
    printf("\n");
  }
}

sparse *addSparse(sparse *a, sparse *b) {
  if (a[0].row != b[0].row || a[0].col != b[0].col) {
    printf("The dimensions of the two are different.\n");
    return NULL;
  }
  int count = 0, i = 1, j = 1;
  while (i <= a[0].val && j <= b[0].val) {
    if (a[i].row == b[j].row && a[i].col == b[j].col) {
      if (a[i].val + b[j].val)
        count++;
      i++, j++;
    } else if (a[i].row < b[j].row ||
               a[i].row == b[j].row && a[i].col < b[j].col)
      count++, i++;
    else
      count++, j++;
  }
  while (i <= a[0].val)
    count++, i++;
  while (j <= b[0].val)
    count++, j++;
  sparse *add = malloc((count + 1) * sizeof(*add));
  add[0] = (sparse){a[0].row, a[0].col};
  i = 1, j = 1;
  int k = 1;
  while (i <= a[0].val && j <= b[0].val) {
    if (a[i].row == b[j].row && a[i].col == b[j].col) {
      if (a[i].val + b[j].val) {
        add[k] = (sparse){a[i].row, a[i].col};
        add[k++].val = a[i].val + b[j].val;
      }
      i++, j++;
    } else if (a[i].row < b[j].row ||
               (a[i].row == b[j].row && a[i].col < b[j].col))
      add[k++] = a[i++];
    else
      add[k++] = b[j++];
  }
  while (i <= a[0].val)
    add[k++] = a[i++];
  while (j <= b[0].val)
    add[k++] = b[j++];
  add[0].val = k - 1;
  return add;
}

sparse *transSparse(sparse *a) {
  int min = a[1].col;
  int max = a[1].col;
  for (int i = 1; i <= a[0].val; i++) {
    if (max < a[i].col)
      max = a[i].col;
    if (min > a[i].col)
      min = a[i].col;
  }
  int countLen = max - min + 1;
  int *count = Arr(countLen);
  for (int i = 1; i <= a[0].val; i++)
    count[a[i].col - min]++;
  int *t = Arr(countLen);
  t[0] = 1;
  for (int i = 1; i < countLen; i++)
    t[i] = t[i - 1] + count[i - 1];
  sparse *trans = malloc(sizeof(sparse) * (a[0].val + 1));
  trans[0] = (sparse){a[0].col, a[0].row, a[0].val};
  for (int i = 1; i <= a[0].val; i++)
    trans[t[a[i].col - min]++] = (sparse){a[i].col, a[i].row, a[i].val};
  freeArrs(2, &t, &count);
  return trans;
}

sparse *mulSparse(sparse *a, sparse *b) {
  if (a[0].col != b[0].row) {
    printf("The dimensions are not compatible.\n");
    return NULL;
  }
  sparse *mul = malloc(sizeof(sparse));
  mul[0] = (sparse){a[0].row, a[0].col};
  int i = 1, j = 1, k = 1;
  return mul;
}
