#include "../cleanup.h"
#include <stdlib.h>

typedef struct {
  int **matrix;
  int vcount;
} graph;

int dfs_cycle(graph g, int *vis, int u, int p)
{
  vis[u] = 1;
  for (int v = 0; v < g.vcount; v++)
    if (g.matrix[u][v]) {
      if (!vis[v]) {
        if (dfs_cycle(g, vis, v, u))
          return 1;
      } else if (v != p)
        return 1;
    }
  return 0;
}

int detect_cycle(graph g)
{
  cl(clean_one) int *vis = calloc(g.vcount, sizeof(int));
  for (int i = 0; i < g.vcount; i++) {
    if (!vis[i])
      if (dfs_cycle(g, vis, i, -1)) {
        free(vis);
        return 1;
      }
  }
  return 0;
}
