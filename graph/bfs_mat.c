#include <stdio.h>
#include <stdlib.h>

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

void bfs(graph g) {
  int *visited = calloc(g.vcount, sizeof(int));
  queue q = {0};
  enqueue(&q, 0);
  visited[0] = 1;
  while (q.count) {
    int u = dequeue(&q);
    printf("Visiting vertex %d\n", u);
    for (int v = 0; v < g.vcount; v++) {
      if (g.matrix[u][v] && !visited[v]) {
        visited[v] = 1;
        enqueue(&q, v);
      }
    }
  }
  free(visited);
}
