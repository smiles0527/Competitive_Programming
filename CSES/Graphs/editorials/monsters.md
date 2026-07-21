# Monsters

## Problem

- **Source:** [CSES 1194: Monsters](https://cses.fi/problemset/task/1194/)
- **Code:** [`View accepted C++ solution (monsters.cpp)`](../monsters.cpp)
- **Constraints:** $1\le n,m\le1000$.

Find a route from `A` to any boundary cell such that the player never occupies a cell at the same time as a monster, or print `NO`.

## Idea

Only arrival times matter. Let `md[v]` be the earliest time any monster can reach cell $v$. A multi-source BFS from all monsters computes these values simultaneously.

Then run BFS from `A`. A transition reaching $v$ at time $t$ is safe exactly when

$$
t<md[v].
$$

Equality is unsafe because a monster may occupy the cell at the same moment. Parent directions reconstruct the route once a boundary cell is reached.

## Algorithm

1. Initialize all monster cells as distance-zero sources and run multi-source BFS.
2. Run a second BFS from `A`, allowing an unvisited neighbor only when the player's arrival time is strictly smaller than its monster distance.
3. Stop at the first boundary cell, reconstruct its parent path, and print it.
4. If no safe boundary cell is reached, print `NO`.

## Correctness

### Lemma 1

After the first BFS, `md[v]` is the earliest time any monster can reach every non-wall cell $v$.

#### Proof

All monster positions are distance-zero sources. Multi-source BFS processes the unweighted grid in increasing distance from this source set, so the first assigned distance is the shortest distance from any monster. $\square$

### Lemma 2

Every cell visited by the player BFS has a safe route from `A`.

#### Proof

The start is admitted only when no monster occupies it at time zero. Every later transition extends a safe route and requires the new player time $t$ to satisfy $t<md[v]$. By Lemma 1, no monster can reach $v$ by time $t$. Induction proves safety. $\square$

### Lemma 3

If a safe escape route exists, the player BFS reaches a boundary cell.

#### Proof

At time $t$ on any safe route, the current cell satisfies $t<md[v]$. Thus every transition of that route is permitted by the player BFS. Induction along the route reaches its boundary endpoint. $\square$

### Theorem

The algorithm prints a safe escape route if and only if one exists.

#### Proof

A reported boundary route is safe by Lemma 2. If none is found, Lemma 3 rules out every safe escape route. $\square$

## Implementation

`INT_MAX` denotes an unreached cell in both distance arrays. The check `pd[cur] + 1 >= md[next]` rejects both later arrivals and ties. Testing the boundary when a player state is dequeued also handles `A` already being on the boundary, producing an empty route.

## Complexity

Both BFS passes take $O(nm)$ time. The auxiliary space is $O(nm)$.

## Worked Example

If the player and the nearest monster both reach a corridor cell at time 3, that cell is rejected. A difference of zero is not a narrow escape; it is a collision, which is why the comparison must be strict.
