#ifndef _ARR_H
#define _ARR_H

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// returns an array of n members of size s
static inline void *__arr(int n, size_t s) { return calloc(n, s); }

#define ARR(type, n) __arr(n, sizeof(type))

// returns a row x col matrix of s-sized members
static inline void **__mat(int row, int col, size_t s) {
  void **mat = (void **)malloc(row * sizeof(void *));
  char *data = (char *)calloc(row * col, s);
  for (int i = 0; i < row; i++)
    mat[i] = data + i * col * s;
  return mat;
}

#define MAT(type, r, c) __mat(r, c, sizeof(type))

// free a matrix with row rows
static inline void **__freeMat(void **mat, int row) {
  free(*mat), free(mat);
  return NULL;
}

#define freeMat(mat, row) __freeMat((void **)mat, row)

// print an array of n integers
static inline void printArr(int *arr, int n) {
  for (int i = 0; i < n; i++)
    printf("%3d", arr[i]);
  printf("\n");
}

// input for an array of n integers
static inline void scanArr(int *arr, int len) {
  for (int i = 0; i < len; i++)
    scanf("%d", arr + i);
}

// free mutliple integer arrays
static inline void __freeArrs(void **arrs[], size_t count) {
  for (size_t i = 0; i < count; ++i) {
    free(*arrs[i]);
    *arrs[i] = NULL;
  }
}

#define freeArrs(...)                                                                              \
  __freeArrs((void **[]){__VA_ARGS__}, sizeof((void **[]){__VA_ARGS__}) / sizeof(void **));

// print a row x col matrix
static inline void printMat(int **mat, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++)
      printf("%3d", mat[i][j]);
    printf("\n");
  }
}

// input a row x col matrix
static inline void scanMat(int **mat, int row, int col) {
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      printf("Element %d%d: ", i, j);
      scanf("%d", &mat[i][j]);
    }
}

// returns sum MAT1 + MAT2
static inline int **addMat(int **mat1, int **mat2, int row, int col) {
  int **mat3 = (int **)MAT(int, row, col);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++)
      mat3[i][j] = mat1[i][j] + mat2[i][j];
  return mat3;
}

// returns diff MAT1 - MAT2
static inline int **subMat(int **mat1, int **mat2, int row, int col) {
  int **mat3 = (int **)MAT(int, row, col);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++)
      mat3[i][j] = mat1[i][j] - mat2[i][j];
  return mat3;
}

// returns product MAT1 [row x n] x MAT2 [n x col]
static inline int **mulMat(int **mat1, int **mat2, int row, int n, int col) {
  int **mul = (int **)MAT(int, row, col);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++)
      for (int k = 0; k < n; k++)
        mul[i][j] += mat1[i][k] * mat2[k][j];
  return mul;
}

#endif
