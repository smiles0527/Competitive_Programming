# SOS Bit Problem

- **Source:** [CSES 1654: SOS Bit Problem](https://cses.fi/problemset/task/1654/)
- **Code:** [`sosbitproblem.cpp`](../sosbitproblem.cpp)

## Problem

For every input value $x$, count input values $y$ satisfying:

1. $x\mathbin{|}y=x$;
2. $x\mathbin{\&}y=x$;
3. $x\mathbin{\&}y\ne0$.

## Idea

The first condition means $y$ is a submask of $x$. The second means $y$ is a supermask of $x$.

Starting from the frequency array, compute

$$
\operatorname{sub}[x]=\sum_{y\subseteq x}\operatorname{freq}[y]
$$

with a subset zeta transform, and

$$
\operatorname{sup}[x]=\sum_{y\supseteq x}\operatorname{freq}[y]
$$

with a superset zeta transform.

For the third count, subtract disjoint values. A value $y$ satisfies $x\mathbin{\&}y=0$ exactly when $y$ is a submask of the $20$-bit complement of $x$. If `full = 2^20 - 1`, the answer is

$$
n-\operatorname{sub}[\text{full}\oplus x].
$$

## Algorithm

1. Store each input frequency in both `sub` and `sup`.
2. Apply the subset zeta transform to `sub`.
3. Apply the superset zeta transform to `sup`.
4. For every original $x$, output `sub[x]`, `sup[x]`, and `n - sub[full ^ x]`.

## Correctness

**Lemma 1.** After the subset transform, `sub[x]` counts input values that are submasks of $x$.

**Proof.** Processing a bit combines masks where that bit is retained with masks where it is cleared. After all bits, every submask and only a submask contributes. $\square$

**Lemma 2.** After the superset transform, `sup[x]` counts input values that are supermasks of $x$.

**Proof.** Symmetrically, processing a missing bit allows it to be either absent or set. After all bits, exactly the masks containing every bit of $x$ contribute. $\square$

**Theorem.** The three values printed for every $x$ are correct.

**Proof.** Lemmas 1 and 2 establish the first two counts. Values disjoint from $x$ are exactly the submasks of its $20$-bit complement, so subtracting their count from $n$ gives the third. $\square$

## Complexity

For $U=2^{20}$, the time complexity is $O(20U+n)$ and the memory usage is $O(U+n)$.

## Implementation

The complement is calculated as `(m - 1) ^ x`; using unary `~x` would also set irrelevant higher bits and produce an invalid index. The original array is retained because answers are printed in input order.

## Worked Example

For $x=3=(0011)_2$, suppose the sample contains three submasks of $3$, two supermasks of $3$, and five values sharing at least one set bit with $3$. The printed line is `3 2 5`.

## Takeaway

Bitwise containment becomes a submask or supermask relation. SOS transforms turn many such per-value scans into constant-time lookups after preprocessing.
