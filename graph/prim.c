#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INF INT_MAX

typedef struct {
  int **matrix;
  int vcount;
} graph;

int minKey(int *key, unsigned char *in_set, int vcount) {
  int min = INF, min_index = -1;
  for (int v = 0; v < vcount; v++)
    if (!in_set[v] && key[v] < min)
      min = key[v], min_index = v;
  return min_index;
}

void primMST(graph g) {
  int *parent = malloc(g.vcount * sizeof(int)); // To store MST
  int *key = malloc(g.vcount * sizeof(int));    // Key values
  unsigned char *in_set = calloc(g.vcount, 1);  // Included in MST?
  for (int i = 0; i < g.vcount; i++)
    key[i] = INF;
  key[0] = 0;
  for (int i = 0; i < g.vcount - 1; i++) {
    int u = minKey(key, in_set, g.vcount);
    in_set[u] = 1;
    for (int v = 0; v < g.vcount; v++)
      if (g.matrix[u][v] && !in_set[v] && g.matrix[u][v] < key[v])
        parent[v] = u, key[v] = g.matrix[u][v];
  }
  printf("Edge \tWeight\n");
  for (int i = 1; i < g.vcount; i++)
    printf("%d - %d \t%d\n", parent[i], i, g.matrix[i][parent[i]]);
  free(parent), free(key), free(in_set);
}
