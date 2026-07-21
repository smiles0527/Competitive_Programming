# Cycle Finding

## Problem

- **Source:** [CSES 1197: Cycle Finding](https://cses.fi/problemset/task/1197/)
- **Code:** [`View accepted C++ solution (cyclefinding.cpp)`](../cyclefinding.cpp)
- **Constraints:** $1\le n\le2500$, $1\le m\le5000$, and $-10^9\le w\le10^9$.

Find and print any directed negative-weight cycle, or report that none exists.

## Idea

Bellman-Ford relaxation detects negative cycles. To search every connected region without creating an explicit super-source, initialize every distance to zero. This is equivalent to adding a new source with a zero-cost edge to every vertex.

Without a negative cycle, every shortest simple path uses at most $n-1$ edges, so no relaxation occurs on the $n$th full pass. If a relaxation does occur, the updated vertex is influenced by a negative cycle in the predecessor graph.

Parent pointers record which edge caused every improvement. Following parents $n$ times from a vertex updated on the final pass guarantees entry into the cycle, discarding any path leading toward it.

## Algorithm

1. Initialize every distance to zero and every parent to $-1$.
2. Relax all edges for exactly $n$ rounds, remembering the last updated vertex.
3. If no vertex is updated on the final round, print `NO`.
4. Otherwise, follow parents $n$ times from the updated vertex.
5. Continue following parents until the starting cycle vertex repeats, then reverse and print the recorded cycle.

## Correctness

If no relaxation occurs on the final round, Bellman-Ford's path-length invariant shows that every distance has stabilized and no negative cycle is reachable. Since every vertex is reachable from the implicit super-source, no negative cycle exists anywhere in the graph.

If a final-round relaxation occurs, Bellman-Ford theory guarantees that a negative cycle influences the predecessor chain. After $n$ parent steps, the current vertex lies inside a repeated portion of a chain over only $n$ vertices. Following parents until that vertex repeats records a directed cycle responsible for indefinite distance decreases, so its total weight is negative.

## Implementation

Zero initialization is intentional and differs from single-source Bellman-Ford. The repeated start vertex appears at both ends of the output cycle. Reversing the parent sequence converts predecessor direction into edge direction. The `NO` branch returns immediately before any parent is accessed.

## Complexity

The time complexity is $O(nm)$ and the space complexity is $O(n+m)$.

## Worked Example

For a cycle $1\to2\to3\to1$ with total weight $-1$, every traversal of the cycle can lower a distance again. Some vertex remains updated on the $n$th pass, and following its parent chain enters and then repeats the negative cycle.
