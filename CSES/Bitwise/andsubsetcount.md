# And Subset Count

- **Source:** [CSES 3141: And Subset Count](https://cses.fi/problemset/task/3141/)
- **Code:** [`andsubsetcount.cpp`](./andsubsetcount.cpp)

## Problem

For every $k=0,1,\ldots,n$, count the nonempty subsets whose bitwise AND equals $k$. Compute every answer modulo $10^9+7$.

## Idea

Fix a mask $x$. A subset has an AND containing every bit of $x$ exactly when every selected element is a supermask of $x$.

Let

$$
c[x]=\lvert\{i:(a_i\mathbin{\&}x)=x\}\rvert.
$$

There are $2^{c[x]}-1$ nonempty subsets formed from those eligible elements. If `exact[y]` counts subsets whose AND is exactly $y$, then

$$
2^{c[x]}-1=\sum_{y\supseteq x}\operatorname{exact}[y].
$$

The right side is a superset zeta transform. First compute $c[x]$ from element frequencies, convert it into cumulative subset counts, then apply superset Möbius inversion to recover exact AND values.

## Algorithm

1. Count the frequency of each input mask.
2. Apply a superset zeta transform to obtain $c[x]$.
3. Set `ans[x] = 2^c[x] - 1` modulo $10^9+7$.
4. Apply superset Möbius inversion by replacing addition with subtraction.
5. Output `ans[0]` through `ans[n]`.

## Correctness

**Lemma 1.** After the first transform, $c[x]$ is the number of input elements that are supermasks of $x$.

**Proof.** For every missing bit, the transform adds masks in which that bit is set. After all bits, the contributing masks are exactly those containing all bits of $x$. $\square$

**Lemma 2.** $2^{c[x]}-1$ counts nonempty subsets whose AND is a supermask of $x$.

**Proof.** Such a subset may select any nonempty collection of the $c[x]$ elements containing every bit of $x$, and may select no other element. Every such selection preserves $x$ in its AND, and every subset preserving $x$ uses only eligible elements. $\square$

**Lemma 3.** Superset Möbius inversion recovers counts for each exact AND.

**Proof.** Before inversion, each coordinate is the sum of exact counts over all supermasks. The subtraction butterfly performs inclusion-exclusion over optional additional bits, which is the inverse of the superset zeta transform. $\square$

**Theorem.** The algorithm outputs the required number of subsets for every exact AND value.

**Proof.** Lemma 1 computes eligible element counts, Lemma 2 converts them into cumulative subset counts, and Lemma 3 recovers exact counts. $\square$

## Complexity

For the power-of-two universe $M$, the time complexity is $O(M\log M+n)$ and the memory usage is $O(M+n)$.

## Implementation

The same conceptual array passes through three meanings: element frequency, supermask element count, and cumulative subset count. Exact counts are stored separately in `ans`. Subtracting one excludes the empty subset, and modular subtractions are normalized immediately.

## Worked Example

For $[3,1,3,4]$, the exact counts for AND values $0,1,2,3,4$ are

$$
7,4,0,3,1.
$$

## Takeaway

To count subsets by exact bitwise AND, first count subsets satisfying a required-bit condition, then invert the resulting superset sums on the Boolean lattice.
