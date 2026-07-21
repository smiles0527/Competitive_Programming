# Shortest Routes II

## Problem

- **Source:** [CSES 1672: Shortest Routes II](https://cses.fi/problemset/task/1672/)
- **Code:** [`View accepted C++ solution (shortestroutes2.cpp)`](./shortestroutes2.cpp)
- **Constraints:** $1\le n\le500$, $1\le m,q\le100000$, and $1\le w\le10^9$.

Answer shortest-path queries in an undirected weighted graph.

## Idea

The number of queries makes running a separate shortest-path algorithm for every pair too slow. The small vertex count allows Floyd-Warshall in $O(n^3)$ time.

After processing intermediate vertices $1,\ldots,k$, let $d[u][v]$ be the shortest path from $u$ to $v$ whose internal vertices belong to that set. A best path either excludes $k$ or uses it. In the second case, splitting the path at $k$ gives

$$
d[u][v]\gets\min\bigl(d[u][v],d[u][k]+d[k][v]\bigr).
$$

This recurrence considers every path according to the greatest-numbered intermediate vertex it uses.

## Algorithm

1. Set $d[u][u]=0$ and every other distance to infinity.
2. Insert every undirected edge in both directions, keeping the lightest parallel edge.
3. Run Floyd-Warshall with the intermediate-vertex loop outermost.
4. Answer every query directly from the resulting matrix.

## Correctness

Induct on the processed intermediate vertices. Before iteration $k$, $d[u][v]$ is optimal among paths whose internal vertices are smaller than $k$. A path allowed after the iteration either avoids $k$, preserving the old value, or uses $k$ and splits into two paths whose internal vertices are smaller than $k$. The transition takes the minimum over exactly these two cases.

After processing all vertices, every graph path is permitted, so every finite table entry is a true shortest distance. Infinity remains exactly for disconnected pairs.

## Implementation

The intermediate-vertex loop must be outermost to preserve the DP invariant. The infinity value leaves enough headroom for adding two finite official distances. Parallel edges are initialized using `min`.

## Complexity

Preprocessing takes $O(n^3)$ time and $O(n^2)$ space. Each query takes $O(1)$ time.

## Worked Example

If edges $1-2$ and $2-3$ have weights 4 and 5, while edge $1-3$ has weight 12, processing intermediate vertex 2 improves $d[1][3]$ from 12 to 9.
