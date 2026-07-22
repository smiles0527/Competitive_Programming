# Rectangle Cutting

## Problem

- **Source:** [CSES 1744: Rectangle Cutting](https://cses.fi/problemset/task/1744/)
- **Code:** [`View accepted C++ solution (rectanglecutting.cpp)`](./rectanglecutting.cpp)

Given an $a\times b$ rectangle, cut it into squares using the minimum number of cuts.

Each cut must divide one rectangle into two smaller rectangles, and all side lengths must remain integers.

## Idea

Let

$$
dp[h][w]
$$

be the minimum number of cuts needed to divide an $h\times w$ rectangle into squares.

If

$$
h=w,
$$

the rectangle is already a square, so

$$
dp[h][w]=0.
$$

Otherwise, consider the first cut.

A horizontal cut after $k$ rows creates two rectangles:

$$
k\times w
$$

and

$$
(h-k)\times w.
$$

The total number of cuts is

$$
dp[k][w]+dp[h-k][w]+1.
$$

A vertical cut after $k$ columns creates

$$
h\times k
$$

and

$$
h\times(w-k),
$$

giving

$$
dp[h][k]+dp[h][w-k]+1.
$$

Trying every possible first cut gives the recurrence

$$
dp[h][w]=\min\left(
\min_{1\le k<h}\left(dp[k][w]+dp[h-k][w]+1\right),
\min_{1\le k<w}\left(dp[h][k]+dp[h][w-k]+1\right)
\right).
$$

## Algorithm

Process rectangle sizes in increasing order.

For every $h$ from 1 to $a$ and every $w$ from 1 to $b$:

- if $h=w$, set $dp[h][w]=0$;
- otherwise, try every horizontal cut;
- try every vertical cut;
- store the minimum result.

The smaller rectangles created by every cut have either smaller height or smaller width, so their DP values have already been computed.

## Correctness

We prove that $dp[h][w]$ is the minimum number of cuts needed to divide an $h\times w$ rectangle into squares.

If $h=w$, the rectangle is already a square, and zero cuts are optimal.

Now suppose $h\ne w$. Any valid solution must begin with either a horizontal or vertical cut.

For a horizontal cut at position $k$, the two resulting rectangles are independent. Dividing both optimally requires

$$
dp[k][w]+dp[h-k][w]
$$

additional cuts, together with the first cut.

The same reasoning applies to every vertical cut.

The algorithm checks every possible position of the first cut and uses optimal solutions for both resulting rectangles. Therefore, every valid first move is considered, and the minimum among them is the optimal answer.

Thus, $dp[a][b]$ is the minimum number of cuts required.

## Implementation

The DP table is initialized automatically to zero, which correctly handles square rectangles.

For nonsquare rectangles, the value is first set to a large number:

```cpp
dp[h][w] = 1e9;
```

Horizontal cuts are tried using

```cpp
for (int k = 1; k < h; k++)
```

and vertical cuts similarly use every $k$ from 1 to $w-1$.

## Complexity

For each of the $ab$ rectangle sizes, the algorithm tries at most $a+b$ cuts.

The time complexity is

$$
O(ab(a+b)).
$$

The DP table uses

$$
O(ab)
$$

memory.

## Worked Example

Consider a $3\times5$ rectangle.

One optimal sequence is:

1. Cut it into a $3\times3$ square and a $3\times2$ rectangle.
2. Cut the $3\times2$ rectangle into a $2\times2$ square and a $1\times2$ rectangle.
3. Cut the $1\times2$ rectangle into two $1\times1$ squares.

This uses 3 cuts, so

$$
dp[3][5]=3.
$$
