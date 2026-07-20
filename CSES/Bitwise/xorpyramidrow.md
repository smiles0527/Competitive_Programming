# Xor Pyramid Row

- **Source:** [CSES 3195: Xor Pyramid Row](https://cses.fi/problemset/task/3195/)
- **Code:** [`xorpyramidrow.cpp`](./xorpyramidrow.cpp)

## Problem

An xor pyramid starts with $n$ values at the bottom. Each higher row replaces adjacent pairs by their xor. Output the row of length $k$.

## Idea

The required row is obtained after

$$
d=n-k
$$

ordinary reductions. Let $E$ denote the shift operator. One reduction applies $I+E$. Over $\mathrm{GF}(2)$, the middle terms vanish when squaring, so

$$
(I+E)^{2^t}=I+E^{2^t}.
$$

For every set power $q=2^t$ in the binary representation of $d$, apply one pass

$$
a_i\gets a_i\oplus a_{i+q}.
$$

This performs $q$ reductions at once and shortens the active row by $q$. The selected shifts sum to $d$, so the final length is $n-d=k$.

## Algorithm

1. Set `d = n - k` and active length `m = n`.
2. For every set power `q` of `d`:
   - apply `a[i] ^= a[i + q]` for every `i + q < m`;
   - decrease `m` by `q`.
3. Output the first $k$ entries.

## Correctness

**Lemma 1.** A pass with shift $q=2^t$ applies exactly $q$ ordinary pyramid reductions.

**Proof.** One reduction is $I+E$. The Frobenius identity in characteristic two gives $(I+E)^q=I+E^q$, whose entrywise action is $a_i\gets a_i\oplus a_{i+q}$. $\square$

**Lemma 2.** After processing some set bits of $d$, the active prefix equals the row obtained after a number of reductions equal to their sum.

**Proof.** Initially the sum is zero and the active prefix is the bottom row. By Lemma 1, processing shift $q$ composes the current row with exactly $q$ further reductions and shortens it by $q$. Induction proves the invariant. $\square$

**Theorem.** The algorithm outputs the row of length $k$.

**Proof.** All processed powers sum to $d=n-k$. By Lemma 2, the final active prefix is the bottom row after exactly $d$ reductions, and its length is $n-d=k$. $\square$

## Complexity

The time complexity is $O(n\operatorname{popcount}(n-k))\subseteq O(n\log n)$ and the memory usage is $O(n)$.

## Implementation

Each pass runs from left to right. Since the source index `i + q` is larger than `i`, it has not yet been modified during that pass. If $d=0$, no pass runs and the original bottom row is printed.

## Worked Example

For $n=9$ and $k=4$, $d=5=(101)_2$. The algorithm applies shifts $1$ and $4$, reducing the active length as

$$
9\longrightarrow8\longrightarrow4.
$$

Together the two passes represent exactly five ordinary reductions.

## Takeaway

In xor arithmetic, a power-of-two number of adjacent reductions collapses into one long-distance xor. Decompose the required number of levels into binary powers.
