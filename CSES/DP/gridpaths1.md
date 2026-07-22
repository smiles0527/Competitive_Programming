# Grid Paths I

## Problem

- **Source:** [CSES 1638: Grid Paths I](https://cses.fi/problemset/task/1638/)
- **Code:** [`View accepted C++ solution (gridpaths1.cpp)`](./gridpaths1.cpp)

Given an $n\times n$ grid containing empty cells and traps, count the number of paths from the upper-left cell to the lower-right cell.

A path may move only right or down and cannot enter a trap.

The answer is printed modulo

$$
10^9+7.
$$

## Idea

For an empty cell $(i,j)$, the final move must come from one of two cells:

- $(i-1,j)$, directly above;
- $(i,j-1)$, directly to the left.

Therefore, the number of paths to $(i,j)$ is

$$
\operatorname{paths}[i][j]
=
\operatorname{paths}[i-1][j]
+
\operatorname{paths}[i][j-1].
$$

A trap has zero paths.

Only the previous row and the already processed part of the current row are needed, so the DP can be compressed into one array.

Let $dp[j]$ store the number of paths to column $j$.

While processing cell $(i,j)$:

- before the update, $dp[j]$ is the number of paths from above;
- after processing column $j-1$, $dp[j-1]$ is the number of paths from the left.

Thus, for an empty cell,

$$
dp[j]\mathrel{+}=dp[j-1].
$$

If the cell is a trap, set

$$
dp[j]=0.
$$

## Algorithm

Initialize

$$
dp[0]=1.
$$

Process the grid row by row and from left to right.

For every cell:

- if it is a trap, set its DP value to 0;
- otherwise, if it is not in the first column, add the value from the left.

After all rows have been processed, $dp[n-1]$ is the number of paths to the lower-right cell.

## Correctness

We prove that after processing cell $(i,j)$, $dp[j]$ equals the number of valid paths from the upper-left cell to $(i,j)$.

If $(i,j)$ is a trap, no valid path may enter it, and the algorithm sets $dp[j]=0$.

Otherwise, every path to $(i,j)$ must enter from above or from the left, since those are the only allowed movements.

Before the update, $dp[j]$ contains the number of paths to $(i-1,j)$. If $j>0$, $dp[j-1]$ has already been updated for the current row and contains the number of paths to $(i,j-1)$.

The algorithm adds these two values, so it counts every valid path to $(i,j)$. The two groups are disjoint because their final moves are different.

The initialization $dp[0]=1$ represents the single path beginning at the starting cell. If the starting cell is a trap, it is immediately changed to 0.

Therefore, after the entire grid is processed, $dp[n-1]$ is exactly the number of valid paths to the lower-right cell.

## Implementation

The grid does not need to be stored. Each row is processed immediately after it is read.

```cpp
vector<int> dp(n);
dp[0] = 1;
```

For an empty cell outside the first column:

```cpp
dp[j] += dp[j - 1];
if (dp[j] >= MOD) dp[j] -= MOD;
```

For a trap:

```cpp
dp[j] = 0;
```

Setting a trap to zero is necessary because its old value represents paths arriving from the row above, none of which may continue through the trap.

## Complexity

The algorithm processes every grid cell once, so the time complexity is

$$
O(n^2).
$$

The DP array contains $n$ integers, so the memory complexity is

$$
O(n).
$$

## Worked Example

Consider the grid

$$
\begin{matrix}
. & . & . & . \\
. & * & . & . \\
. & . & . & * \\
* & . & . & .
\end{matrix}
$$

After each row, the DP array is:

$$
[1,1,1,1]
$$

$$
[1,0,1,2]
$$

$$
[1,1,2,0]
$$

$$
[0,1,3,3]
$$

The final value is

$$
dp[3]=3,
$$

so there are 3 valid paths.
