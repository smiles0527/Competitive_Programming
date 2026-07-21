# Road Reparation

## Problem

- **Source:** [CSES 1675: Road Reparation](https://cses.fi/problemset/task/1675/)
- **Code:** [`View accepted C++ solution (roadreparation.cpp)`](../roadreparation.cpp)
- **Constraints:** $1\le n\le100000$, $1\le m\le200000$, and $1\le w\le10^9$.

Choose roads of minimum total cost so that all cities become connected, or report that this is impossible.

## Idea

This is a minimum spanning tree problem. Kruskal's algorithm sorts edges by nondecreasing weight and accepts an edge exactly when it joins two different components.

The cut property justifies this choice. When an accepted edge joins components $A$ and $B$, consider the cut separating one current component from the rest. Because edges are processed by weight, no unprocessed crossing edge is lighter. Therefore some minimum spanning tree contains the accepted edge; if necessary, add it to an MST and remove another edge from the resulting cycle.

Disjoint-set union stores the components formed by accepted edges.

## Algorithm

Sort all edges by cost. Initialize every vertex as a separate DSU component. For each edge, add its cost and unite its endpoints only when they currently belong to different components. A spanning tree exists exactly when $n-1$ edges are accepted.

## Correctness

DSU rejects exactly the edges that would create a cycle, so the accepted edges always form a forest. By the cut-property exchange argument, after each acceptance there exists an MST containing the current forest. If $n-1$ edges are accepted, this forest is connected and therefore is itself an MST.

If fewer than $n-1$ edges are accepted after every input edge has been considered, at least two graph components have no connecting edge. No spanning tree exists, so reporting impossibility is correct.

## Implementation

Union by size and path halving make DSU operations nearly constant time. The total cost uses `long long`. The number of accepted edges provides the final connectivity test.

## Complexity

Sorting takes $O(m\log m)$ time, and all DSU operations take $O(m\alpha(n))$ total. The stored edge list and DSU arrays use $O(n+m)$ space.

## Worked Example

For a triangle with edge costs 2, 3, and 10, Kruskal accepts costs 2 and 3. The final edge joins already connected vertices and is discarded, giving the optimal cost 5.
