#ifndef _ARR_H
#define _ARR_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// returns an array of n members of size s
static inline void *_arr(size_t n, size_t s) {
  void *p = calloc(n, s);
  if (!p)
    exit(1);
  return p;
}

#define ARR(type, n) _arr(n, sizeof(type))

// free an array
static inline void _free_arr(void *arr) {
  void **ptr = arr;
  free(*ptr);
  *ptr = NULL;
}

#define free_arr(arr) _free_arr(&(arr))

// returns a row x col flat matrix of s-sized members
static inline void *_mat(int row, int col, size_t s) {
  void **mat = malloc(row * sizeof(void *));
  if (!mat)
    exit(1);
  char *data = calloc(row * col, s);
  if (!data)
    exit(1);
  for (int i = 0; i < row; i++)
    mat[i] = data + i * col * s;
  return mat;
}

#define MAT(type, r, c) _mat(r, c, sizeof(type))

// free a flat matrix
static inline void _free_mat(void *mat) {
  void ***ptr = mat;
  free(**ptr);
  free(*ptr);
  *ptr = NULL;
}

#define free_mat(mat) _free_mat(&(mat))

// free a matrix with r rows
static inline void _free_mat_r(void *mat, size_t r) {
  void ***ptr = mat;
  for (int i = 0; i < r; i++) {
    void *row = i[*ptr];
    free(row);
  }
  free(*ptr);
  *ptr = NULL;
}

#define free_mat_r(mat, r) _free_mat_r(&(mat), r)

// print an array of n integers
static inline void print_arr(int *arr, size_t n) {
  for (int i = 0; i < n; i++)
    printf("%3d", arr[i]);
  printf("\n");
}

// input for an array of n integers
static inline void scan_arr(int *arr, size_t n) {
  for (int i = 0; i < n; i++)
    scanf("%d", arr + i);
}

// free mutliple arrays
static inline void _free_arrs(void *arrs[], size_t count) {
  for (size_t i = 0; i < count; i++)
    _free_arr(arrs[i]);
}

#define free_arrs(...)                                                                             \
  _free_arrs((void *[]){__VA_ARGS__}, sizeof((void *[]){__VA_ARGS__}) / sizeof(void *));

// free mutliple arrays
static inline void _free_mats(void *mats[], size_t count) {
  for (size_t i = 0; i < count; i++)
    _free_mat(mats[i]);
}

#define free_mats(...)                                                                             \
  _free_mats((void *[]){__VA_ARGS__}, sizeof((void *[]){__VA_ARGS__}) / sizeof(void *));

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
