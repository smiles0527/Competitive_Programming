# Shortest Routes I

## Problem

- **Source:** [CSES 1671: Shortest Routes I](https://cses.fi/problemset/task/1671/)
- **Code:** [`View accepted C++ solution (shortestroutes1.cpp)`](./shortestroutes1.cpp)
- **Constraints:** $1\le n\le100000$, $1\le m\le200000$, and $1\le w\le10^9$.

Compute shortest directed-path distances from vertex 1 to every vertex in a graph with nonnegative edge weights.

## Idea

The constraints rule out Bellman-Ford because of its $O(nm)$ running time. Nonnegative edge weights allow Dijkstra's algorithm. Maintain tentative distances and repeatedly process the queued state with the smallest distance.

When `(dist[v], v)` is popped and matches the current value of `dist[v]`, no later path can make it smaller. Any unprocessed path reaches its first unprocessed vertex through a settled prefix and then adds only nonnegative weight, so its length is at least the smallest key currently in the queue. Relaxing the outgoing edges exposes every path whose settled prefix ends at $v$.

The priority queue may contain stale entries with larger distances after later improvements. These entries are ignored when popped.

## Algorithm

1. Set every distance to infinity except the source distance, which is zero.
2. Push `(0,1)` into a min-priority queue.
3. Pop states, skip stale ones, relax every outgoing edge, and push each improvement.
4. Print the distance array.

## Correctness

By Dijkstra's cut argument, every nonstale popped vertex has its true shortest distance. If a shorter path existed, that path would cross from the settled region to the unsettled region and create a queue key no larger than its total length, contradicting the minimality of the popped key.

Every shortest path is exposed when its predecessor is settled, so relaxation eventually assigns the true distance to every reachable vertex. Therefore all printed distances are correct.

## Implementation

Distances use `long long` because path sums may exceed 32-bit range. Adjacency-list pairs store `(destination, weight)`, while priority-queue pairs store `(distance, vertex)`. Official input guarantees that every vertex is reachable from vertex 1, so no infinity sentinel is printed.

## Complexity

Using a binary heap, the time complexity is $O((n+m)\log n)$ and the space complexity is $O(n+m)$.

## Worked Example

With edges $1\to2$ of weight 5, $1\to3$ of weight 2, and $3\to2$ of weight 1, vertex 2 is first discovered at distance 5 and later improved to 3. The stale queue entry with distance 5 is ignored.
