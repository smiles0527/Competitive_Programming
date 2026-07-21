# Labyrinth

## Problem

- **Source:** [CSES 1193: Labyrinth](https://cses.fi/problemset/task/1193/)
- **Code:** [`View accepted C++ solution (labyrinth.cpp)`](../labyrinth.cpp)
- **Constraints:** $1\le n,m\le1000$.

Find a route from `A` to `B` through non-wall cells, or report that none exists.

## Idea

Model every non-wall cell as a vertex and connect cells sharing a side. The result is an unweighted graph, so BFS finds a shortest route.

Storing a complete path for every queued cell would cause unnecessary copying. Instead, when a cell is first discovered, store only the direction used to enter it. These characters form a parent tree from which the route can be reconstructed backwards.

## Algorithm

1. Find `A` and `B` while reading the grid.
2. Run BFS from `A`. Mark each valid neighbor when it is enqueued and store the move used to enter it.
3. If `B` was not visited, print `NO`.
4. Otherwise, follow the stored moves backwards from `B` to `A`, reverse the resulting string, and print it.

## Correctness

### Lemma 1

Every visited cell is reachable from `A`, and its stored parent chain leads back to `A`.

#### Proof

The claim is true for `A`. Every other cell is marked while examining an already visited adjacent cell, and the stored character is exactly the move from that cell to the new one. Induction over discovery order proves the claim. $\square$

### Lemma 2

If `B` is reachable from `A`, BFS visits `B`.

#### Proof

Consider any route from `A` to `B`. Starting from `A`, whenever BFS visits one cell of the route, it examines and either discovers or has already discovered the next cell. Induction along the route reaches `B`. $\square$

### Theorem

The algorithm prints `NO` exactly when no route exists; otherwise, it prints a valid shortest route from `A` to `B`.

#### Proof

Lemma 2 proves the failure case. In the success case, Lemma 1 proves that reversing the reconstructed parent chain gives a valid route. Since BFS discovers cells in nondecreasing distance, the first parent assigned to `B` belongs to a shortest route. $\square$

## Implementation

The arrays `dr`, `dc`, and `stepdir = "DURL"` use matching indices. Cells are marked when enqueued so that each cell receives one fixed parent. During reconstruction, `D` moves one row upward to the parent, `U` downward, `R` left, and `L` right.

## Complexity

The time complexity is $O(nm)$ and the auxiliary space is $O(nm)$.

## Worked Example

Suppose BFS enters `B` using moves `R`, `R`, `D`. Reconstruction reads the destination first, producing `DRR`; reversing it gives the forward route `RRD`.
