# Chapter 6 Graphs
Graph is the most another method generalised method to represent data structure.
* Pros: Can be applied to many different places, most general structure
* Cons: Difficult to implement

## Contents
1. [Introduction](#1-introduction)
2. [Basic Operations](#2-basic-operations)
3. [Minimum Cost Spanning Trees](#3-minimum-cost-spanning-trees)
4. [Shortest Paths and Transitive Closure](#4-shortest-paths-and-transitive-closure)
5. [Examples](#5-examples)

## 1. Introduction
### Terminology
```
[DEFINITION] Graphs
Graph G=(V,E) is a set consists of two different set V and E which represents Vertices and Edges in the graph.
```

#### Directed Graph vs. Undirected Graph
If there is a direction in edge used in a graph, between two vertices, then it is called **directed graph**,
otherwise called **undirected graph**.

We represents edge in **directed graph** as <u, v>, for the edge from u to v where u is called **tail** while v is called 
**head**. <u, v> and <v, u> are different to each other.

We represents edge in **undirected graph** as (u, v), for the edge incident with u and v where u and v are both called as 
**end point**. (u, v) and (v, u) are identical to each other.

#### Restriction in this chapter
Since we are considering **Simple Graph** we exclude 1) self loop and 2) multiple edges between two different vertices, 
otherwise we called it **multigraph**.

#### Subgraph
Subgraph is a graph made from original graph G using a subgroup of its vertex set V and edge set E

#### Path
Path is a set of edges or a sequence of vertices from vertex u to v in a graph G, and we call **length** for the number of
edges used in a path, while the **simple path** is the path that does not visit the same edge twice.

**Cycle** is a special path whose beginin and end edge is identical, meaning path from u to u is cycle (circuit)

#### Connected Component
We say two vertices are **connected** if there is a path between two. Specifically, for directed graph, we classify connectivity 
by 1) strongly connected and 2) weakly connected, while **strongly connected** means there is a path from v to u and 
a path from u to v exists for every pair u, v in V. While **weakly connected** implies that there is a path between any vertex
as undirected path.

**Connected Component** is an undirected graph is a maximal connected subgraph.

### Implementation
We can implement graph using 1) adjacency matrix or 2) adjacency list

#### Adjacency Matrix
This method is simple to implement by putting 1 if two elements are connected otherwise 0.
However this may cause huge waste of memory it there is not much edges compare to its vertices,
ofcourse it is easy to check whether two vertices are connected!

_c.f.,_
1) Since there is no loop or multiple edges, the matrix is zero-one while diagonal is all 0.
2) However, we can represent multiple edges, loop and even direction of the edges.

#### Adjacency List
Opposite to the matrix implementation. If there are sparse edges or not regular rule between edges (_i.e.,_ degree of vertex
is different), then it is good idea to use list representation.
This will be implemented by linked list staring from one-dimentional array, so it would be quite difficult to implement and 
takes time to search whether two vertices are connected or not.

```c
typedef struct node* node_pointer;
typedef struct{
  int vertex;
  node_pointer link;
} node;

node_pointer graph[MAX_VERTICES];
```

## 2. Basic Operations
### Depth First Search (DFS)
#### Definition
Depth First Search is finding goal nodes by traversing through all connected vertex (possible to visit at the current position) unless it is already visited. The traverse stops when the goal node is reached or the stack is empty.

_c.f.,_
1) Its complexity using adjacency list is O(V), but O(n^2) if we use matrix because we need to visit all the elements of the matrix to search all the possible way to traverse.
2) Stack is the key of this algorithm!

#### Implementation
```c
//assume that v is just given as starting vertex
void dfs(int v){
  node_pointer w = NULL;
  
  visited[v] = TRUE; /* base case */
  printf("%5d", v); /* base case */
  for(w = graph[v]; w; w = w->link) /* from starting point to all of its connected nodes */
    if(!visited[w->vertex])
      dfs(w->vertex);
}
```

### Breadth First Search (BFS)
#### Definition
Breadth First Search is finding goal nodes by traversing at each level completely by printing all the connected vertices from the started vertex while adding to queue. Letting extend to visit the unvisited vertices which we have found at this moment. The traverse stops when the goal node is reached or the queue is empty.

_c.f.,_
1) Its complexity using adjacency list is O(E) because we visit all connected edges and decide whether to visit or not, unlike dfs(visit directly after new vertex is found). However O(n^2) if we use matrix because we need to visit all the elements of the matrix to search all the possible way to traverse.
2) Queue is the key of this algorithm!

#### Implementation
```c
//need queue to implement this function

typedef struct queue* queue_pointer;
typedef struct{
  int vertex;
  queue_pointer link;
} queue;

void addq(queue_pointer *, queue_pointer *, int);
int deleteq(queue_pointer *);

void bfs(int v){
  node_pointer w;
  queue_pointer front, rear;
  front = rear = NULL;
  
  printf("%5d", v); /* base case */
  visited[v] = TRUE; /* base case */
  addq(&front, &rear, v); /* basecase */
  
  while(front){
    v = deleteq(&front);
    for(w = graph[v]; w; w = w->link)
      if(!visited[w->vertex]){
        printf("%5f", w->vertex);
        addq(&front, &rear, w->vertex);
        visited[w->vertex] = TRUE;
      }
  }
}
```

#### DFS vs. BFS
Depending on situation, if the goal is at the left-most position, then DFS is better, but if the goal is at the right-upper position, then BFS is faster. Hence, the each algorithms complexity is depends on the situation. Hence there is a algorithm that mix two algorithm called **Iterative Depth Search**, which is mainly used in AI. This operate DFS by setting maximum depth.

### Connected Components
#### Definition
To find the connected components, use either dfs or bfs then prints only visited vertex.

_c.f.,_
1) The complexity of the algorithm is O(n+e) using adjacency list and dfs, because we need to traverse all the vertices for choosing the vertex to start dfs, while dfs needs O(e) complexity.

#### Implementation
```c
void connected(void){
  int i;
  
  for(i=0; i<n; i++){ /* this loop let to start dfs at all possible vertex if it is still unvisited */
    if(!visited[i]){
      dfs(i); /* dfs(i) would print all the connected vertices from vertex i */
      printf("\n");
}
```

### Spanning Trees
#### Definition

#### Implementation

### Biconnected Components and Articulation Points
#### Definition

#### Implementation

## 3. Minimum Cost Spanning Trees
### Kruskal's Algorithm

### Prim's Algorithm

### Sollin's Algorithm

## 4. Shortest Paths and Transitive Closure
### Single Source All Destination Algorithm (1): Dijkstra's Algorithm

### Single Source All Destination Algorithm (2): Bellman-Ford's Algorithm

### All Source All Destination Algorithm (ASAD)

## 5. Examples
