# Xor Pyramid Peak

- **Source:** [CSES 2419: Xor Pyramid Peak](https://cses.fi/problemset/task/2419/)
- **Code:** [`xorpyramidpeak.cpp`](../xorpyramidpeak.cpp)

## Problem

Given the bottom row of an xor pyramid, find the single value at its peak. Each higher row is formed by xoring adjacent values.

## Idea

After $d$ reductions, the coefficient of bottom value $a_i$ in the leftmost result is

$$
\binom di\bmod2.
$$

For the peak, $d=n-1$. Lucas' theorem modulo two states that $\binom di$ is odd exactly when every set bit of $i$ is also set in $d$. Thus, $i$ contributes precisely when

$$
(i\mathbin{\&}d)=i.
$$

## Algorithm

For each zero-based index $i$, xor $a_i$ into the answer when $i$ is a submask of $n-1$.

## Correctness

**Lemma.** After $d$ reductions, the coefficient of $a_i$ in the leftmost value is $\binom di\bmod2$.

**Proof.** Adjacent xor follows Pascal's recurrence. Coefficients from the two children add modulo two, giving Pascal's triangle modulo two. $\square$

**Theorem.** The algorithm outputs the pyramid peak.

**Proof.** By the lemma, $a_i$ contributes exactly when $\binom{n-1}{i}$ is odd. Lucas' theorem identifies exactly the submasks of $n-1$, which are precisely the indices selected by the implementation. $\square$

## Complexity

The time complexity is $O(n)$ and the auxiliary space is $O(1)$.

## Implementation

The test `(i & (n - 1)) == i` is the standard submask test. Values are read and incorporated immediately, so the bottom row does not need to be stored.

## Worked Example

If $n=8$, then $n-1=7=(111)_2$. Every index from $0$ through $7$ is a submask of $7$, so every bottom value contributes to the peak.

## Takeaway

Repeated linear neighbor operations often produce binomial coefficients. Modulo two, Lucas' theorem converts coefficient parity into a submask condition.
