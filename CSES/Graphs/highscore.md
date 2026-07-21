# High Score

## Problem

- **Source:** [CSES 1673: High Score](https://cses.fi/problemset/task/1673/)
- **Code:** [`View accepted C++ solution (highscore.cpp)`](./highscore.cpp)
- **Constraints:** $1\le n\le2500$, $1\le m\le5000$, and $-10^9\le w\le10^9$.

Compute the largest possible score of a route from vertex 1 to vertex $n$, or print `-1` if the score can be made arbitrarily large.

## Idea

Negate every edge score. Maximizing the original score becomes minimizing negated cost, and a positive-score cycle becomes a negative cycle. Such a cycle makes the answer unbounded only when it is reachable from vertex 1 and can also reach vertex $n$.

Run $n-1$ Bellman-Ford passes from vertex 1 to obtain finite shortest values when no relevant negative cycle intervenes. Then continue relaxing and propagate an `inf` mark. A vertex is marked if it can still be improved or is reachable from an already marked vertex. After at most $n$ additional passes, every vertex reachable from a source-reachable negative cycle is marked.

## Algorithm

1. Negate all edge scores and initialize only the source distance to zero.
2. Relax all edges $n-1$ times.
3. Perform $n$ additional passes which relax edges and propagate unboundedness marks.
4. Print `-1` if the target is marked; otherwise print the negation of its shortest distance.

## Correctness

Bellman-Ford computes the minimum negated cost of every source-reachable path restricted to at most $n-1$ edges. A later improvement is possible only because a source-reachable negative cycle can influence that vertex. Propagating marks along outgoing edges identifies exactly the vertices reachable from such cycles.

The target is marked exactly when a positive original cycle can be inserted into a route from source to target arbitrarily many times, making the score unbounded. Otherwise, an optimal route can be chosen simple after removing nonpositive cycles, so its negated cost equals the stabilized Bellman-Ford distance. Negating it gives the maximum score.

## Implementation

Relaxations originate only from finite distances, enforcing reachability from vertex 1. The additional $n$ passes both discover and propagate affected vertices. Edge scores are negated while being read.

## Complexity

The time complexity is $O(nm)$ and the space complexity is $O(n+m)$.

## Worked Example

If a cycle reachable from vertex 1 has original total score 4 and a path continues from it to the target, repeating the cycle adds 4 each time. Negated Bellman-Ford keeps improving and eventually marks the target, producing `-1`.
