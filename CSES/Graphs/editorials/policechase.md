# Police Chase

## Problem

- **Source:** [CSES 1695, Police Chase](https://cses.fi/problemset/task/1695/)
- **Code:** [`View accepted C++ solution (policechase.cpp)`](../policechase.cpp)
- **Constraints:** 2 <= n <= 500 and 1 <= m <= 1000.

An undirected graph represents streets. Remove as few streets as possible so that vertex $1$ can no longer reach vertex $n$. Print both the minimum number and one set of streets to remove.

This is a minimum edge cut between two fixed vertices.

## Idea

Assign capacity one to every street. Any set of removed streets that separates source and sink is an $s$-$t$ cut whose capacity equals its number of streets. By the max-flow min-cut theorem, the smallest such number equals the maximum flow value.

An undirected capacity-one street permits net flow in either direction, but at most one unit across the edge. The implementation stores two opposite residual arcs, both initially of capacity one, as a paired representation. Sending one unit from $a$ to $b$ changes their residual capacities from $(1,1)$ to $(0,2)$. The value above one in the reverse direction represents cancellation plus the unused opposite orientation; it does not allow two units of net flow simultaneously.

After maximum flow, run one residual traversal from the source. Let $S$ be the reached vertices and $T$ the unreached vertices. The sink lies in $T$, since otherwise another augmenting path would exist. Every original street with one endpoint in each side belongs to the cut. These are exactly the streets printed by the implementation.

## Algorithm

1. Store each undirected street as a paired pair of residual arcs, each initially capacity one. Also retain its original endpoints.
2. Run Dinic from vertex $1$ to vertex $n$ until the sink is unreachable in the residual graph.
3. BFS from vertex $1$ through every positive residual arc and mark the reachable side $S$.
4. Scan the original streets. Select a street exactly when its endpoints have different reachability marks.
5. Print all selected streets.

## Correctness

### Lemma 1

The flow computation finds a maximum feasible net flow through the undirected unit-capacity streets.

#### Proof

For each street, the paired residual capacities encode its net flow: sending in one direction decreases that direction and increases the opposite one, while a later reverse augmentation cancels the earlier net flow first. Thus absolute net flow across the street never exceeds one. Dinic preserves conservation and augments until no residual source-to-sink path remains. The usual residual-cut argument then proves the resulting flow is maximum. $\square$

### Lemma 2

Every street selected after the final residual BFS crosses a valid source-sink cut.

#### Proof

The residual BFS places vertex $1$ in $S$. Since Dinic has terminated, vertex $n$ is not residual-reachable and lies in $T$. A selected street has one endpoint in each set by definition. Removing every selected street leaves no graph edge crossing between $S$ and $T$, so no path can connect $1$ to $n$. $\square$

### Lemma 3

The number of selected streets equals the maximum-flow value.

#### Proof

For any street crossing from $S$ to $T$, its residual capacity in that direction is zero; otherwise the residual BFS would reach its endpoint in $T$. Under the paired undirected representation, this means one unit of net flow crosses from $S$ to $T$. No net flow crosses back from $T$ to $S$, because that would leave positive residual capacity from $S$ to $T$ through the opposite orientation. Summing conservation over vertices in $S$ shows that the flow value equals the number of crossing streets. $\square$

### Theorem

The algorithm prints a minimum-size set of streets whose removal disconnects vertex $1$ from vertex $n$.

#### Proof

Lemma 2 proves the printed set is a valid cut. Lemma 3 says its size equals the maximum-flow value. Every valid cut has capacity at least the maximum flow, so no smaller removal set exists. $\square$

## Implementation

Unlike an ordinary directed-edge `add`, this version initializes both members of an edge pair with capacity one. They still remain paired by `id ^ 1`, and the standard residual update correctly changes their net orientation.

The arrays `ea` and `eb` preserve each street once. Scanning these original records avoids printing both residual directions and preserves parallel streets as distinct removable edges.

The maximum-flow value itself is not accumulated because only the cut edges are requested; Dinic is run solely to saturation.

## Complexity

Dinic has the general bound $O(n^2m)$ here. The final residual BFS and street scan take $O(n+m)$. Auxiliary space is $O(n+m)$.

## Worked Example

Suppose streets are $1-2$, $2-4$, $1-3$, $3-4$, and $2-3$. Two edge-disjoint routes connect $1$ to $4$, so at least two streets must be removed. After max flow, one possible residual reachable set is $S=\{1\}$, making the crossing streets $1-2$ and $1-3$. Removing them isolates the source, and the printed cut has optimal size two.

A different maximum flow may produce a different reachable side and hence a different minimum cut. Any such cut is accepted.
