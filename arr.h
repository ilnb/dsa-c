#ifndef _ARR_H
#define _ARR_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// retuns an array of n integers
int *Arr(int n) {
  int *arr = (int *)calloc(n, sizeof(int));
  return arr;
}

// returns an array of n members of size s
void *pArr(int n, int s) { return malloc(n * s); }

// returns a row x col matrix
int **Mat(int row, int col) {
  int **mat = (int **)malloc(row * sizeof(int));
  int *data = (int *)calloc(row * col, sizeof(int));
  for (int i = 0; i < row; i++)
    mat[i] = data + i * col;
  return mat;
}

// int **Mat(int row, int col) {
//   int **mat = (int **)malloc(row*sizeof(int*));
//   for (int i = 0; i < col; i++)
//     mat[i] = (int *)calloc(col, sizeof(int));
//   return mat;
// }

// returns a row x col matrix of s-sized members
void **pMat(int row, int col, int s) {
  void **mat = (void **)malloc(row * s);
  char *data = (char *)malloc(row * col * s);
  for (int i = 0; i < row; i++)
    mat[i] = data + i * col * s;
  return mat;
}

// void **pMat(int row, int col, int s) {
//   void **mat = (void **)malloc(row *sizeof(void *));
//   for (int i= 0; i <row; i++)
//     mat[i] = malloc(col *s);
//   return mat;
// }

// print an array of n integers
void printArr(int *arr, int n) {
  for (int i = 0; i < n; i++)
    printf("%3d", arr[i]);
  printf("\n");
}

// input for an array of n integers
void scanArr(int *arr, int len) {
  for (int i = 0; i < len; i++)
    scanf("%d", arr + i);
}

// free a matrix with row rows
int **freeMat(int **mat, int row) {
  free(*mat), free(mat);
  return NULL;
}

// free mutliple integer arrays
void freeArrs(int count, ...) {
  va_list ptr;
  va_start(ptr, count);
  for (int i = 0; i < count; i++) {
    void **t = va_arg(ptr, void **);
    free(*t);
    *t = NULL;
  }
  va_end(ptr);
}

// print a row x col matrix
void printMat(int **mat, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++)
      printf("%3d", mat[i][j]);
    printf("\n");
  }
}

// input a row x col matrix
void scanMat(int **mat, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      printf("Element %d%d: ", i, j);
      scanf("%d", &mat[i][j]);
    }
  }
}

// returns sum MAT1 + MAT2
int **addMat(int **mat1, int **mat2, int row, int col) {
  int **mat3 = Mat(row, col);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++)
      mat3[i][j] = mat1[i][j] + mat2[i][j];
  return mat3;
}

// returns diff MAT1 - MAT2
int **subMat(int **mat1, int **mat2, int row, int col) {
  int **mat3 = Mat(row, col);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++)
      mat3[i][j] = mat1[i][j] - mat2[i][j];
  return mat3;
}

// returns product MAT1 x MAT2
int **mulMat(int **mul1, int **mul2, int row, int n, int col) {
  int **mul = Mat(row, col);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++)
      for (int k = 0; k < n; k++)
        mul[i][j] += mul1[i][k] * mul2[k][j];
  return mul;
}

#endif
