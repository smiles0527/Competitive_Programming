# Road Construction

## Problem

- **Source:** [CSES 1676: Road Construction](https://cses.fi/problemset/task/1676/)
- **Code:** [`View accepted C++ solution (roadconstruction.cpp)`](./roadconstruction.cpp)
- **Constraints:** $1\le n\le100000$ and $1\le m\le200000$.

After each undirected road is constructed, print the number of connected components and the size of the largest component.

## Idea

Because edges are added but never removed, connected components can only merge. A disjoint-set union structure tracks each component by its root and stores its size.

Initially there are $n$ singleton components and the maximum size is 1. If a road joins vertices with the same root, nothing changes. Otherwise, merging the roots decreases the component count by one and creates a component whose size is the sum of the two old sizes. No other component is affected.

## Algorithm

Initialize DSU parent and size arrays. For each road, find the roots of its endpoints. If they differ, attach the smaller component to the larger, update the new root size, decrement the component count, and update the maximum size. Print the two maintained values after every road.

## Correctness

The DSU invariant is that two vertices have the same root exactly when the roads processed so far connect them. A road inside one root leaves the component partition unchanged. A road between two roots joins every vertex in those two components and no others, so one union, one component-count decrement, and one size addition describe the graph change exactly.

Induction over the inserted roads proves that the component count and all root sizes remain correct. Updating the maximum after every successful merge therefore gives the correct largest component size.

## Implementation

Both roots are recomputed before comparison. The maximum size changes only after a successful union. A redundant road still produces an output line with unchanged values.

## Complexity

With union by size and path halving, the total time is $O((n+m)\alpha(n))$. The auxiliary space is $O(n)$.

## Worked Example

Starting with four isolated cities, adding roads $(1,2)$, $(3,4)$, and $(2,3)$ changes `(components, maximum size)` from $(3,2)$ to $(2,2)$ and finally to $(1,4)$.
