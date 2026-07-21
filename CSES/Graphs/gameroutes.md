# Game Routes

## Problem

- **Source:** [CSES 1681: Game Routes](https://cses.fi/problemset/task/1681/)
- **Code:** [`View accepted C++ solution (gameroutes.cpp)`](./gameroutes.cpp)
- **Constraints:** $1\le n\le100000$ and $1\le m\le200000$; the graph is acyclic.

Count directed routes from vertex 1 to vertex $n$ modulo $10^9+7$.

## Idea

In a topological ordering, every edge goes from an earlier vertex to a later vertex. Let `dp[v]` be the number of routes from vertex 1 to vertex $v$. The source has one empty route. Every route reaching $u$ through edge $v\to u$ is created uniquely by taking a route to $v$ and appending that edge:

$$
dp[u]\mathrel{+}=dp[v].
$$

Kahn's algorithm can generate a topological order and propagate the DP values at the same time.

## Algorithm

1. Compute indegrees, enqueue all zero-indegree vertices, and set `dp[1] = 1`.
2. Process vertices in Kahn order. For each edge $v\to u$, add `dp[v]` to `dp[u]`, decrease `indeg[u]`, and enqueue $u$ if its indegree becomes zero.
3. Print `dp[n]` modulo $10^9+7$.

## Correctness

When vertex $v$ leaves the queue, every predecessor has already been processed because all incoming edges of $v$ have been removed. Therefore `dp[v]` already contains the contribution from every possible final incoming edge and equals the total number of routes from vertex 1 to $v$.

Propagation through each outgoing edge appends that edge to every route exactly once. Induction over the topological order proves every DP value correct, including `dp[n]`.

## Implementation

All graph vertices participate in Kahn's algorithm, including vertices unreachable from the source. Their DP values remain zero and contribute nothing. Counts are reduced modulo $10^9+7$ after every addition.

## Complexity

The time complexity is $O(n+m)$ and the space complexity is $O(n+m)$.

## Worked Example

With edges $1\to2$, $1\to3$, $2\to4$, and $3\to4$, vertices 2 and 3 receive one route each. Vertex 4 receives their sum, so there are two routes from 1 to 4.
