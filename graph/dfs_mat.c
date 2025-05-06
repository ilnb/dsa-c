#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int **matrix;
  int vcount;
} graph;

void dfs_visit(graph g, int *visited, int u) {
  visited[u] = 1;
  printf("Visiting vertex %d\n", u);
  for (int v = 0; v < g.vcount; v++) {
    if (g.matrix[u][v] && !visited[v])
      dfs_visit(g, visited, v);
  }
}

void dfs(graph g) {
  int *visited = calloc(g.vcount, sizeof(int));
  for (int i = 0; i < g.vcount; i++) {
    if (!visited[i])
      dfs_visit(g, visited, i);
  }
  free(visited);
}
