# Flight Routes Check

## Problem

- **Source:** [CSES 1682: Flight Routes Check](https://cses.fi/problemset/task/1682/)
- **Code:** [`View accepted C++ solution (flightroutescheck.cpp)`](./flightroutescheck.cpp)
- **Constraints:** $1\le n\le100000$ and $1\le m\le200000$.

Check whether every city can reach every other city. If not, print an ordered pair $(a,b)$ for which no route exists from $a$ to $b$.

## Idea

A directed graph is strongly connected exactly when one chosen root reaches every other vertex and every other vertex reaches that root.

Run BFS from vertex 1 in the original graph to test the first condition. The second condition is equivalent to vertex 1 reaching every vertex in the reversed graph. If original BFS misses $v$, then $(1,v)$ is a certificate. If reversed BFS misses $v$, then the original graph has no route from $v$ to 1, so $(v,1)$ is a certificate.

If both checks pass, every route $a\to b$ can be formed by concatenating $a\to1$ and $1\to b$.

## Algorithm

Run BFS from vertex 1 in the original graph and report the first unreachable vertex as `(1,v)`. Then run BFS from vertex 1 in the reversed graph and report the first unreachable vertex as `(v,1)`. Print `YES` if both searches reach every vertex.

## Correctness

An original-graph failure directly proves that the printed pair $(1,v)$ is unreachable. A reversed-graph failure from 1 to $v$ means exactly that the original graph has no path from $v$ to 1, validating pair $(v,1)$.

If both searches succeed, every city is reachable from 1 and can reach 1. Hence every ordered pair is connected through vertex 1, so the graph is strongly connected.

## Implementation

The BFS helper clears the shared visitation array before every run. Reverse edges are built together with original edges. The certificate orientation intentionally differs between the two failure cases, and each failure returns immediately after printing.

## Complexity

Two BFS runs take $O(n+m)$ time. Both adjacency lists and traversal storage require $O(n+m)$ space.

## Worked Example

Suppose vertex 1 reaches vertex 2, but vertex 2 cannot return to vertex 1. Original BFS reaches 2. In the reversed graph, vertex 1 cannot reach 2, so the algorithm prints `2 1`, a genuinely unreachable ordered pair.
