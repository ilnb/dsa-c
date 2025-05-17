#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int index;
  struct node *next;
} node;

typedef struct {
  int self;
  int *neigh;
  int ncount;
} vertices;

typedef struct {
  vertices *vert;
  int vcount;
} graph;

graph new_graph();
void free_graph(graph *);
void dfs_visit(graph, int *, int);
void dfs(graph);

int main() {
  graph graph = new_graph();
  dfs(graph);
  goto exit;
  // while (1) {
  //   printf("Wanna find something? [1/0]:");
  //   int choice;
  //   scanf("%d", &choice);
  //   switch (choice) {
  //     case 1: {
  //       printf("Enter the value you want to find: ");
  //       int val;
  //       scanf("%d", &val);
  //       if (find_bfs(graph, val))
  //         printf("The vertex was found.\n");
  //       else
  //         printf("Not found.\n");
  //     }
  //     case 2:
  //       goto exit;
  //   }
  // }
exit: {
  free_graph(&graph);
  printf("Exited.\n");
}
  return 0;
}

graph new_graph() {
  graph g;
  printf("How many vertices? ");
  scanf("%d", &g.vcount);
  g.vert = malloc(sizeof(vertices) * g.vcount);
  for (int i = 0; i < g.vcount; i++) {
    printf("Vertice: %d\n", i);
    printf("Enter the vertex: ");
    scanf("%d", &g.vert[i].self);
    printf("n(Neighbours): ");
    scanf("%d", &g.vert[i].ncount);
    g.vert[i].neigh = calloc(g.vert[i].ncount, sizeof(int));
    printf("Index of:\n");
    for (int j = 0; j < g.vert[i].ncount;) {
      printf("Neighbour %d: ", j);
      scanf("%d", g.vert[i].neigh + j);
      if (g.vert[i].neigh[j] < 0 || g.vert[i].neigh[j] >= g.vcount)
        printf("Invalid index.\n");
      else
        j++;
    }
  }
  return g;
}

void free_graph(graph *g) {
  for (int i = 0; i < g->vcount; i++) {
    free(g->vert[i].neigh);
    g->vert[i].ncount = 0;
  }
  free(g->vert);
  g->vcount = 0;
}

void dfs_visit(graph g, int *visited, int u_index) {
  visited[u_index] = 1;
  printf("Visiting vertex %d\n", g.vert[u_index].self);
  for (int i = 0; i < g.vert[u_index].ncount; i++) {
    int neigh_index = g.vert[u_index].neigh[i];
    if (!visited[neigh_index])
      dfs_visit(g, visited, neigh_index);
  }
}

void dfs(graph g) {
  int *visited = calloc(g.vcount, sizeof(int));
  for (int i = 0; i < g.vcount; i++)
    if (!visited[i])
      dfs_visit(g, visited, i);
  free(visited);
}
