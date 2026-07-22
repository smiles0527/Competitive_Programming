# Dice Combinations

## Problem

- **Source:** [CSES 1633: Dice Combinations](https://cses.fi/problemset/task/1633/)
- **Code:** [`View accepted C++ solution (dicecombinations.cpp)`](./dicecombinations.cpp)

Count, modulo $10^9+7$, the number of ordered sequences of integers from $1$ through $6$ whose sum is exactly $n$.

Order matters: two sequences with the same multiset of elements but different orderings are different sequences. For $n=3$, the valid sequences are $1+1+1$, $1+2$, $2+1$, and $3$.

## Idea

Enumerating all sequences gives an exponential search tree. The crucial observation is that each nonempty sequence has a unique last roll.

Define $dp[s]$ as the number of sequences whose sum is $s$.

If a sequence summing to $s$ ends with $d$, removing that roll gives a sequence summing to $s-d$. Conversely, appending $d$ to any sequence summing to $s-d$ produces a unique sequence summing to $s$ whose last roll is $d$.

Hence, the sequences split into six mutually exclusive classes, one for each $d\in\{1,2,3,4,5,6\}$:

$$dp[s]=\sum_{\substack{1\le d\le6\\d\le s}}dp[s-d].$$

The condition $d\le s$ prevents the use of negative sums.

The initial condition is $dp[0]=1$, representing the single empty prefix. This is how one roll can build a positive sum; it does not claim that zero represents a nonempty dice sequence.

The recurrence also explains why order is counted. For sum $3$, state $dp[1]$ contributes by appending $2$, while $dp[2]$ contributes by appending $1$. These are different last-roll classes.

## Algorithm

1. Initialize $dp[0]=1$ and all other states to zero.
2. For every target sum $s=1,2,\ldots,n$:
   * for every $d\in\{1,2,3,4,5,6\}$ with $d\le s$, add $dp[s-d]$ to $dp[s]$ modulo $10^9+7$.
3. Return $dp[n]$.

## Correctness

### Lemma 1

For fixed $s$ and $d$ with $0<d\le s$, the number of sequences summing to $s$ whose last roll is $d$ equals $dp[s-d]$.

#### Proof

Removing the final $d$ gives a prefix summing to $s-d$. The operation is invertible: appending $d$ to any sequence summing to $s-d$ gives a unique sequence summing to $s$ whose last roll is $d$. Therefore, the two sets are in bijection. $\square$

### Lemma 2

After processing sum $s$, $dp[s]$ equals the number of ordered dice sequences summing to $s$.

#### Proof

By induction on $s$. The base state $dp[0]=1$ correctly represents the only empty sequence.

For $s\ge1$, every valid sequence has a unique last roll $d\in\{1,\ldots,6\}$ with $d\le s$. Classes with different final rolls are disjoint. By Lemma 1, the class ending in $d$ contains $dp[s-d]$ sequences. The recurrence sums exactly these classes, so $dp[s]$ is correct. $\square$

### Theorem

The algorithm returns the number of ordered dice sequences whose sum is $n$.

#### Proof

States are computed in increasing order, so Lemma 2 holds for every $s\le n$. Hence, $dp[n]$ is the required count, with every update performed modulo $10^9+7$. $\square$

## Implementation

The outer loop processes sums increasingly because every transition into $dp[s]$ comes from a smaller sum. The inner loop limits $d$ to $d\le s$, enforcing the nonnegative-state boundary.

After every addition, both operands are smaller than the modulus, so one subtraction is enough and the intermediate sum fits in a signed `int`.

## Complexity

Each of the $n$ states considers at most six rolls, giving $O(6n)=O(n)$ time and $O(n)$ space.

## Worked Example

For $n=5$, classify sequences by their final roll:

| Last roll | Remaining sum | Contribution |
|---:|---:|---:|
| $1$ | $4$ | $dp[4]=8$ |
| $2$ | $3$ | $dp[3]=4$ |
| $3$ | $2$ | $dp[2]=2$ |
| $4$ | $1$ | $dp[1]=1$ |
| $5$ | $0$ | $dp[0]=1$ |

Thus, $dp[5]=8+4+2+1+1=16$.

## Takeaway

For ordered constructions, partition complete objects by their last decision. Removing that decision often produces the smaller instance and the natural dynamic-programming recurrence.

## Related Problems

Coin Combinations I uses the same last-decision recurrence with arbitrary coin values. Coin Combinations II changes the loop order to count unordered selections.
