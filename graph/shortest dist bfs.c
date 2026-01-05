#include "../cleanup.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  struct node *next;
  int index;
} node;

typedef struct queue {
  node *front, *rear;
  int count;
} queue;

typedef struct {
  int **matrix;
  int vcount;
} graph;

void enqueue(queue *q, int x)
{
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

int dequeue(queue *q)
{
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

void bfs(graph g, int s)
{
  cl(clean_one) int *vis = calloc(g.vcount, sizeof(int));
  cl(clean_one) int *d = malloc(g.vcount * sizeof(int));
  queue q = {0};
  memset(d, -1, g.vcount * sizeof(int));
  d[s] = 0;
  enqueue(&q, s);
  vis[s] = 1;
  while (q.count) {
    int u = dequeue(&q);
    // printf("Visiting vertex %d, Distance: %d\n", u, distance[u]);
    for (int v = 0; v < g.vcount; v++)
      if (g.matrix[u][v] && !vis[v]) {
        vis[v] = 1;
        d[v] = d[u] + 1;
        enqueue(&q, v);
      }
  }

  printf("\nFrom vertex %d:\n", s);
  for (int i = 0; i < g.vcount; i++) {
    if (d[i] == -1)
      printf("Vertex %d is unreachable\n", i);
    else
      printf("Shortest distance to vertex %d: %d\n", i, d[i]);
  }
}
