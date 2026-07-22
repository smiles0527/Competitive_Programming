# Increasing Subsequence

## Problem

- **Source:** [CSES 1145: Increasing Subsequence](https://cses.fi/problemset/task/1145/)
- **Code:** [`View accepted C++ solution (increasingsubsequence.cpp)`](./increasingsubsequence.cpp)

Given an array of $n$ integers, find the length of its longest strictly increasing subsequence.

A subsequence preserves the original order but may skip elements.

## Idea

A direct dynamic programming solution could define

$$
dp[i]
$$

as the longest increasing subsequence ending at position $i$. It would check every earlier position, resulting in

$$
O(n^2),
$$

which is too slow for $n\le2\cdot10^5$.

Instead, maintain an array `tail` where

$$
\text{tail}[k]
$$

is the smallest possible ending value of an increasing subsequence of length $k+1$ found so far.

A smaller ending value is always at least as useful as a larger one because it allows more future values to extend the subsequence.

For each value $x$, find the first position $p$ such that

$$
\text{tail}[p]\ge x.
$$

If such a position exists, replace it with $x$. Otherwise, append $x$.

The array `tail` remains sorted, so this position can be found using `lower_bound`.

## Algorithm

Start with an empty `tail` array.

For each array value $x$:

1. Find the first index $p$ with `tail[p] >= x`.
2. If $p$ is outside the array, append $x$.
3. Otherwise, set `tail[p] = x`.

After processing all values, the size of `tail` is the LIS length.

## Correctness

After processing any prefix of the input, `tail[k]` is the smallest possible ending value of an increasing subsequence of length $k+1$.

When processing $x$, suppose `lower_bound` returns position $p$.

All values before $p$ are strictly smaller than $x$. Therefore, an increasing subsequence of length $p$ ending at `tail[p-1]` can be extended by $x$, producing a subsequence of length $p+1$.

Replacing `tail[p]` with $x$ does not remove the existence of a subsequence of that length. It only gives that length a smaller or equal ending value.

If no position has value at least $x$, then $x$ is larger than the final value of the longest subsequence found so far, so it extends that subsequence by one.

Thus, `tail` stores one valid best ending value for every attainable subsequence length, and its size is exactly the longest increasing subsequence length.

## Implementation

The search uses

```cpp
lower_bound(tail.begin(), tail.end(), x)
```

rather than `upper_bound`.

`lower_bound` replaces the first value greater than or equal to $x$, so equal values do not increase the subsequence length. This matches the requirement that every next element must be strictly larger.

The original array does not need to be stored because each value is processed once.

## Complexity

Each of the $n$ values performs one binary search in `tail`.

The time complexity is

$$
O(n\log n).
$$

The `tail` array contains at most $n$ values, so the memory complexity is

$$
O(n).
$$

## Worked Example

For

$$
[7,3,5,3,6,2,9,8],
$$

the `tail` array changes as follows:

$$
[7]
$$

$$
[3]
$$

$$
[3,5]
$$

$$
[3,5]
$$

$$
[3,5,6]
$$

$$
[2,5,6]
$$

$$
[2,5,6,9]
$$

$$
[2,5,6,8].
$$

Its final length is

$$
4,
$$

so the longest increasing subsequence has length 4.
