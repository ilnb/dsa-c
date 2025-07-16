#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INF INT_MAX

typedef struct {
  int **matrix;
  int vcount;
} graph;

int minKey(int *key, int *mstSet, int vcount) {
  int min = INF, min_index = -1;
  for (int v = 0; v < vcount; v++)
    if (!mstSet[v] && key[v] < min)
      min = key[v], min_index = v;
  return min_index;
}

void primMST(graph g) {
  int *parent = malloc(g.vcount * sizeof(int)); // To store MST
  int *key = malloc(g.vcount * sizeof(int));    // Key values
  int *mstSet = calloc(g.vcount, sizeof(int));  // Included in MST?
  for (int i = 0; i < g.vcount; i++)
    key[i] = INF;
  key[0] = 0;
  for (int i = 0; i < g.vcount - 1; i++) {
    int u = minKey(key, mstSet, g.vcount);
    mstSet[u] = 1;
    for (int v = 0; v < g.vcount; v++)
      if (g.matrix[u][v] && !mstSet[v] && g.matrix[u][v] < key[v])
        parent[v] = u, key[v] = g.matrix[u][v];
  }
  printf("Edge \tWeight\n");
  for (int i = 1; i < g.vcount; i++)
    printf("%d - %d \t%d\n", parent[i], i, g.matrix[i][parent[i]]);
  free(parent), free(key), free(mstSet);
}
