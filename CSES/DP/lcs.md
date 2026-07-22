# Longest Common Subsequence

## Problem

- **Source:** [CSES 3403: Longest Common Subsequence](https://cses.fi/problemset/task/3403/)
- **Code:** [`View accepted C++ solution (lcs.cpp)`](./lcs.cpp)

Given two integer arrays $a$ and $b$, find their longest common subsequence.

A subsequence preserves the original order but may skip elements. The output must contain both the maximum possible length and one subsequence attaining that length.

## Idea

Consider prefixes of the two arrays.

Define

$$
dp[i][j]
$$

as the length of the longest common subsequence between

$$
a_1,a_2,\dots,a_i
$$

and

$$
b_1,b_2,\dots,b_j.
$$

We decide what happens with the final elements of these prefixes.

If

$$
a_i=b_j,
$$

the matching value can be appended to a common subsequence of the preceding prefixes. Therefore,

$$
dp[i][j]=dp[i-1][j-1]+1.
$$

If

$$
a_i\ne b_j,
$$

they cannot both be matched together. Any common subsequence must omit at least one of them, so

$$
dp[i][j]=\max(dp[i-1][j],dp[i][j-1]).
$$

The base cases are

$$
dp[0][j]=0,\qquad dp[i][0]=0,
$$

because an empty array has no nonempty common subsequence with another array.

## Algorithm

Fill the DP table in increasing order of $i$ and $j$.

After the table is complete, $dp[n][m]$ is the LCS length.

To reconstruct a sequence, start from $(n,m)$:

- if $a_{i-1}=b_{j-1}$, include this value and move diagonally to $(i-1,j-1)$;
- otherwise, move to whichever of $(i-1,j)$ and $(i,j-1)$ has the larger DP value.

The values are collected from right to left, so reverse them before printing.

## Correctness

We prove that $dp[i][j]$ is the length of the longest common subsequence of the first $i$ elements of $a$ and the first $j$ elements of $b$.

If either prefix is empty, the longest common subsequence has length 0, matching the initialization.

Now consider positive $i$ and $j$.

If $a_i=b_j$, append this common value to an LCS of the prefixes ending at $i-1$ and $j-1$. This produces a common subsequence of length

$$
dp[i-1][j-1]+1.
$$

No longer common subsequence is possible, because after using the matching final elements, all earlier selected elements must come from those preceding prefixes.

If $a_i\ne b_j$, no common subsequence can match these two final elements together. It must omit $a_i$, omit $b_j$, or omit both. These possibilities are covered by

$$
dp[i-1][j]
$$

and

$$
dp[i][j-1].
$$

Taking their maximum therefore gives the optimal length.

Thus, every DP state is correct, and $dp[n][m]$ is the LCS length.

During reconstruction, a diagonal move records a value present at the current position in both arrays. Otherwise, the algorithm moves to a neighboring state with the same optimal value. Therefore, it remains on a path representing an optimal solution until reaching an empty prefix.

The recorded values form a common subsequence of length $dp[n][m]$, so the produced sequence is optimal.

## Implementation

The full table is retained because reconstruction needs to compare neighboring states.

```cpp
if (a[i - 1] == b[j - 1]) {
    dp[i][j] = dp[i - 1][j - 1] + 1;
} else {
    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
}
```

During reconstruction, equal neighboring values may allow either direction. Choosing the upper state when the values are tied still preserves the optimal LCS length.

The sequence is found backwards:

```cpp
if (a[i - 1] == b[j - 1]) {
    ans.push_back(a[i - 1]);
    i--;
    j--;
}
```

It is reversed before being printed.

## Complexity

The table contains

$$
(n+1)(m+1)
$$

states, each calculated in constant time.

The time complexity is

$$
O(nm).
$$

The DP table uses

$$
O(nm)
$$

memory.

## Worked Example

Consider

$$
a=[3,1,3,2,7,4,8,2]
$$

and

$$
b=[6,5,1,2,3,4].
$$

The table gives

$$
dp[8][6]=3.
$$

During reconstruction, one possible sequence of matches is:

- match 4 in both arrays;
- move backwards and match 2;
- move backwards and match 1.

These values are discovered in reverse order:

$$
[4,2,1].
$$

After reversing, the resulting longest common subsequence is

$$
[1,2,4].
$$

Its length is

$$
3.
$$
