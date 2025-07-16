#include <stdlib.h>

typedef struct {
  int **matrix;
  int vcount;
} graph;

int dfs_cycle(graph g, int *visited, int u, int parent) {
  visited[u] = 1;
  for (int v = 0; v < g.vcount; v++)
    if (g.matrix[u][v]) {
      if (!visited[v]) {
        if (dfs_cycle(g, visited, v, u))
          return 1;
      } else if (v != parent)
        return 1;
    }
  return 0;
}

int detect_cycle(graph g) {
  int *visited = calloc(g.vcount, sizeof(int));
  for (int i = 0; i < g.vcount; i++)
    if (!visited[i])
      if (dfs_cycle(g, visited, i, -1)) {
        free(visited);
        return 1;
      }
  free(visited);
  return 0;
}
