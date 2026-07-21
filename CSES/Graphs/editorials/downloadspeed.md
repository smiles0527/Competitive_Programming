# Download Speed

## Problem

- **Source:** [CSES 1694, Download Speed](https://cses.fi/problemset/task/1694/)
- **Code:** [`View accepted C++ solution (downloadspeed.cpp)`](../downloadspeed.cpp)
- **Constraints:** 2 <= n <= 500, 1 <= m <= 1000, and 1 <= c <= 10^9.

A directed network has a nonnegative capacity on every connection. Determine the maximum total rate that can be sent from computer $1$ to computer $n$ without exceeding any edge capacity.

Flow may split across several routes and recombine later. Choosing one widest path is therefore insufficient.

## Idea

A feasible flow assigns each directed edge $u\to v$ a value between zero and its capacity. Every internal vertex must receive and send the same total amount. The objective is the net amount leaving the source.

An augmenting-path algorithm starts with zero flow and repeatedly sends more through the residual graph. A forward residual capacity is unused original capacity. A reverse residual capacity represents flow that can be cancelled and rerouted. This reverse operation is what lets a locally chosen earlier path be corrected later.

Dinic's algorithm accelerates augmentation in phases. BFS constructs a level graph containing only residual edges that advance one level away from the source. DFS sends a blocking flow through this acyclic layered graph. Once no more source-to-sink flow fits in the current levels, a new BFS is required.

The persistent cursor `it_[v]` remembers which outgoing residual edges have already failed during a phase. Since residual capacities only decrease on forward level edges during that blocking-flow search, reconsidering those failed edges cannot help.

## Algorithm

1. For each input edge, create a forward residual edge with its capacity and a reverse residual edge with capacity zero.
2. While BFS can reach the sink through positive residual capacity:
   - assign every reachable vertex its shortest residual distance from the source;
   - reset all current-edge cursors;
   - repeatedly run DFS from source to sink through edges whose level increases by one;
   - add every returned amount to the total flow.
3. When BFS can no longer reach the sink, print the accumulated flow.

## Correctness

### Lemma 1

Every DFS augmentation preserves capacity constraints and flow conservation.

#### Proof

DFS sends an amount no larger than the residual capacity of every edge on its source-to-sink path. Subtracting it from each forward residual capacity and adding it to the paired reverse capacity updates the represented flow without exceeding original capacity. At every internal path vertex the same amount enters and leaves, so conservation is preserved. $\square$

### Lemma 2

Within one BFS phase, repeated DFS calls produce a blocking flow in the level graph.

#### Proof

DFS explores only edges from level $d$ to $d+1$. A failed edge or exhausted edge is passed permanently by its source cursor. When DFS can no longer send flow from the source, every source-to-sink path in the level graph contains an exhausted edge; otherwise DFS would discover a positive-capacity continuation along such a path. Thus no additional flow can cross the current level graph. $\square$

### Lemma 3

When the final BFS cannot reach the sink, the current flow is maximum.

#### Proof

Let $S$ be the vertices reachable from the source in the final residual graph and let $T$ contain the rest, including the sink. No positive residual edge crosses from $S$ to $T$. Therefore every original forward edge across the cut is saturated, and every original edge from $T$ to $S$ carries zero net flow. The current flow value equals the capacity of this cut. No feasible flow can exceed any source-sink cut capacity, so the current flow is maximum. $\square$

### Theorem

The algorithm prints the maximum possible download speed.

#### Proof

Lemma 1 keeps the accumulated flow feasible. Dinic phases continue while an augmenting path exists, and terminate only when the sink is unreachable in the residual graph. Lemma 3 then proves that the feasible flow has maximum value. $\square$

## Implementation

Residual edges are stored in consecutive pairs. If `id` is one direction, `id ^ 1` is its reverse. Updating both capacities maintains the residual representation.

`bfs` assigns `level_`; `dfs` accepts at most `pushed` units and returns after one successful augmentation. The caller repeats it until the current level graph is blocked.

`INF = 1e18` is an upper bound for one DFS request, while the actual returned value is limited by edge residual capacities.

## Complexity

For a general directed graph, Dinic's algorithm runs in $O(n^2m)$ time. The residual edge array and adjacency lists use $O(n+m)$ space. With the problem's small vertex bound, this is suitable, while capacities require `long long`.

## Worked Example

Suppose capacities are $1\to2:5$, $1\to3:4$, $2\to4:3$, $3\to4:4$, and $2\to3:2$. One blocking-flow phase may send 3 along $1,2,4$ and 4 along $1,3,4$, for total 7. The sink's incoming cut has capacity $3+4=7$, so no later phase can improve it.

The unused capacity on $1\to2$ does not imply more total flow is possible: every continuation to the sink is saturated. The residual reachability cut formalizes this bottleneck.
