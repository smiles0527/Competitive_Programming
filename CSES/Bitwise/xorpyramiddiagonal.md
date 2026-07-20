# Xor Pyramid Diagonal

- **Source:** [CSES 3194: Xor Pyramid Diagonal](https://cses.fi/problemset/task/3194/)
- **Code:** [`xorpyramiddiagonal.cpp`](./xorpyramiddiagonal.cpp)

## Problem

Given the bottom row of an xor pyramid, output the leftmost value of every row, starting at the bottom and moving upward.

## Idea

After $d$ reductions, the leftmost value is

$$
L(d)=\bigoplus_{i=0}^{d}(\binom di\bmod2)a_i.
$$

By Lucas' theorem, the coefficient is odd exactly when $i$ is a submask of $d$. Therefore,

$$
L(d)=\bigoplus_{i\subseteq d}a_i.
$$

This is the subset zeta transform with xor as the aggregation operation. Pad the array with zeros to a power of two. For every bit, a mask containing that bit receives the value of the same mask with the bit cleared.

## Algorithm

1. Pad the bottom row to the smallest power-of-two length $M\ge n$.
2. For every bit value `b` and every mask containing it, apply

   $$
   a[\text{mask}]\mathrel{\oplus}=a[\text{mask}\oplus b].
   $$

3. Output the first $n$ transformed values.

## Correctness

**Lemma.** After processing a set of bit positions, `a[mask]` is the xor of the original entries obtained by independently clearing any subset of those processed bits from `mask`.

**Proof.** Before any bit is processed, only the original mask contributes. Processing bit $b$ combines the class where $b$ remains set with the class where it is cleared. These classes are disjoint and cover every allowed choice for $b$. Induction proves the invariant. $\square$

**Theorem.** The algorithm outputs every leftmost pyramid value.

**Proof.** After all bits are processed, the lemma gives the xor of every submask of $d$ at position $d$. Lucas' theorem shows that this is exactly the leftmost value after $d$ reductions. Output positions $0$ through $n-1$ therefore list the required diagonal from bottom to top. $\square$

## Complexity

For the next power of two $M$, the time complexity is $O(M\log M)$ and the memory usage is $O(M)$.

## Implementation

Padding with zeroes does not affect positions below $n$, because every submask of such a position is also below $n$. The transform is safe in place: during a bit stage, source masks without that bit are not modified by destinations containing it.

## Worked Example

For masks $0$ through $3$, the transform produces the xor of submask sets $\{0\}$, $\{0,1\}$, $\{0,2\}$, and $\{0,1,2,3\}$, matching the odd entries of the corresponding Pascal rows.

## Takeaway

When every answer is an aggregate over all submasks, use a sum-over-subsets transform. The aggregation operation can be xor when it is associative.
