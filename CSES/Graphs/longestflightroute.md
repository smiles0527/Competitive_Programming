# Longest Flight Route

## Problem

- **Source:** [CSES 1680: Longest Flight Route](https://cses.fi/problemset/task/1680/)
- **Code:** [`View accepted C++ solution (longestflightroute.cpp)`](./longestflightroute.cpp)
- **Constraints:** $2\le n\le100000$ and $1\le m\le200000$; the graph is acyclic.

Find a route from vertex 1 to vertex $n$ containing the maximum number of vertices, or report that no such route exists.

## Idea

Let `dp[v]` be the maximum number of vertices on a path from $v$ to $n$. The target has `dp[n] = 1`. In reverse topological order, choose among the outgoing neighbors $u$ that can reach $n$:

$$
dp[v]=1+\max_{v\to u}dp[u].
$$

Store the neighbor attaining the maximum. Starting from vertex 1 and following these successors reconstructs a longest route.

The implementation finds a topological order using Kahn's algorithm over the whole DAG and processes it in reverse. States unable to reach $n$ remain equal to `INT_MIN`.

## Algorithm

Find a topological ordering. Initialize every DP state as unreachable except `dp[n] = 1`. Process the order in reverse, relax every reachable outgoing neighbor, and store the best successor. If vertex 1 remains unreachable, print `IMPOSSIBLE`; otherwise follow successors from vertex 1 to $n$.

## Correctness

In reverse topological order, every outgoing neighbor's final state is known before the current vertex is processed. Every path from $v$ to $n$ starts with one outgoing edge, so the recurrence considers all such paths and chooses the longest. Induction over reverse topological order proves every reachable state optimal.

Each stored successor attains the chosen transition, so following successors decreases the remaining path length by one and eventually reaches $n$. The reconstructed route contains `dp[1]` vertices and is therefore longest.

## Implementation

`dp[n] = 1` counts vertices rather than edges. `INT_MIN` marks inability to reach the target. The successor of vertex $n$ remains `-1`, naturally ending reconstruction. The impossible branch returns before reading an invalid successor.

## Complexity

Topological sorting and dynamic programming each take $O(n+m)$ time. The space complexity is $O(n+m)$.

## Worked Example

With edges $1\to2$, $1\to3$, $2\to4$, $3\to5$, and $5\to4$, target 4 gives path lengths 1 at vertex 4, 2 at vertices 2 and 5, 3 at vertex 3, and 4 at vertex 1. Reconstruction returns $1,3,5,4$.
