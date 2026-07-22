# Two Sets II

## Problem

- **Source:** [CSES 1093: Two Sets II](https://cses.fi/problemset/task/1093/)
- **Code:** [`View accepted C++ solution (twosetsII.cpp)`](./twosetsII.cpp)

Count the number of ways to divide the numbers

$$
1,2,\dots,n
$$

into two sets with equal sums.

The two sets are unordered, so swapping them does not create a new solution.

## Idea

The total sum is

$$
S=\frac{n(n+1)}{2}.
$$

If $S$ is odd, it cannot be divided into two equal integer sums, so the answer is 0.

Otherwise, each set must have sum

$$
T=\frac{S}{2}.
$$

A direct subset-sum DP over all numbers would count every partition twice: once by choosing the first set and once by choosing its complement.

Instead, count only subsets that do not contain $n$.

Every valid partition has exactly one set not containing $n$, because $n$ belongs to exactly one of the two sets. Therefore, valid partitions correspond one-to-one with subsets of

$$
\{1,2,\dots,n-1\}
$$

whose sum is $T$.

Let

$$
dp[s]
$$

be the number of subsets of the processed numbers whose sum is $s$.

Initially,

$$
dp[0]=1,
$$

representing the empty subset.

When processing a number $x$,

$$
dp[s]\mathrel{+}=dp[s-x].
$$

The sums are processed in decreasing order so that $x$ is used at most once.

## Algorithm

1. Calculate $S=n(n+1)/2$.
2. If $S$ is odd, print 0.
3. Set $T=S/2$.
4. Initialize $dp[0]=1$.
5. Process each number $x=1,2,\dots,n-1$.
6. For $s$ from $T$ down to $x$, update

   $$
   dp[s]\mathrel{+}=dp[s-x].
   $$

7. Output $dp[T]$.

## Correctness

We prove that the algorithm outputs the number of equal-sum partitions.

After processing numbers 1 through $x$, $dp[s]$ equals the number of subsets of those numbers with sum $s$.

For each number $x$, a subset with sum $s$ either excludes $x$, in which case it was already counted by $dp[s]$, or includes $x$, in which case removing $x$ leaves a subset with sum $s-x$. Thus,

$$
dp[s]\mathrel{+}=dp[s-x]
$$

counts all valid subsets.

The decreasing update order prevents the same number from being selected more than once.

Now consider equal-sum partitions of $\{1,\dots,n\}$. In every partition, exactly one of the two sets excludes $n$. That set has sum $T$ and is counted by the DP.

Conversely, every subset of $\{1,\dots,n-1\}$ with sum $T$ determines one valid partition: the subset and its complement.

Therefore, $dp[T]$ counts every partition exactly once.

## Complexity

The target sum is

$$
T=O(n^2).
$$

For each of the $n-1$ numbers, the algorithm processes at most $T$ sums.

The time complexity is

$$
O(nT)=O(n^3).
$$

The DP array uses

$$
O(T)=O(n^2)
$$

memory.

## Worked Example

For $n=7$,

$$
S=\frac{7\cdot8}{2}=28,\qquad T=14.
$$

We count subsets of

$$
\{1,2,3,4,5,6\}
$$

with sum 14.

They are

$$
\{1,3,4,6\},
$$

$$
\{1,2,5,6\},
$$

$$
\{2,3,4,5\},
$$

$$
\{3,5,6\}.
$$

Each determines one partition when paired with its complement, so the answer is

$$
4.
$$
