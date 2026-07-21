# Building Roads

## Problem

- **Source:** [CSES 1666: Building Roads](https://cses.fi/problemset/task/1666/)
- **Code:** [`View accepted C++ solution (buildingroads.cpp)`](./buildingroads.cpp)
- **Constraints:** $1\le n\le100000$ and $1\le m\le200000$.

Add the minimum number of undirected roads needed to make all cities connected, and print those roads.

## Idea

Suppose the current graph has $k$ connected components. Every new road can unite only two components, reducing the number of components by at most one. Hence at least $k-1$ roads are necessary.

Choose one representative from each component during DFS. Connecting the representatives into a chain uses exactly $k-1$ roads and makes every consecutive pair of components connected. By transitivity, all components become connected, attaining the lower bound.

## Algorithm

Iterate over all vertices. Whenever an unvisited vertex is found, record it as a component representative and traverse its component. Print one fewer than the number of representatives, then connect each representative to its immediate predecessor.

## Correctness

DFS from a representative visits exactly its connected component. Thus the recorded vertices represent distinct components, and every component receives exactly one representative.

Every added road connects two consecutive represented components. By induction, after adding the first $i$ roads, the first $i+1$ components form one connected component. Therefore all $k$ components are connected after $k-1$ roads. Since every valid solution needs at least $k-1$ roads, the construction is optimal.

## Implementation

Representatives are recorded before DFS. The traversal uses an explicit stack, and vertices are marked immediately when pushed to avoid duplicate entries. The output chain uses `rep[i-1]` and `rep[i]`, so component sizes are unnecessary.

## Complexity

The traversal takes $O(n+m)$ time. The adjacency list, visited array, representatives, and explicit stack use $O(n+m)$ space.

## Worked Example

If the component representatives are 1, 4, and 7, print roads $(1,4)$ and $(4,7)$. Two roads are both sufficient and necessary for three components.
