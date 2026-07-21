# Planets and Kingdoms

## Problem

- **Source:** [CSES 1683, Planets and Kingdoms](https://cses.fi/problemset/task/1683/)
- **Code:** [`View accepted C++ solution (planetskingdoms.cpp)`](../planetskingdoms.cpp)
- **Constraints:** 1 <= n <= 100000 and 1 <= m <= 200000.

Partition the vertices of a directed graph into kingdoms so that two vertices receive the same label exactly when each is reachable from the other. Print the number of kingdoms and one kingdom label for every vertex.

These equivalence classes are the graph's strongly connected components, or SCCs.

## Idea

Reachability from one DFS root is insufficient: a DFS tree records paths away from its root, not mutual reachability. Running a search from every vertex would cost $O(n(n+m))$.

Kosaraju's algorithm uses two complete traversals. The first DFS runs on the original graph and records vertices by finishing time. Contract every SCC into one vertex. The resulting condensation graph is a DAG. If there is an edge from component $C$ to distinct component $D$, a DFS that enters $D$ through that edge cannot return to $C$, so $D$ finishes before $C$. Thus decreasing finishing time orders source components before their descendants.

Reverse every edge. A source SCC of the remaining condensation graph becomes a sink: from it, the reversed graph cannot escape to an unassigned SCC. Starting a reverse-graph search at the greatest-finishing unassigned vertex therefore visits exactly its SCC.

The implementation reproduces recursive postorder with explicit frames `(vertex, next edge index)`. A vertex is appended only after every outgoing edge has been examined. This avoids recursion depth failure on a path of $10^5$ vertices.

## Algorithm

1. Build the graph `adj` and its edge-reversed graph `radj`.
2. For every unvisited vertex, perform iterative DFS on `adj`:
   - each stack frame stores the next outgoing edge to examine;
   - after all edges are processed, append the vertex to `order_`.
3. Scan `order_` backward.
4. Whenever an unassigned vertex is found, create a new component label and traverse from it in `radj`, assigning that label to every reached unassigned vertex.
5. Print the number of labels and each vertex's label.

## Correctness

### Lemma 1

If the condensation graph contains an edge from SCC $C$ to distinct SCC $D$, and the first DFS reaches $D$ while exploring from $C$, every vertex of $D$ finishes before the initiating vertex in $C$.

#### Proof

DFS must complete all recursively or explicitly stacked exploration reachable through the edge into $D$ before it can finish the frame in $C$. Because distinct SCCs cannot have a return path from $D$ to $C$, exploration of $D$ does not make $C$ part of the same unfinished strongly connected region. Hence $D$'s vertices are appended earlier. $\square$

### Lemma 2

At each second-pass search, the chosen unassigned start vertex belongs to an SCC with no reversed edge to another unassigned SCC.

#### Proof

Equivalently, its SCC has no original incoming edge from an unassigned SCC. If such an edge $X\to C$ existed, finishing-time order on the condensation DAG would place an appropriate vertex of $X$ after vertices of $C$, so $X$ would appear earlier in the backward scan. It would have been selected first, contradicting that $C$ is the current greatest-finishing unassigned component. $\square$

### Lemma 3

One second-pass traversal assigns exactly one SCC.

#### Proof

All vertices inside the start's SCC remain mutually reachable after every edge is reversed, so the traversal reaches the entire SCC. By Lemma 2, it cannot cross a reversed edge into a different unassigned SCC. Previously assigned vertices are explicitly ignored. Thus it assigns precisely the start's SCC. $\square$

### Theorem

The algorithm outputs exactly the strongly connected components of the graph.

#### Proof

Every second-pass search assigns exactly one SCC by Lemma 3. The backward scan eventually encounters every still-unassigned vertex, so every SCC is assigned once. Therefore two vertices share a printed label exactly when they are mutually reachable. $\square$

## Implementation

The first stack stores `pair<int,int>`. Its second field is a referenceable cursor inside the frame. Incrementing it before pushing a child ensures the parent resumes at the following edge.

`comp[v] == 0` means unassigned because actual component labels begin at 1. The second traversal needs only a vertex stack since no finishing order is produced there.

## Complexity

Each traversal examines every vertex and edge at most once. Time is $O(n+m)$ and auxiliary space is $O(n+m)$ for both adjacency lists, traversal stacks, and arrays.

## Worked Example

Consider edges $1\to2$, $2\to1$, $2\to3$, $3\to4$, and $4\to3$. The SCCs are $C_1=\{1,2\}$ and $C_2=\{3,4\}$, with condensation edge $C_1\to C_2$.

The first pass finishes vertices in $C_2$ before the initiating vertices in $C_1$. Scanning backward therefore selects $C_1$ first. In the reversed graph, its search cannot cross into $C_2$ because the intercomponent edge now points from $C_2$ to $C_1$. The next search assigns $C_2$ separately.
