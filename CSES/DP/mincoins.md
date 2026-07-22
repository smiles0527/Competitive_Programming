# Minimizing Coins

## Problem

- **Source:** [CSES 1634: Minimizing Coins](https://cses.fi/problemset/task/1634/)
- **Code:** [`View accepted C++ solution (mincoins.cpp)`](./mincoins.cpp)

Given $n$ positive coin values and a target $x$, return the minimum number of coins whose values sum to exactly $x$. Each denomination may be used arbitrarily many times. Output $-1$ if $x$ is unreachable.

For coins $\{1,5,7\}$ and target $11$, one optimum construction is $5+5+1$, requiring three coins.

## Idea

Greedily selecting the largest coin is incorrect for general denominations. For coins $\{1,3,4\}$ and target $6$, greedy produces $4+1+1$, although $3+3$ uses fewer coins.

Instead, describe a construction by its last coin. Let $dp[s]$ be the minimum number of coins required to form sum $s$.

If the last coin is worth $c$, removing it leaves a construction of $s-c$. A minimum construction ending in $c$ therefore uses $dp[s-c]+1$ coins. Checking every possible last coin gives

$$dp[s]=\min_{\substack{c\text{ is a coin}\\c\le s}}\bigl(dp[s-c]+1\bigr).$$

The base case is $dp[0]=0$, since no coins are required to form zero. Every positive state begins as unreachable.

The recurrence has optimal substructure. If an optimal construction ending in $c$ used a nonoptimal prefix for $s-c$, replacing that prefix by an optimal one would reduce the total number of coins, contradicting optimality.

## Algorithm

1. Sort the coin values.
2. Initialize all states to the unreachable sentinel $x+1$, then set $dp[0]=0$.
3. For every sum $s=1,2,\ldots,x$:
   * inspect coins while $c_i\le s$;
   * minimize $dp[s]$ with $dp[s-c_i]+1$.
4. If $dp[x]>x$, print $-1$; otherwise, print $dp[x]$.

## Correctness

### Lemma 1

Every finite candidate $dp[s-c]+1$ for $dp[s]$ is the size of a valid construction of $s$.

#### Proof

A finite state $dp[s-c]$ represents a construction of $s-c$. Adding one coin of value $c$ produces sum $s$ and increases the number of coins by one. $\square$

### Lemma 2

After processing sum $s$, $dp[s]$ equals the minimum number of coins forming $s$, or remains unreachable if no construction exists.

#### Proof

Use induction on $s$. The base state $dp[0]=0$ is optimal.

For $s>0$, Lemma 1 shows that every finite transition considered is valid, so $dp[s]$ cannot be smaller than the optimum.

Conversely, take an optimal construction of $s$ and let $c$ be its final coin. Removing $c$ leaves a construction of $s-c$. By the induction hypothesis, $dp[s-c]$ is no larger than this prefix. Since the algorithm considers $c$, its candidate is no larger than the optimum. Hence, $dp[s]$ equals the optimum. If no predecessor is reachable, no construction can have that last coin, and the state remains unreachable. $\square$

### Theorem

The algorithm outputs the minimum number of coins forming $x$, or $-1$ if $x$ is unreachable.

#### Proof

By Lemma 2, $dp[x]$ is optimal whenever $x$ is reachable and remains unreachable otherwise. The final sentinel check distinguishes these cases. $\square$

## Implementation

The sentinel is $x+1$. Because all coin values are positive integers, any valid construction of $x$ uses at most $x$ coins. Therefore, no valid answer is confused with the sentinel.

If a predecessor is unreachable, adding one still produces a value greater than $x$, so it cannot replace a valid answer.

Sorting is not needed for correctness, but allows the inner loop to stop at the first denomination exceeding the current sum:

```cpp
for (int i = 0; i < n && c[i] <= s; i++)
```

Sums are processed increasingly because every dependency $s-c_i$ is smaller than $s$.

## Complexity

Sorting takes $O(n\log n)$. The DP checks at most $n$ coins for each of $x$ sums, taking $O(nx)$ time and $O(x)$ space.

## Worked Example

For coins $\{1,5,7\}$ and target $11$, useful states include $dp[0]=0$, $dp[1]=1$, $dp[5]=1$, $dp[6]=2$, $dp[7]=1$, and $dp[10]=2$.

For the target,

$$dp[11]=1+\min(dp[10],dp[6],dp[4])=3.$$

One optimum is $5+5+1$.

## Takeaway

When greedy denomination choice fails, examine an optimal construction and its last coin. The remaining construction reveals a one-dimensional minimum DP.

## Related Problems

Coin Combinations I counts ordered constructions instead of minimizing them. Coin Combinations II changes the iteration order to count unordered constructions.
