# Money Sums

## Problem

- **Source:** [CSES 1745: Money Sums](https://cses.fi/problemset/task/1745/)
- **Code:** [`View accepted C++ solution (moneysums.cpp)`](./moneysums.cpp)

Given $n$ coins, each usable at most once, determine every positive sum obtainable from a subset and print the sums increasingly.

## Idea

Let $dp[s]$ indicate whether sum $s$ can be formed using the coins processed so far.

Initially, no coins have been processed. The only reachable sum is zero, formed by the empty subset:

$$dp[0]=\text{true}.$$

When processing a coin of value $x$, every previously reachable sum $s-x$ creates a new reachable sum $s$:

$$dp[s]\mathrel{|}=dp[s-x].$$

Sums must be processed in decreasing order so that the current coin is used at most once during its iteration.

## Algorithm

Let $S=\sum_{i=1}^n x_i$.

1. Create a Boolean array $dp[0\ldots S]$ and set $dp[0]=\text{true}$.
2. For every coin $x$:
   * iterate from the current maximum reachable sum plus $x$ down to $x$;
   * if $dp[s-x]$ is true, set $dp[s]$ to true.
3. Scan $dp[1\ldots S]$ from left to right and output every reachable index.

The scan automatically produces increasing order.

## Correctness

We prove that after processing any prefix of the coins, $dp[s]$ is true exactly when a subset of those coins has sum $s$.

Initially, only the empty subset is available, so only sum zero is reachable.

Now process a coin of value $x$. A reachable sum after this step either comes from a subset that excludes $x$, in which case it was already reachable, or from a subset that includes $x$, in which case removing the coin leaves a subset of sum $s-x$.

The update $dp[s]\mathrel{|}=dp[s-x]$ covers both cases. Because sums are processed decreasingly, $dp[s-x]$ still refers to a subset formed before the current coin was used. Therefore, the coin cannot be selected more than once.

Thus, after all coins are processed, $dp[s]$ is true exactly for the achievable subset sums.

## Implementation

The maximum possible sum is at most $100\cdot1000=100000$, so a one-dimensional Boolean array is sufficient.

Variable `cur` stores the sum of processed coins. Before adding $x$, no sum above `cur` is reachable, so only sums through `cur + x` must be checked.

```cpp
for (int x : a) {
    for (int s = cur + x; s >= x; s--) {
        if (dp[s - x]) dp[s] = true;
    }
    cur += x;
}
```

The backward loop is crucial. A forward loop could use a state created by the same coin and thereby select it repeatedly.

## Complexity

Let $S=\sum_i x_i$. The time complexity is $O(nS)$ and the DP array uses $O(S)$ space.

## Worked Example

For coins $[4,2,5,2]$, the reachable positive sums evolve as follows:

* after $4$: $\{4\}$;
* after $2$: $\{2,4,6\}$;
* after $5$: $\{2,4,5,6,7,9,11\}$;
* after the final $2$: $\{2,4,5,6,7,8,9,11,13\}$.

There are nine distinct reachable positive sums.
