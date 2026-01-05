#include "../cleanup.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INF INT_MAX

typedef struct {
  int **matrix;
  int vcount;
} graph;

int min_key(int *key, unsigned char *vis, int vcount) {
  int min = INF, idx = -1;
  for (int v = 0; v < vcount; v++)
    if (!vis[v] && key[v] < min)
      min = key[v], idx = v;
  return idx;
}

void prim_mst(graph g) {
  cl(clean_one) int *p = malloc(g.vcount * sizeof(int));   // To store MST
  cl(clean_one) int *key = malloc(g.vcount * sizeof(int)); // Key values
  cl(clean_one) unsigned char *vis = calloc(g.vcount, 1);  // Included in MST?
  for (int i = 0; i < g.vcount; i++)
    key[i] = INF;
  key[0] = 0;
  for (int i = 0; i < g.vcount - 1; i++) {
    int u = min_key(key, vis, g.vcount);
    vis[u] = 1;
    for (int v = 0; v < g.vcount; v++)
      if (g.matrix[u][v] && !vis[v] && g.matrix[u][v] < key[v])
        p[v] = u, key[v] = g.matrix[u][v];
  }
  printf("Edge \tWeight\n");
  for (int i = 1; i < g.vcount; i++)
    printf("%d - %d \t%d\n", p[i], i, g.matrix[i][p[i]]);
}
