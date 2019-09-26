#include <vector>
#include <queue>

using namespace std;

const int INFINITE = 0x3c3c3c3c;

class Edge {
 public:
  int src;
  int dest;
  int weight;
};

class Graph {
 public:
  int vertexCount;
  int edgeCount;
  vector<Edge> edges;

  Graph(int vertex_count, int edge_count) {
    this->vertexCount = vertex_count;
    this->edgeCount = edge_count;
    this->edges.reserve((unsigned)edge_count);
  }

  void addEdge(int src, int dest, int weight) {
    Edge *e = new Edge();
    e->src = src;
    e->dest = dest;
    e->weight = weight;

    this->edges.push_back(*e);
  }
};

vector<int> dist;
vector<int> from;

void bellmanFord(Graph* g) {
  int isChange;

  int oldDist, newDist;
  do {
    isChange = 0;

    for (auto edge : g->edges) {
      oldDist = dist[edge.dest];
      newDist = dist[edge.src] + edge.weight;

      if (newDist < oldDist) {
        dist[edge.dest] = newDist;
        from[edge.dest] = edge.src;

        isChange = 1;
      }
    }
  } while(isChange);
}

int main() {
  int vertex_count = 8;
  int edge_count = 16;

  dist.assign(8, INFINITE);
  dist[0] = 0;
  from.assign(8, -1);

  Graph *g = new Graph(vertex_count, edge_count);
  g->addEdge(0, 1, 5);
  g->addEdge(0, 4, 9);
  g->addEdge(0, 7, 8);
  g->addEdge(1, 2, 12);
  g->addEdge(1, 3, 15);
  g->addEdge(1, 7, 4);
  g->addEdge(2, 3, 3);
  g->addEdge(2, 6, 11);
  g->addEdge(3, 6, 9);
  g->addEdge(4, 5, 4);
  g->addEdge(4, 6, 20);
  g->addEdge(4, 7, 5);
  g->addEdge(5, 2, 1);
  g->addEdge(5, 6, 13);
  g->addEdge(7, 5, 6);
  g->addEdge(7, 2, 7);

  bellmanFord(g);

  int i;

  printf("dist\n--------------------\n");
  for (i = 0; i < vertex_count; i++) {
    printf("%d: %d\n", i, dist[i]);
  }

  printf("\nfrom\n--------------------\n");
  for (i = 1; i < vertex_count; i++) {
    printf("%d: %d\n", i, from[i]);
  }

  int src, curr;
  printf("\nshortest path\n--------------------\n");
  for (i = 1; i < vertex_count; i++) {
    curr = i;

    printf("%d<-", i);
    while (curr != 0) {
      src = from[curr];
      printf("%d<-", src);
      curr = src;
    }

    printf("\n");
  }

  return 0;
}
