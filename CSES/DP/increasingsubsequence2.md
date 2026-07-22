# Increasing Subsequence II

## Problem

- **Source:** [CSES 1748: Increasing Subsequence II](https://cses.fi/problemset/task/1748/)
- **Code:** [`View accepted C++ solution (increasingsubsequence2.cpp)`](./increasingsubsequence2.cpp)

Given an array of $n$ integers, count all nonempty strictly increasing subsequences.

Subsequences using different positions are counted separately, even when their values are equal. The answer is required modulo $10^9+7$.

## Idea

Let $dp[i]$ be the number of increasing subsequences whose final element is $a_i$.

The one-element subsequence $[a_i]$ always contributes one possibility. Any longer subsequence ending at $i$ must previously end at some position $j<i$ satisfying $a_j<a_i$.

Appending $a_i$ to each such subsequence gives

$$dp[i]=1+\sum_{\substack{j<i\\a_j<a_i}}dp[j].$$

Calculating this sum by checking every earlier position would take $O(n^2)$, which is too slow for $n\le2\cdot10^5$. We need to maintain the total number of subsequences ending at values smaller than the current value.

## Coordinate Compression

The values may be as large as $10^9$, so they cannot be used directly as Fenwick tree indices.

Sort all distinct values and assign them ranks $1,2,\dots,k$. The ranks preserve comparisons:

$$a_i<a_j\quad\Longleftrightarrow\quad\operatorname{rank}(a_i)<\operatorname{rank}(a_j).$$

Equal values receive the same rank.

## Fenwick Tree

The Fenwick tree stores, for every compressed value, the total number of increasing subsequences processed so far that end at that value.

Suppose $a_i$ has compressed position $p$. The number of subsequences ending at a strictly smaller value is the prefix sum $\operatorname{query}(p-1)$.

Therefore,

$$dp[i]=1+\operatorname{query}(p-1).$$

After calculating this value, add it at position $p$:

$$\operatorname{add}(p,dp[i]).$$

Querying $p-1$, rather than $p$, is essential because equal values cannot follow one another in a strictly increasing subsequence.

## Algorithm

1. Read the array.
2. Coordinate-compress all values.
3. Initialize an empty Fenwick tree.
4. Process the array from left to right.
5. For each value with compressed position $p$:

   * calculate $cur=1+\operatorname{query}(p-1)$;
   * add `cur` at position $p$.

6. The sum over the entire Fenwick tree is the number of nonempty increasing subsequences.

## Correctness

We prove that the algorithm counts every increasing subsequence exactly once.

When processing position $i$, the Fenwick tree contains only information from positions before $i$.

The prefix query at $p-1$ returns the sum of $dp[j]$ over exactly those earlier positions satisfying $a_j<a_i$. Appending $a_i$ to any of these subsequences creates a valid strictly increasing subsequence ending at $i$.

The additional $1$ counts the subsequence consisting only of $a_i$.

Conversely, every increasing subsequence ending at $i$ is either the one-element subsequence $[a_i]$, or has a unique previous final position $j<i$ with $a_j<a_i$. It is therefore counted by exactly one term in the recurrence.

Thus, the value added for position $i$ equals the number of increasing subsequences ending there. Every nonempty increasing subsequence has one unique final position, so summing all stored values counts every valid subsequence exactly once.

## Implementation

Equal values are compressed to the same position:

```cpp
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());
```

The compressed position is found with

```cpp
int p = lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
```

Fenwick trees use one-based indexing, which explains the added $1$.

For each element:

```cpp
int cur = get(p - 1) + 1;
add(p, cur);
```

The array is processed from left to right, so only subsequences respecting the original position order are counted.

## Complexity

Coordinate compression takes $O(n\log n)$. Each element performs one Fenwick tree query and one update, each taking $O(\log n)$.

Thus, the total time complexity is $O(n\log n)$. The compressed array and Fenwick tree use $O(n)$ memory.

## Worked Example

For $a=[3,1,4,2]$, coordinate compression maps the values $1,2,3,4$ to ranks $1,2,3,4$, so the array of ranks is $[3,1,4,2]$.

The Fenwick transitions are:

* for $3$: $cur=query(2)+1=1$;
* for $1$: $cur=query(0)+1=1$;
* for $4$: $cur=query(3)+1=1+1+1=3$;
* for $2$: $cur=query(1)+1=1+1=2$.

The total is $1+1+3+2=7$. These are the four singleton subsequences together with $[3,4]$, $[1,4]$, and $[1,2]$.
