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
  int **matrix;
  int vcount;
} graph;

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
  [[gnu::cleanup(clean_one)]] int *vis = calloc(g.vcount, sizeof(int));
  queue q = {0};
  enqueue(&q, 0);
  vis[0] = 1;
  while (q.count) {
    int u = dequeue(&q);
    printf("Visiting vertex %d\n", u);
    for (int v = 0; v < g.vcount; v++)
      if (g.matrix[u][v] && !vis[v]) {
        vis[v] = 1;
        enqueue(&q, v);
      }
  }
}
