# School Dance

## Problem

- **Source:** [CSES 1696, School Dance](https://cses.fi/problemset/task/1696/)
- **Code:** [`View accepted C++ solution (schooldance.cpp)`](../schooldance.cpp)
- **Constraints:** 1 <= n,m <= 500 and 1 <= k <= 1000.

There are $n$ boys, $m$ girls, and $k$ acceptable boy-girl pairs. Select as many pairs as possible so that each student appears in at most one selected pair. Print the maximum number and the selected pairs.

This is maximum matching in a bipartite graph.

## Idea

Directly choosing an arbitrary available partner can block a larger matching. For example, if one boy can dance with either of two girls while another can dance only with the first, matching the flexible boy to the first girl loses one pair. A correct algorithm must be able to reroute earlier choices.

Build a flow network:

- source $S$ connects to every boy with capacity one;
- every acceptable pair creates a boy-to-girl edge of capacity one;
- every girl connects to sink $T$ with capacity one.

Any integral unit of flow follows $S\to$ boy $\to$ girl $\to T$ and represents one pair. Source and sink incident capacities ensure no student participates twice. Conversely, every matching sends one unit along the corresponding three-edge path for each pair.

All capacities are integral, so Dinic returns an integral maximum flow. A boy-to-girl edge is matched exactly when it is saturated after the computation.

## Algorithm

1. Number boys as vertices $1$ through $n$ and girls as $n+1$ through $n+m$.
2. Add source-to-boy and girl-to-sink edges of capacity one.
3. Add one capacity-one edge for each acceptable pair, remembering its forward residual-edge identifier.
4. Run Dinic to compute maximum flow from $S$ to $T$.
5. Print the flow value.
6. For every remembered pair edge, print its boy and girl if its forward residual capacity is zero.

## Correctness

### Lemma 1

Every integral flow of value $F$ in the constructed network defines a matching of size $F$.

#### Proof

Every source-to-sink flow path has the form source, boy, girl, sink. The capacity-one source edge allows at most one unit through each boy, and the capacity-one sink edge allows at most one unit through each girl. Hence the saturated boy-girl edges form pairwise student-disjoint pairs. Flow conservation makes their count equal the total flow value $F$. $\square$

### Lemma 2

Every matching of size $M$ defines a feasible flow of value $M$.

#### Proof

For each matched pair, send one unit from the source to its boy, across the acceptable-pair edge, and from its girl to the sink. Since no student appears in two pairs, no capacity-one source or sink edge is exceeded. The resulting flow is feasible and has one unit per matched pair. $\square$

### Lemma 3

The pairs printed by the implementation are exactly the matching represented by the final flow.

#### Proof

Every remembered boy-girl edge began with capacity one. Integral flow can place either zero or one unit on it. It carries one unit exactly when its forward residual capacity has decreased to zero. The scan prints precisely these saturated pair edges, and Lemma 1 shows they form a matching whose size equals the flow. $\square$

### Theorem

The algorithm prints a maximum-cardinality valid dance pairing.

#### Proof

By Lemma 2, maximum flow is at least the size of every matching. By Lemma 1, the maximum flow itself produces a matching of the same value, so no larger matching exists. Lemma 3 proves that the output is exactly such a matching. $\square$

## Implementation

`firstEdge` stores the residual identifier returned implicitly by `es.size()` just before each boy-girl edge is added. This preserves a direct link from input pairs to their final saturation state.

For a saturated pair edge `id`, `es[id^1].to` is the boy because the reverse edge points back to its source. The forward destination minus `n` recovers the girl's original index.

Parallel acceptable-pair entries are represented separately, but capacity-one student edges ensure that at most one can be selected.

## Complexity

The network has $n+m+2$ vertices and $n+m+k$ forward edges. The implementation uses Dinic, with general bound $O(V^2E)$ and $O(V+E)$ auxiliary space. Unit capacities and the layered bipartite structure make it substantially faster in practice for the given limits.

## Worked Example

Suppose boy 1 accepts girls 1 and 2, while boy 2 accepts only girl 1. Selecting pair $(1,1)$ greedily blocks boy 2 and yields one pair. In the residual network, an augmenting path can reverse that decision and produce $(1,2)$ plus $(2,1)$, yielding flow two.

The final source-to-boy and girl-to-sink edges for both students are saturated, and scanning the pair edges prints the two chosen matches.
