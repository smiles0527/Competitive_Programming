# Counting Bits

- **Source:** [CSES 1146: Counting Bits](https://cses.fi/problemset/task/1146/)
- **Code:** [`countingbits.cpp`](../countingbits.cpp)

## Problem

Find the total number of set bits in the binary representations of all integers from $1$ through $n$.

Enumerating every value and applying a popcount function is too slow when $n$ is large. The total must be calculated one bit position at a time.

## Idea

Fix bit position $i$, whose value is $2^i$. Across consecutive nonnegative integers, this bit has a periodic pattern: it is zero for $2^i$ values, then one for $2^i$ values. The period is therefore $2^{i+1}$.

Count over the half-open interval $[0,N)$, where $N=n+1$. Let

$$
\text{half}=2^i,
\qquad
\text{block}=2^{i+1}.
$$

There are $\lfloor N/\text{block}\rfloor$ complete blocks, each contributing `half` set bits. If

$$
\text{rem}=N\bmod\text{block},
$$

then the remaining prefix contributes

$$
\max(0,\text{rem}-\text{half}).
$$

The first `half` positions of a block contain zeros at bit $i$; every remaining position contains a one. Including zero does not affect the answer because zero has no set bits.

## Algorithm

For every power of two `b` not exceeding $n$:

1. Set `len = 2 * b`.
2. Add `(n + 1) / len * b` for the complete blocks.
3. Add `max(0, (n + 1) % len - b)` for the partial block.

Output the accumulated total.

## Correctness

**Lemma.** For a fixed bit value $b=2^i$, the algorithm counts exactly the integers in $[0,n]$ whose bit $i$ is set.

**Proof.** Every complete block of length $2b$ contains $b$ zeroes followed by $b$ ones at bit $i$, so the complete-block term is exact. In the remaining prefix, no one appears among the first $b$ positions, while each later position contributes one. Its contribution is therefore $\max(0,\text{rem}-b)$. The complete blocks and remaining prefix partition $[0,n]$. $\square$

**Theorem.** The algorithm outputs the total number of set bits in $1,2,\ldots,n$.

**Proof.** Every set bit belongs to one unique bit position. By the lemma, the contribution of each position is counted exactly. Summing over all relevant positions counts every set bit once. Zero contributes nothing, so counting $[0,n]$ gives the required total over $[1,n]$. $\square$

## Complexity

There are $\Theta(\log n)$ relevant bit positions. The time complexity is $O(\log n)$ and the auxiliary space is $O(1)$.

## Implementation

The loop variable `b` is a `long long`, so `b << 1` and every quotient or product use 64-bit arithmetic. The half-open interval represented by `n + 1` avoids separate handling of the inclusive endpoint.

## Worked Example

For $n=6$, set $N=7$.

| Bit | Block length | Complete contribution | Partial contribution | Total |
| ---: | ---: | ---: | ---: | ---: |
| $0$ | $2$ | $3$ | $0$ | $3$ |
| $1$ | $4$ | $2$ | $1$ | $3$ |
| $2$ | $8$ | $0$ | $3$ | $3$ |

The result is $3+3+3=9$.

## Takeaway

When aggregating bits over an integer range, treat each bit independently through its periodic zero-one pattern. Half-open intervals turn the count into quotient and remainder expressions.
