# Teleporters Path

## Problem

- **Source:** [CSES 1693: Teleporters Path](https://cses.fi/problemset/task/1693/)
- **Code:** [`View accepted C++ solution (teleporters.cpp)`](./teleporters.cpp)
- **Constraints:** $2\le n\le100000$ and $1\le m\le200000$.

Find a directed trail from vertex 1 to vertex $n$ that uses every edge exactly once, or print `IMPOSSIBLE`.

## Idea

This is a directed Eulerian trail with fixed endpoints. Every internal vertex must pair arrivals with departures, while the start has one unmatched departure and the target has one unmatched arrival:

$$
out(1)=in(1)+1,\qquad in(n)=out(n)+1,
$$

and $in(v)=out(v)$ for every other vertex.

Degree balances alone do not exclude disconnected edge sets. Hierholzer's algorithm constructs the trail from vertex 1, and the final requirement that its vertex sequence has length $m+1$ confirms that every edge was used.

## Algorithm

1. Build directed adjacency lists and compute indegrees and outdegrees.
2. Check the required degree differences for vertices 1, $n$, and all internal vertices.
3. Run iterative Hierholzer from vertex 1, consuming each outgoing adjacency entry with a persistent cursor.
4. Reverse the backtracking sequence and require its length to be $m+1$, its first vertex to be 1, and its last vertex to be $n$.

## Correctness

### Lemma 1

Every input edge is selected at most once.

#### Proof

For each vertex, its cursor advances immediately when an outgoing adjacency entry is selected and never decreases. Thus every entry, including each parallel edge, is used at most once. $\square$

### Lemma 2

If the degree conditions hold, reversing Hierholzer's backtracking sequence gives a directed trail from 1 to $n$ using every selected edge once.

#### Proof

Each push follows a directed edge, while appending occurs only after all outgoing edges are exhausted. Reversal therefore splices completed subtrails in forward direction. Balanced internal vertices pair arrivals and departures; vertex 1 has the unmatched departure and vertex $n$ the unmatched arrival. Lemma 1 prevents repetition. $\square$

### Theorem

The algorithm outputs a valid teleporters path if and only if one exists.

#### Proof

Every valid trail must satisfy the checked degree conditions. If they hold, Lemma 2 constructs a trail through all edges reachable in the traversal. A sequence of $m+1$ vertices uses exactly $m$ edges, so the length check proves that every input edge was included. A shorter sequence exposes an unreachable edge set, which no trail starting at vertex 1 can include. $\square$

## Implementation

Explicit edge identifiers are unnecessary because each directed adjacency entry is one distinct edge and its source cursor consumes it once. Parallel edges remain separate entries. The endpoint and $m+1$ checks are both retained because local degree balances do not guarantee global coverage.

## Complexity

The time complexity is $O(n+m)$ and the auxiliary space is $O(n+m)$.

## Worked Example

For edges $1\to2$, $2\to1$, and $1\to3$, the degree differences match start 1 and target 3. Hierholzer backtracks as `3,1,2,1`; reversing produces `1 2 1 3`, which uses every edge exactly once.
