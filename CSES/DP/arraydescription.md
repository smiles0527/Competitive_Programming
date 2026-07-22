# Array Description

## Problem

- **Source:** [CSES 1746: Array Description](https://cses.fi/problemset/task/1746/)
- **Code:** [`View accepted C++ solution (arraydescription.cpp)`](./arraydescription.cpp)

Count arrays of length $n$ whose elements lie from $1$ through $m$ and whose neighboring elements differ by at most one.

Some positions are fixed, while value zero means that any value is allowed. Return the answer modulo $10^9+7$.

## Idea

The validity of the next position depends only on the previous value.

Let $dp[v]$ be the number of valid prefixes processed so far whose final value is $v$.

If the next position contains $v$, the previous value can only be $v-1$, $v$, or $v+1$. Therefore,

$$ndp[v]=dp[v-1]+dp[v]+dp[v+1].$$

If the current position is fixed to $x_i$, only $ndp[x_i]$ is allowed. Otherwise, every value from $1$ through $m$ is calculated.

## Initialization

For the first position:

* if $x_1$ is fixed, there is one prefix ending in $x_1$;
* if $x_1=0$, every value from $1$ through $m$ creates one valid prefix.

Thus, $dp[v]=1$ for every allowed first value and zero otherwise.

## Algorithm

Maintain two arrays `dp` and `ndp`, indexed from $1$ through $m$.

For every position after the first:

1. Clear `ndp`.
2. Determine the allowed values at the current position.
3. For every allowed $v$, compute $ndp[v]=dp[v-1]+dp[v]+dp[v+1]$ modulo $10^9+7$.
4. Replace `dp` with `ndp`.

Finally, sum $dp[v]$ over $1\le v\le m$.

## Correctness

We prove that after processing position $i$, $dp[v]$ equals the number of valid prefixes of length $i+1$ whose last value is $v$.

The initialization is correct because each allowed first value produces exactly one prefix of length one.

Assume the claim before processing the next position. A valid prefix ending in $v$ must previously end in $v-1$, $v$, or $v+1$. By the induction hypothesis, the numbers of such prefixes are $dp[v-1]$, $dp[v]$, and $dp[v+1]$.

Appending $v$ to any of them preserves the adjacent-difference condition. No other previous value can be followed by $v$, and the three groups are disjoint because their previous values differ. Hence,

$$ndp[v]=dp[v-1]+dp[v]+dp[v+1]$$

counts every valid prefix ending in $v$ exactly once.

The algorithm calculates this state only when $v$ agrees with the given description. Therefore, after all positions are processed, summing over all final values counts exactly all valid arrays.

## Implementation

The arrays have size $m+2$. Indices zero and $m+1$ remain zero, so the same transition handles boundaries $1$ and $m$:

```cpp
ndp[v] = dp[v - 1] + dp[v] + dp[v + 1];
```

Only two rows are required because the current position depends solely on the previous position.

When a position is fixed, the loop handles only that value:

```cpp
int l = 1, r = m;
if (a[i]) l = r = a[i];
```

## Complexity

Each of the $n$ positions considers at most $m$ values, so the time complexity is $O(nm)$ and the two DP arrays use $O(m)$ space.

## Worked Example

For $n=3$, $m=5$, and description $[2,0,2]$, the first position must be $2$:

$$dp=[0,1,0,0,0].$$

The second position may be $1$, $2$, or $3$:

$$dp=[1,1,1,0,0].$$

The final value must be $2$, giving $dp[1]+dp[2]+dp[3]=3$. The valid arrays are $[2,1,2]$, $[2,2,2]$, and $[2,3,2]$.

Thus, the answer is $3$.
