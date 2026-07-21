# Mail Delivery

## Problem

- **Source:** [CSES 1691: Mail Delivery](https://cses.fi/problemset/task/1691/)
- **Code:** [`View accepted C++ solution (maildelivery.cpp)`](../maildelivery.cpp)
- **Constraints:** $2\le n\le100000$ and $1\le m\le200000$.

Starting from vertex 1, find a closed walk using every edge of an undirected multigraph exactly once, or print `IMPOSSIBLE`.

## Idea

The required walk is an Eulerian circuit. Every used arrival at a vertex must be paired with a departure, so every vertex must have even degree. The nonzero-degree vertices must also belong to the component of vertex 1.

Hierholzer's algorithm maintains the current trail on a stack. It consumes an unused incident edge whenever possible. When the top vertex has no unused edge, that vertex is appended to the circuit during backtracking. This splices completed closed subtrails into one Eulerian circuit.

## Algorithm

1. Store both adjacency entries of each edge with one shared edge identifier.
2. Reject the graph if any degree is odd.
3. Run iterative Hierholzer from vertex 1, using a persistent adjacency cursor for every vertex.
4. Require the resulting circuit to contain exactly $m+1$ vertices, reverse it, and print it.

## Correctness

### Lemma 1

Every input edge is traversed at most once.

#### Proof

Both adjacency entries share an identifier. The identifier is marked before traversal, so neither entry can select that edge again. $\square$

### Lemma 2

After reversal, consecutive circuit vertices are joined by distinct selected edges.

#### Proof

Each stack push follows one selected edge. Vertices are appended only during backtracking, so their order is the reverse of the completed trail order. Reversal restores the edge directions along the undirected walk, and Lemma 1 gives distinctness. $\square$

### Theorem

The algorithm outputs an Eulerian circuit exactly when one exists.

#### Proof

An odd degree makes a closed Eulerian walk impossible. With even degrees, Hierholzer closes every reachable trail and Lemma 2 gives a closed walk using every edge reachable from vertex 1 once. Its vertex sequence has length $m+1$ exactly when all $m$ edges were included. If it is shorter, some nonzero-degree component is disconnected from vertex 1, so no required circuit exists. $\square$

## Implementation

Unique edge identifiers are necessary because parallel streets are distinct. The cursor `it_[v]` prevents rescanning discarded adjacency entries. Marking an edge identifier consumes both of its undirected representations.

## Complexity

The time complexity is $O(n+m)$ and the auxiliary space is $O(n+m)$.

## Worked Example

| Action | Stack | Backtracking sequence |
|---|---|---|
| start | `1` | empty |
| use $1-2$ | `1,2` | empty |
| use $2-3$ | `1,2,3` | empty |
| use $3-1$ | `1,2,3,1` | empty |
| backtrack fully | empty | `1,3,2,1` |

Reversing gives the Eulerian circuit `1 2 3 1`.
