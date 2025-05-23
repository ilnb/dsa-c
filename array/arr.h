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

// returns a row x col matrix
int **Mat(int row, int col) {
  int **Mat = (int **)malloc(row * sizeof(int *));
  for (int i = 0; i < row; i++)
    Mat[i] = (int *)calloc(col, sizeof(int));
  return Mat;
}

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
int **freeMat(int **arr, int row) {
  for (int i = 0; i < row; i++) {
    free(arr[i]);
    arr[i] = NULL;
  }
  free(arr);
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
void printMat(int **Mat, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++)
      printf("%3d", Mat[i][j]);
    printf("\n");
  }
}

// input a row x col matrix
void scanMat(int **Mat, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      printf("Element %d%d: ", i, j);
      scanf("%d", &Mat[i][j]);
    }
  }
}

// returns sum MAT1 + MAT2
int **addMat(int **Mat1, int **Mat2, int row, int col) {
  int **Mat3 = Mat(row, col);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++)
      Mat3[i][j] = Mat1[i][j] + Mat2[i][j];
  return Mat3;
}

// returns diff MAT1 - MAT2
int **subMat(int **Mat1, int **Mat2, int row, int col) {
  int **Mat3 = Mat(row, col);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++)
      Mat3[i][j] = Mat1[i][j] - Mat2[i][j];
  return Mat3;
}

// returns product MAT1 x MAT2
int **mulMat(int **Mul1, int **Mul2, int row, int n, int col) {
  int **Mul = Mat(row, col);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++)
      for (int k = 0; k < n; k++)
        Mul[i][j] += Mul1[i][k] * Mul2[k][j];
  return Mul;
}

#endif
