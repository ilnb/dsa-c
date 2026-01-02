#ifndef _ARR_H
#define _ARR_H

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// returns an array of n members of size s
static inline void *__arr(int n, size_t s) {
  void *p = calloc(n, s);
  if (!p)
    exit(1);
  return p;
}

#define ARR(type, n) (type *)__arr(n, sizeof(type))

// returns a row x col matrix of s-sized members
static inline void **__mat(int row, int col, size_t s) {
  void **mat = (void **)malloc(row * sizeof(void *));
  if (!mat)
    exit(1);
  char *data = (char *)calloc(row * col, s);
  if (!data)
    exit(1);
  for (int i = 0; i < row; i++)
    mat[i] = data + i * col * s;
  return mat;
}

#define MAT(type, r, c) (type **)__mat(r, c, sizeof(type))

// free a matrix with row rows
static inline void **__free_mat(void **mat) {
  free(*mat), free(mat);
  return NULL;
}

#define free_mat(mat) (void *)__free_mat((void **)mat)

// print an array of n integers
static inline void print_arr(int *arr, int n) {
  for (int i = 0; i < n; i++)
    printf("%3d", arr[i]);
  printf("\n");
}

// input for an array of n integers
static inline void scan_arr(int *arr, int n) {
  for (int i = 0; i < n; i++)
    scanf("%d", arr + i);
}

// free mutliple integer arrays
static inline void __free_arrs(void **arrs[], size_t count) {
  for (size_t i = 0; i < count; ++i) {
    free(*arrs[i]);
    *arrs[i] = NULL;
  }
}

#define free_arrs(...)                                                                             \
  __free_arrs((void **[]){__VA_ARGS__}, sizeof((void **[]){__VA_ARGS__}) / sizeof(void **));

// print a row x col matrix
static inline void print_mat(int **mat, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++)
      printf("%3d", mat[i][j]);
    printf("\n");
  }
}

// input a row x col matrix
static inline void scan_mat(int **mat, int row, int col) {
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      printf("Element %d%d: ", i, j);
      scanf("%d", &mat[i][j]);
    }
}

// returns sum MAT1 + MAT2
static inline int **add_mat(int **mat1, int **mat2, int row, int col) {
  int **mat3 = MAT(int, row, col);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++)
      mat3[i][j] = mat1[i][j] + mat2[i][j];
  return mat3;
}

// returns diff MAT1 - MAT2
static inline int **sub_mat(int **mat1, int **mat2, int row, int col) {
  int **mat3 = MAT(int, row, col);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++)
      mat3[i][j] = mat1[i][j] - mat2[i][j];
  return mat3;
}

// returns product MAT1 [row x n] x MAT2 [n x col]
static inline int **mul_mat(int **mat1, int **mat2, int row, int n, int col) {
  int **mul = MAT(int, row, col);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++)
      for (int k = 0; k < n; k++)
        mul[i][j] += mat1[i][k] * mat2[k][j];
  return mul;
}

#endif
