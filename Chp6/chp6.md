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
Spanning tree is a tree converted from graph by erasing unused edge. Precisely, spanning tree is any tree that 1) consists solely of edges in G and that 2) includes all the vertices in G.

_i.e.,_
1) If we add more edges than spanning tree needed, then cycle would be generated.
2) A spanning tree is a minimal subgraph of G such that V(G) is maintained and connected.
3) To connect n vertices, we need exactly n-1 edges.

#### Implementation
SEE [Section 3](#3-minimum-cost-spanning-trees) below

### Biconnected Components and Articulation Points
#### Definition
**Articulation Point** is a vertex v of G such that the deletion of v, and its edges incident with v, produces a graph that has at least two connected components.

**Biconnected Components** is a graph that contains none of articulation points, which is highly demanded in various area, to generate stable connection.

_i.e.,_
1) Biconnected components of a connected undirected graph is a maximal biconnected subgraph of G.

#### Implementation

## 3. Minimum Cost Spanning Trees
**Cost of the spanning tree** of a weighted undirected graph (_i.e.,_ there are numbers written at each edges), is just sum of the costs of the edges in the spanning tree. 

Our goal is to minimise the cost of the spanning tree, and there are three different greedy algorithm to find this:
1) Kruskal's Algorithm
2) Prim's Algorithm
3) Sollin's Algorithm

_c.f.,_
1) In general, greedy algorithm does not guarantee the optimal path for whole algorithm, but for this case (for a least cost or a highest profit criterion), all of above algorithm (greedy algorithm) guarantees its mimial cost.

### Kruskal's Algorithm
#### Idea
- Repeat the below procedure till all verices are added, which is equivalent to n-1 edges:
  - Keep select the edge in accending order of the cost
  - Check whether the addiditional edge makes loop

#### Implementation
```c
T = {};
while(T contains less than n-1 edges && E is not empty){
  choose a least cost edge (v,w) from E; /* use heap to implement */
  delete (v,w) from E;
  if ((v,w) does not create a cycle in T) /* search: check if there is same vertex in T */
    add (v,w) to T; /* union: add (v,w) in T */
  else
    discard (v,w);
}
if (T contains fewer than n-1 edges)
  printf("No spanning tree\n");
```

### Prim's Algorithm
#### Idea
- Select the edge that has smallest cost. /* base case */
- Repeat the below procedure till all vertices are added, which is equivalent to n-1 edges:
  - Keep select the smaller cost edge incedent with the two end points of current path. (no need to check cycle)

#### Implementation
```c
T = {};
TV= {0}; /* assume that we start from vertex 0; this can be arbitrary set */
while (T contains fewer than n-1 edges){
  let (u,v) be a least cost edge such that u is in TV but not for v; /* by doing this no need to check cycle */
  if(there is no such edge)
    break; /* comparable to the condition E is not empty in the while loop in Kruskal algorithm, and this has further more condtion */
  add v to TV;
  add (u,v) to T;
}
if(T contains fewer than n-1 edges)
  printf("No spanning tree\n");
```

#### Kruskal vs. Prim
The complexity is simillar to kruskal but, Prim may consider the same edge twice or even more, unlike Kruskal, Kruskal can be considered as better algorithm. However, this does not have to check cycle, which is easy to implement!

### Sollin's Algorithm
#### Idea
- Repeat the below procedure till all vertices are added, which is equivalent to n-1 edges:
  - Choose the smaller cost edge from each connected components. (vertex for the first case)
  
#### Implementation
```c
//quite difficult to implement because the program should be operate in parallel (for loop should be done at once)
T = {};
connected_components = {(v) | v in V};
while (T continas fewer than n-1 edges){
  for(c in connected_components){
   choose the the less cost edge (a,b) where a is end vertex of c, but b does not in c; 
  }
}
```

## 4. Shortest Paths and Transitive Closure
Now we want to find the shortest path from vertex to the other verices, if it exist.

Hence, we are going to consider two differnet algorithm:
- Single Source All Destination: Dijkstra (positive distance), Bellman-Ford (general distance)
- All Source All Destination: ASAD

### Single Source All Destination Algorithm (1): Dijkstra's Algorithm
#### Idea
The basic idea is simillar to prim algorithm as follows:
- Repeat following procedure for n-1 times:
  - Consier the shortest path to all vertices except source (if it is connected) from the source
  - Put a vertex in the source that has the shortest path among found path in this stage
  
#### Implementation
```c
#define MAX_VERTICES 6 /* maximum number of vertices */
int cost[][MAX_VERTICES]; /* adjacency martix to represent the cost between path */
int distance[MAX_VERTICES]; /* represents the shortes path from vertex v to i */
shor int found[MAX_VERTICES]; /* represents whether the node has the shortes path; meaning whether it is in source */
int n = MAX_VERTICES;

void shortestpath(int v, int cost[][MAX_VERTICES], int distance[], int n, short int found[]){
  int i, u, w;
  
  //initialisation
  for (i = 0; i < n; i++){
    found[i] = FALSE;
    disance[i] = cost[v][i];
  }
  found[v] = TRUE;
  distance[v] = 0;
  
  //finding path
  for(i = 0; i < n-2; i++){
    u = choose(distance, n, found);
    found[u] = TRUE;
    for(w = 0; w < n; w++){
      if(!found[w])
        if(distance[u] + cost[u][w] < distance[w])
          distance[w] = distance[u] + cost[u][w];
    }
  }
}

//find the smallest distance not yet checked
int choose(int distance[], int n, short int found[]){
  int i, min, minpos;
  min = INT_MAX;
  minpos = -1;
  
  for(i = 0; i < n; i++)
    if(distance[i] < min && !found[i]
      min = distance[i]; minpos = i;
  
  return minpos;
}

```
### Single Source All Destination Algorithm (2): Bellman-Ford's Algorithm

```c
void BellmanFord(int n, int v){
  for(int = 0; i < n; i++)
    dist[i] = length[v][i];
  
  for(int k = 2; k <= n-1; k++)
    for(each u such that u != v and u has at least one incoming edge)
      for(each <i, u> in the graph)
        if(dist[u] > dist[i] + length[i][u])
          dist[u] = dist[i] + length[i][u];
}
```
### All Source All Destination Algorithm (ASAD)

## 5. Examples
