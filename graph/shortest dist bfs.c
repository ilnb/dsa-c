#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  int index;
  struct node *next;
} node;

typedef struct queue {
  node *front, *rear;
  int count;
} queue;

typedef struct {
  int **matrix;
  int vcount;
} graph;

void enqueue(queue *q_ptr, int val) {
  node *t = malloc(sizeof(node));
  if (!t) {
    printf("Queue overflow.\n");
    return;
  }
  t->index = val;
  t->next = NULL;
  if (!q_ptr->rear)
    q_ptr->front = t;
  else
    q_ptr->rear->next = t;
  q_ptr->rear = t;
  q_ptr->count++;
}

int dequeue(queue *q_ptr) {
  if (!q_ptr->front)
    return -1;
  node *t = q_ptr->front;
  int n = t->index;
  q_ptr->front = t->next;
  if (!q_ptr->front)
    q_ptr->rear = 0;
  free(t);
  q_ptr->count--;
  return n;
}

void bfs(graph g, int start) {
  int *visited = calloc(g.vcount, sizeof(int));
  int *distance = malloc(g.vcount * sizeof(int));
  queue q = {0};
  memset(distance, -1, g.vcount * sizeof(int));
  distance[start] = 0;
  enqueue(&q, start);
  visited[start] = 1;
  while (q.count) {
    int u = dequeue(&q);
    // printf("Visiting vertex %d, Distance: %d\n", u, distance[u]);
    for (int v = 0; v < g.vcount; v++) {
      if (g.matrix[u][v] && !visited[v]) {
        visited[v] = 1;
        distance[v] = distance[u] + 1;
        enqueue(&q, v);
      }
    }
  }

  printf("\nFrom vertex %d:\n", start);
  for (int i = 0; i < g.vcount; i++) {
    if (distance[i] == -1)
      printf("Vertex %d is unreachable\n", i);
    else
      printf("Shortest distance to vertex %d: %d\n", i, distance[i]);
  }
  free(visited), free(distance);
}
