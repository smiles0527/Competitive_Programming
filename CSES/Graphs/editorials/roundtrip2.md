# Round Trip II

## Problem

- **Source:** [CSES 1678: Round Trip II](https://cses.fi/problemset/task/1678/)
- **Code:** [`View accepted C++ solution (roundtrip2.cpp)`](../roundtrip2.cpp)
- **Constraints:** $1\le n\le100000$ and $1\le m\le200000$.

Find and output a directed cycle, or report that the graph is acyclic.

## Idea

During depth-first search, each vertex has one of three colors: white before discovery, gray while its DFS frame is open, and black after all outgoing edges have been processed. An edge from the current vertex `ce` to a gray vertex `cs` is a back edge to an ancestor on the current DFS path, so it closes a directed cycle.

An edge to a black vertex does not prove a cycle because that vertex's DFS path has already finished. When a gray endpoint is found, parent pointers trace the tree path from the ancestor to the current vertex.

The implementation emulates DFS with explicit frames `(vertex, next edge index)` to avoid call-stack failure on a deep graph.

## Algorithm

Start iterative DFS from every white vertex. Color a vertex gray when its frame is pushed and black after all outgoing edges have been processed. If an edge `ce -> cs` reaches a gray vertex, stop, follow parents from `ce` to `cs`, reverse that path, and append `cs` again to close the cycle.

## Correctness

The gray vertices are exactly the ancestor chain represented by the active DFS frames. If edge `ce -> cs` reaches a gray vertex, the parent edges form a directed path from `cs` to `ce`; adding the discovered edge produces a directed cycle. Reversing the parent sequence and repeating `cs` prints it in forward direction.

If no edge ever reaches a gray vertex, no directed cycle exists. Any directed cycle encountered by DFS must contain an edge to an earlier vertex whose frame is still active, which would be a gray endpoint. Therefore the algorithm reports impossibility exactly for acyclic graphs.

## Implementation

The next-edge index is stored in the top frame so exploration resumes at the correct edge after returning from a child. The parent chain is reversed and the start vertex is appended to satisfy the closed-cycle output format.

## Complexity

Every vertex is pushed once and every directed edge is examined once. The time complexity is $O(n+m)$ and the space complexity is $O(n+m)$.

## Worked Example

With edges $1\to2$, $2\to3$, and $3\to1$, all three vertices are gray when edge $3\to1$ is examined. Following parents reconstructs the cycle `1 2 3 1`.
