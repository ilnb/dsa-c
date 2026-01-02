#include "../cleanup.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int **matrix;
  int vcount;
} graph;

void dfs_visit(graph g, int *vis, int u) {
  vis[u] = 1;
  printf("Visiting vertex %d\n", u);
  for (int v = 0; v < g.vcount; v++)
    if (g.matrix[u][v] && !vis[v])
      dfs_visit(g, vis, v);
}

void dfs(graph g) {
  [[gnu::cleanup(clean_one)]] int *vis = calloc(g.vcount, sizeof(int));
  for (int i = 0; i < g.vcount; i++)
    if (!vis[i])
      dfs_visit(g, vis, i);
}
