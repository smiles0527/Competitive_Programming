# Building Teams

## Problem

- **Source:** [CSES 1668: Building Teams](https://cses.fi/problemset/task/1668/)
- **Code:** [`View accepted C++ solution (buildingteams.cpp)`](./buildingteams.cpp)
- **Constraints:** $1\le n\le100000$ and $1\le m\le200000$.

Assign every student to one of two teams so that no friendship edge connects two students on the same team, or report failure.

## Idea

The problem is bipartite graph coloring. Choose the color of an arbitrary vertex in each connected component. Every neighbor is then forced to have the other color. Vertices at even graph distance from the root receive the first color, while vertices at odd distance receive the second.

If an edge connects two vertices with the same color, the two BFS paths from the component root to its endpoints, together with that edge, contain an odd cycle. Therefore a two-coloring is impossible. Otherwise, if the process finishes without a conflict, no adjacent vertices share a color and the assignment is valid.

Disconnected components can be colored independently, so BFS must be launched from every uncolored vertex.

## Algorithm

For every uncolored vertex, assign color 1 and run BFS. Assign each uncolored neighbor color `3 - currentColor`. If an edge has endpoints with the same existing color, print `IMPOSSIBLE`. If every component succeeds, print all colors.

## Correctness

Whenever the algorithm colors a new vertex, it uses the only color different from that of the neighbor which discovered it, so the corresponding BFS-tree edge is colored correctly. If equal colors are found on the endpoints of an edge, parity of the two BFS paths produces an odd cycle, so no two-team assignment exists.

If no conflict occurs, every edge is examined from an endpoint. Its other endpoint is either assigned the complementary color or verified to already have it. Therefore every friendship edge joins different teams, and the printed assignment is valid.

## Implementation

Color zero denotes an unvisited vertex; team labels are 1 and 2. The outer loop is required for isolated vertices and disconnected components. The conflict branch returns immediately after printing `IMPOSSIBLE`.

## Complexity

Every vertex enters the queue once and every undirected edge is examined twice. The time complexity is $O(n+m)$ and the space complexity is $O(n+m)$.

## Worked Example

A path $1-2-3-4$ receives alternating colors $1,2,1,2$. Adding edge $4-1$ remains valid, while adding edge $1-3$ connects equal-colored vertices and creates an odd cycle of length three.
