#include "arr.h"

typedef struct {
  int row, col, val;
} sparse;

sparse *mk_sp(int **, int, int);
void print_sp(sparse *);
sparse *add_sp(sparse *, sparse *);
sparse *trans_sp(sparse *);
sparse *mul_sp(sparse *, sparse *);

int main()
{
  int **mat1 = MAT(int, 3, 3);
  mat1[0][0] = 1, mat1[1][0] = 2, mat1[2][2] = 1;
  int **mat2 = MAT(int, 3, 3);
  mat2[0][2] = 1, mat2[1][0] = -2, mat2[2][0] = 1;

  sparse *sm1 = mk_sp(mat1, 3, 3);
  printf("Parent matrix of the first sparse matrix:\n");
  print_sp(sm1);

  sparse *trans = trans_sp(sm1);
  printf("Trans of it is:\n");
  print_sp(trans);

  sparse *sm2 = mk_sp(mat2, 3, 3);
  printf("Parent matrix of the second sparse matrix:\n");
  print_sp(sm2);

  sparse *sm3 = add_sp(sm1, sm2);
  printf("Matrix after adding the parent matrices:\n");
  print_sp(sm3);

  free_mats(&mat1, &mat2);
  free_arrs(&sm1, &sm2, &sm3, &trans);
  return 0;
}

sparse *mk_sp(int **mat, int row, int col)
{
  int count = 0;
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++)
      if (mat[i][j])
        count++;
  if (!count) {
    printf("No non-zero data found.\n");
    return NULL;
  }
  sparse *sm = ARR(sparse, count + 1);
  sm[0] = (sparse){row, col, count};
  int k = 1;
  for (int i = 0; i < row; i++)
    if (k <= count)
      for (int j = 0; j < col; j++)
        if (k <= count && mat[i][j])
          sm[k++] = (sparse){i, j, mat[i][j]};
  return sm;
}

void print_sp(sparse *sm)
{
  int k = 1;
  const int r = sm[0].row, c = sm[0].col;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (k <= sm[0].val && i == sm[k].row && j == sm[k].col)
        printf("%3d", sm[k++].val);
      else
        printf("%3d", 0);
    }
    printf("\n");
  }
}

sparse *add_sp(sparse *a, sparse *b)
{
  if (a[0].row != b[0].row || a[0].col != b[0].col) {
    printf("The dimensions of the two are different.\n");
    return NULL;
  }
  int count = 0, i = 1, j = 1;
  while (i <= a[0].val && j <= b[0].val) {
    int ar = a[i].row, ac = a[i].col;
    int br = b[j].row, bc = b[j].col;
    int av = a[i].val, bv = b[j].val;
    if (ar == br && ac == bc) {
      if (av + bv)
        count++;
      i++, j++;
    } else if (ar < br || ar == br && ac < bc)
      count++, i++;
    else
      count++, j++;
  }
  while (i <= a[0].val)
    count++, i++;
  while (j <= b[0].val)
    count++, j++;
  sparse *add = ARR(sparse, count + 1);
  add[0] = (sparse){a[0].row, a[0].col, count};
  i = 1, j = 1;
  int k = 1;
  while (i <= a[0].val && j <= b[0].val) {
    int ar = a[i].row, ac = a[i].col;
    int br = b[j].row, bc = b[j].col;
    int av = a[i].val, bv = b[j].val;
    if (ar == br && ac == bc) {
      if (av + bv) {
        add[k] = (sparse){ar, ac};
        add[k++].val = av + bv;
      }
      i++, j++;
    } else if (ar < br || ar == br && ac < bc)
      add[k++] = a[i++];
    else
      add[k++] = b[j++];
  }
  while (i <= a[0].val)
    add[k++] = a[i++];
  while (j <= b[0].val)
    add[k++] = b[j++];
  return add;
}

sparse *trans_sp(sparse *a)
{
  int min = a[1].col, max = a[1].col;
  int n = a[0].val;
  for (int i = 2; i <= n; i++) {
    if (max < a[i].col)
      max = a[i].col;
    if (min > a[i].col)
      min = a[i].col;
  }
  int countn = max - min + 1;
  [[gnu::cleanup(_free_arr)]] int *count = ARR(int, countn);
  for (int i = 1; i <= n; i++)
    count[a[i].col - min]++;
  [[gnu::cleanup(_free_arr)]] int *t = ARR(int, countn);
  t[0] = 1;
  for (int i = 1; i < countn; i++)
    t[i] = t[i - 1] + count[i - 1];
  sparse *trans = ARR(sparse, n + 1);
  trans[0] = (sparse){a[0].col, a[0].row, n};
  for (int i = 1; i <= n; i++)
    trans[t[a[i].col - min]++] = (sparse){a[i].col, a[i].row, a[i].val};
  return trans;
}

sparse *mul_sp(sparse *a, sparse *b)
{
  if (a[0].col != b[0].row) {
    printf("The dimensions are not compatible.\n");
    return NULL;
  }
  sparse *mul;
  // TODO: implement multiplication
  return mul;
}
