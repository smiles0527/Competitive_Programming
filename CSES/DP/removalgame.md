# Removal Game

## Problem

- **Source:** [CSES 1097: Removal Game](https://cses.fi/problemset/task/1097/)
- **Code:** [`View accepted C++ solution (removalgame.cpp)`](./removalgame.cpp)

Two players alternately remove either the first or last number from an array. The removed value is added to that player's score.

Both players play optimally. Find the maximum score the first player can obtain.

The values may be negative.

## Approach

Trying to store only the first player's best score is awkward because whose turn it is changes after every move.

Instead, describe an interval from the perspective of the player whose turn it currently is.

Let

$$
dp[l][r]
$$

be the maximum score difference

$$
\text{current player's score}-\text{other player's score}
$$

that the current player can guarantee from the interval $[l,r]$.

If the current player removes $a_l$, the opponent becomes the current player on $[l+1,r]$. The opponent can obtain a score difference of

$$
dp[l+1][r].
$$

Therefore, the original player's final difference is

$$
a_l-dp[l+1][r].
$$

Similarly, removing $a_r$ gives

$$
a_r-dp[l][r-1].
$$

Hence,

$$
dp[l][r]=\max\left(a_l-dp[l+1][r],a_r-dp[l][r-1]\right).
$$

For an interval containing one value,

$$
dp[i][i]=a_i,
$$

because the current player takes that number and the opponent receives nothing.

## Recovering the First Player's Score

Let the total sum of the array be $S$, and let

$$
d=dp[0][n-1].
$$

If the first and second players finish with scores $p_1$ and $p_2$, then

$$
p_1+p_2=S
$$

and

$$
p_1-p_2=d.
$$

Adding the equations gives

$$
2p_1=S+d,
$$

so

$$
p_1=\frac{S+d}{2}.
$$

## Memory Optimization

The recurrence for an interval $[l,r]$ uses only

$$
dp[l+1][r]
$$

and

$$
dp[l][r-1].
$$

A one-dimensional array is enough.

Before updating `dp[l]` for interval $[l,r]$:

- `dp[l]` stores the answer for $[l,r-1]$;
- `dp[l+1]` stores the answer for $[l+1,r]$.

Intervals are processed by increasing length, and left endpoints are processed from left to right. This keeps both required shorter intervals available.

The update is

$$
dp[l]=\max(a_l-dp[l+1],a_r-dp[l]).
$$

## Correctness

We prove that $dp[l][r]$ equals the maximum score difference the current player can guarantee on interval $[l,r]$.

For $l=r$, the current player takes the only value $a_l$, so the score difference is exactly $a_l$.

Now consider an interval $[l,r]$ with more than one value.

The current player has exactly two legal moves.

If they take $a_l$, the opponent plays optimally on $[l+1,r]$ and achieves difference $dp[l+1][r]$ from their own perspective. Therefore, the original player's difference is

$$
a_l-dp[l+1][r].
$$

If they take $a_r$, the resulting difference is

$$
a_r-dp[l][r-1].
$$

The player chooses the move producing the larger difference, so

$$
dp[l][r]=\max\left(a_l-dp[l+1][r],a_r-dp[l][r-1]\right).
$$

Thus, the recurrence gives the optimal difference for every interval. For the full array, $dp[0][n-1]$ is the first player's final score minus the second player's final score. Combining this with the total sum gives the maximum first-player score.

## Complexity

There are

$$
O(n^2)
$$

intervals, and each transition takes constant time.

The time complexity is

$$
O(n^2).
$$

The compressed DP array uses

$$
O(n)
$$

memory.

## Worked Example

For

$$
[4,5,1,3],
$$

the length-one states are

$$
[4,5,1,3].
$$

For intervals of length 2:

$$
dp[0]=\max(4-5,5-4)=1,
$$

$$
dp[1]=\max(5-1,1-5)=4,
$$

$$
dp[2]=\max(1-3,3-1)=2.
$$

Continuing with longer intervals eventually gives

$$
dp[0]=3
$$

for the full array.

The total sum is

$$
S=4+5+1+3=13.
$$

Therefore, the first player's score is

$$
\frac{13+3}{2}=8.
$$
