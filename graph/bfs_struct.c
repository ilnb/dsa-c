#include "../cleanup.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  struct node *next;
  int index;
} node;

typedef struct queue {
  node *front, *rear;
  int count;
} queue;

typedef struct {
  int *neigh;
  int self;
  int ncount;
} vertices;

typedef struct {
  vertices *vert;
  int vcount;
} graph;

void enqueue(queue *, int);
int dequeue(queue *);
graph new_graph();
void bfs(graph);
void free_graph(graph *);

int main() {
  cl(free_graph) graph g = new_graph();
  int opt;
  bfs(g);
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

void enqueue(queue *q, int x) {
  node *t = malloc(sizeof *t);
  if (!t)
    return;
  t->index = x;
  t->next = NULL;
  if (!q->rear)
    q->front = t;
  else
    q->rear->next = t;
  q->rear = t;
  q->count++;
}

int dequeue(queue *q) {
  if (!q->front)
    return -1;
  node *t = q->front;
  int n = t->index;
  q->front = t->next;
  if (!q->front)
    q->rear = 0;
  free(t);
  q->count--;
  return n;
}

void bfs(graph g) {
  cl(clean_one) int *vis = calloc(g.vcount, sizeof(int));
  queue q = {0};
  enqueue(&q, 0);
  vis[0] = 1;
  while (q.count) {
    int u = dequeue(&q);
    vertices u_vert = g.vert[u];
    printf("Visiting vertex %d\n", u_vert.self);
    for (int i = 0; i < u_vert.ncount; i++) {
      int v = u_vert.neigh[i];
      if (!vis[v]) {
        vis[v] = 1;
        enqueue(&q, v);
      }
    }
  }
}

void free_graph(graph *g) {
  for (int i = 0; i < g->vcount; i++) {
    free(g->vert[i].neigh);
    g->vert[i].neigh = NULL;
    g->vert[i].ncount = 0;
  }
  free(g->vert);
  g->vert = NULL;
  g->vcount = 0;
}
