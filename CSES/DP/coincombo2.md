# Coin Combinations II

## Problem

- **Source:** [CSES 1636: Coin Combinations II](https://cses.fi/problemset/task/1636/)
- **Code:** [`View accepted C++ solution (coincombo2.cpp)`](./coincombo2.cpp)

Given $n$ distinct positive coin values, count the combinations whose total is $x$. Each denomination may be used arbitrarily many times, but combinations differing only by coin order are identical. Output the answer modulo $10^9+7$.

For coins $\{2,3,5\}$ and target $9$, the combinations are $2+2+5$, $3+3+3$, and $2+2+2+3$, so the answer is $3$.

## Idea

The recurrence for Coin Combinations I cannot be used with the same loop order. With a fixed sum and a loop over final coins, $2+3$ and $3+2$ are created separately.

To discard order, process denominations one at a time. After processing the first $i$ coin types, maintain the invariant that $dp[s]$ is the number of combinations summing to $s$ using only those types.

Initially, no types have been processed, so $dp[0]=1$ and all positive states are zero.

Now process a coin of value $c$. A combination of sum $s$ either contains no $c$, in which case it is already counted by $dp[s]$, or contains at least one $c$. Removing one $c$ from the latter produces a combination of sum $s-c$ that may itself contain $c$. Therefore,

$$dp[s]\mathrel{+}=dp[s-c].$$

The sum loop must move upward. When processing $dp[s]$, state $dp[s-c]$ has already been updated for the current denomination, so it represents combinations containing zero, one, or many copies of $c$.

The two loop choices have separate meanings:

* coin types outside prevent permutations from being regenerated;
* increasing sums inside allow unlimited reuse of the current coin.

## Algorithm

1. Set $dp[0]=1$ and every other state to zero.
2. For each coin value $c_i$:
   * for $s=c_i,c_i+1,\ldots,x$, add $dp[s-c_i]$ to $dp[s]$ modulo $10^9+7$.
3. Output $dp[x]$.

## Correctness

### Lemma 1

While processing coin type $i$, immediately after updating sum $s$, $dp[s]$ equals the number of combinations summing to $s$ using only the first $i$ coin types.

#### Proof

Before the update, $dp[s]$ counts combinations using only the first $i-1$ types, exactly those using zero copies of $c_i$.

Because sums are scanned increasingly, $dp[s-c_i]$ has already been updated for $c_i$. It counts combinations of sum $s-c_i$ using the first $i$ types. Adding one $c_i$ bijectively produces all combinations of sum $s$ containing at least one $c_i$.

The zero-copy and positive-copy groups are disjoint and exhaustive, so their sum is correct. $\square$

### Lemma 2

After processing the first $i$ coin types, every state $dp[s]$ counts all combinations summing to $s$ using only those types.

#### Proof

For $i=0$, only the empty combination forms sum zero, matching the initialization. Assuming the invariant after $i-1$ types, Lemma 1 establishes the correct value for every sum while processing type $i$. Sums below $c_i$ cannot use the new coin and remain correct. $\square$

### Theorem

The algorithm outputs the number of unordered combinations summing to $x$.

#### Proof

After all $n$ types are processed, Lemma 2 says that $dp[x]$ counts every combination using the available denominations. Each multiset is introduced once according to the fixed type order, regardless of its permutations. Hence, the output is correct modulo $10^9+7$. $\square$

## Implementation

The exact nesting is crucial:

```cpp
for (int i = 0; i < n; i++) {
    for (int s = c[i]; s <= x; s++) {
```

Moving the sum loop outside counts ordered sequences as in Coin Combinations I. Iterating sums downward makes $dp[s-c_i]$ belong to the previous coin phase, allowing the current denomination at most once.

Sorting is unnecessary. The input order already supplies a fixed canonical order for introducing combinations.

After each modular addition, both values are below `MOD`; one subtraction is sufficient and the intermediate sum fits in `int`.

## Complexity

There are $n$ coin passes, each visiting at most $x$ sums, so the time complexity is $O(nx)$ and the memory complexity is $O(x)$.

## Worked Example

Let the coins be $\{2,3,5\}$ and $x=9$.

After coin $2$, each reachable even sum has one combination. During coin $3$, the increasing loop permits repeated threes: $dp[3]=1$, $dp[6]=2$, and $dp[9]=2$. The two combinations for $9$ are $3+3+3$ and $2+2+2+3$.

Finally, coin $5$ adds $dp[4]=1$ to $dp[9]$, corresponding to $2+2+5$. Thus, $dp[9]=3$.

## Takeaway

In one-dimensional knapsack DP, loop order is part of the state definition. Choice-first, increasing-sum updates count unlimited unordered combinations.

## Related Problems

Coin Combinations I places sums outside to count ordered sequences. Money Sums uses decreasing sums because each input coin may be used at most once.
