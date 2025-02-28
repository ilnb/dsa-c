#ifndef _ARR_H
#define _ARR_H

#include <stdio.h>
#include <stdlib.h>

int *Arr(int len) {
  int *arr = (int *)calloc(len, sizeof(int));
  return arr;
}

int **Mat(int row, int col) {
  int **Mat = (int **)malloc(row * sizeof(int *));
  for (int i = 0; i < row; i++) {
    Mat[i] = (int *)calloc(col, sizeof(int));
  }
  return Mat;
}

void printArr(int *arr, int len) {
  for (int i = 0; i < len; i++) {
    printf("%3d", arr[i]);
  }
  printf("\n");
}

void scanArr(int *arr, int len) {
  for (int i = 0; i < len; i++) {
    scanf("%d", arr + i);
  }
}

int **freeMat(int **arr, int row) {
  for (int i = 0; i < row; i++) {
    free(arr[i]);
    arr[i] = NULL;
  }
  free(arr);
  return NULL;
}

void printMat(int **Mat, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      printf("%3d", Mat[i][j]);
    }
    printf("\n");
  }
}

void scanMat(int **Mat, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      printf("Element %d%d: ", i, j);
      scanf("%d", &Mat[i][j]);
    }
  }
}

int **addMat(int **Mat1, int **Mat2, int row, int col) {
  int **Mat3 = Mat(row, col);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      Mat3[i][j] = Mat1[i][j] + Mat2[i][j];
    }
  }
  return Mat3;
}

int **subMat(int **Mat1, int **Mat2, int row, int col) {
  int **Mat3 = Mat(row, col);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      Mat3[i][j] = Mat1[i][j] - Mat2[i][j];
    }
  }
  return Mat3;
}

int **mulMat(int **Mul1, int **Mul2, int row, int n, int col) {
  int **Mul = Mat(row, col);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      Mul[i][j] = 0;
      for (int k = 0; k < n; k++) {
        Mul[i][j] += Mul1[i][k] * Mul2[k][j];
      }
    }
  }
  return Mul;
}

#endif
