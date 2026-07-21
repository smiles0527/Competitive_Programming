# De Bruijn Sequence

## Problem

- **Source:** [CSES 1692: De Bruijn Sequence](https://cses.fi/problemset/task/1692/)
- **Code:** [`View accepted C++ solution (debrujin.cpp)`](./debrujin.cpp)
- **Constraints:** $1\le n\le15$.

Construct a binary string in which every binary string of length $n$ occurs exactly once as a contiguous substring.

There are $2^n$ required windows, so a linear answer has length $2^n+n-1$.

## Idea

Successive length-$n$ windows overlap in $n-1$ bits. Build a directed graph whose vertices are binary strings of length $n-1$. For every length-$n$ string, add an edge from its $(n-1)$-bit prefix to its $(n-1)$-bit suffix, labeled by the final bit.

Thus edges correspond one-to-one with required windows. Every vertex has two incoming and two outgoing edges, and the overlap graph is connected, so it has an Eulerian circuit. The circuit's edge labels form a cyclic De Bruijn sequence.

For integer state $v$ and appended bit $b$, the next state is

$$
u=((v\ll1)\mid b)\mathbin{\&}(2^{n-1}-1).
$$

## Algorithm

1. For $n=1$, print `01`.
2. Represent the $2^{n-1}$ overlap states by integers and give each state two implicit outgoing edges, labeled 0 and 1.
3. Run iterative Hierholzer from the all-zero state, storing the entering edge label with each stack entry.
4. Append labels during backtracking and reverse them to obtain the cyclic sequence.
5. Append its first $n-1$ labels to expose the windows crossing the cycle boundary.

## Correctness

### Lemma 1

The implicit graph contains exactly one edge for every binary string of length $n$.

#### Proof

A length-$n$ string is uniquely determined by its first $n-1$ bits, which select the source state, and its final bit, which selects one of the two outgoing edges. $\square$

### Lemma 2

Hierholzer's traversal uses every edge of the implicit graph exactly once.

#### Proof

Each state cursor selects labels 0 and 1 once. Every state has equal indegree and outdegree. Repeatedly appending zero reaches the all-zero state from every state, and suitable prefixes reach every state from zero, so all edges lie in one Eulerian component. Hierholzer therefore uses all $2^n$ edges once. $\square$

### Theorem

The printed string contains every length-$n$ binary string exactly once.

#### Proof

By Lemma 2, the cyclic edge-label sequence visits each edge once. By Lemma 1, its cyclic length-$n$ windows are exactly all binary strings. Appending the first $n-1$ labels exposes precisely the windows crossing the chosen cut, producing the required linear sequence. $\square$

## Implementation

`mask` retains the low $n-1$ bits. The sentinel entering label `-1` belongs to the initial state and is not appended. Labels are collected while backtracking, hence the reversal. The special case $n=1$ avoids a zero-bit state representation.

## Complexity

The time complexity is $O(2^n)$ and the auxiliary space is $O(2^n)$.

## Worked Example

For $n=3$, the states are `00`, `01`, `10`, and `11`. The edge from `01` labeled `1` reaches `11` and represents `011`. One Eulerian label cycle is `00010111`; appending its first two labels gives `0001011100`. Its windows are `000`, `001`, `010`, `101`, `011`, `111`, `110`, and `100`.
