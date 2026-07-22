# Coin Combinations I

## Problem

- **Source:** [CSES 1635: Coin Combinations I](https://cses.fi/problemset/task/1635/)
- **Code:** [`View accepted C++ solution (coincombo1.cpp)`](./coincombo1.cpp)

With $n$ distinct positive coin values, calculate the number of ordered coin sequences with total sum $x$. Each denomination may be used arbitrarily many times. Output the answer modulo $10^9+7$.

Order matters. For example, $2+3$ and $3+2$ are different sequences.

## Idea

Let $dp[s]$ be the number of ordered coin sequences summing to $s$.

Every nonempty sequence has a unique final coin $c$. Removing it gives a sequence summing to $s-c$. Conversely, appending $c$ to any sequence summing to $s-c$ produces a unique sequence summing to $s$ ending in $c$.

Therefore,

$$dp[s]=\sum_{\substack{c\text{ is a coin}\\c\le s}}dp[s-c],$$

with base state $dp[0]=1$.

The base represents the single empty prefix and allows sum $c$ to be formed by one coin through $dp[c-c]$.

The loop order reflects this definition. First fix the formed sum $s$, then consider all possible last coins. Thus, $2+3$ enters $dp[5]$ by appending $3$ to $dp[2]$, while $3+2$ enters through appending $2$ to $dp[3]$.

Putting the coin loop outside would instead classify constructions by the set of processed denominations, producing the unordered problem Coin Combinations II.

## Algorithm

1. Sort the coin values.
2. Initialize $dp[0]=1$ and all other states to zero.
3. For every sum $s=1,2,\ldots,x$:
   * for every sorted coin $c_i\le s$, add $dp[s-c_i]$ to $dp[s]$ modulo $10^9+7$.
4. Output $dp[x]$.

## Correctness

### Lemma 1

For fixed $s$ and coin $c$, the number of valid sequences summing to $s$ whose last coin is $c$ equals $dp[s-c]$.

#### Proof

Removing the final $c$ gives an ordered sequence with sum $s-c$. This is reversible by appending $c$, so it is a bijection. $\square$

### Lemma 2

After processing sum $s$, $dp[s]$ equals the number of ordered coin sequences summing to $s$.

#### Proof

Use induction on $s$. The base $dp[0]=1$ correctly represents the empty sequence.

For $s>0$, every valid sequence has a unique last coin $c$. Since denominations are distinct, the classes for different final coins are disjoint. By Lemma 1 and the induction hypothesis, the class ending in $c$ has $dp[s-c]$ members. The transition sums exactly these classes, counting every sequence once. $\square$

### Theorem

The algorithm outputs the number of ordered coin sequences summing to $x$.

#### Proof

The increasing-sum loop computes each predecessor before it is used. Lemma 2 therefore holds through sum $x$, making $dp[x]$ the required count modulo $10^9+7$. $\square$

## Implementation

Sorting is optional but allows the inner loop to stop when a denomination exceeds the current sum.

```cpp
dp[s] += dp[s - c[i]];
if (dp[s] >= MOD) dp[s] -= MOD;
```

Both operands are below `MOD`, so one subtraction is sufficient and the intermediate value fits in `int`.

The outer sum loop is mandatory: every ordered prefix $dp[s-c]$ is already built, and the inner loop appends every possible final coin.

## Complexity

Sorting costs $O(n\log n)$. The dynamic program checks at most $n$ coins for each of $x$ sums, taking $O(nx)$ time and $O(x)$ space.

## Worked Example

Let the coins be $\{2,3,5\}$ and $x=9$. At sum $5$, the last-coin classes are:

| Last coin | Prefix sum | Completed sequences |
|---:|---:|---|
| $2$ | $3$ | $3+2$ |
| $3$ | $2$ | $2+3$ |
| $5$ | $0$ | $5$ |

Thus, $dp[5]=3$. Continuing the recurrence gives $dp[9]=8$.

## Takeaway

For ordered unlimited-choice sums, fix the total first and partition constructions by their last choice. This interpretation determines the loop order.

## Related Problems

Dice Combinations uses the same recurrence with choices $1$ through $6$. Coin Combinations II reverses the nesting to count unordered constructions.
