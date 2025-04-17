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
  int self;
  int *neigh;
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
  graph graph = new_graph();
  bfs(graph);
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

void enqueue(queue *q_ptr, int index) {
  node *t = malloc(sizeof(node));
  if (!t) {
    printf("Queue overflow.\n");
    return;
  }
  t->index = index;
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
  // consider the first entry in
  // the vertices array as the root
  enqueue(&q, 0);
  visited[0] = 1;
  while (q.count) {
    int u_index = dequeue(&q);
    vertices u = g.vert[u_index];
    printf("Visiting vertex %d\n", u.self);
    for (int i = 0; i < u.ncount; i++) {
      int neigh_index = u.neigh[i];
      if (!visited[neigh_index]) {
        visited[neigh_index] = 1;
        enqueue(&q, neigh_index);
      }
    }
  }
  free(visited);
}

void free_graph(graph *g) {
  for (int i = 0; i < g->vcount; i++) {
    free(g->vert[i].neigh);
    g->vert[i].ncount = 0;
  }
  free(g->vert);
  g->vcount = 0;
}
