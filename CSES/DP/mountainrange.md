# Mountain Range

## Problem

- **Source:** [CSES 3314: Mountain Range](https://cses.fi/problemset/task/3314/)
- **Code:** [`View accepted C++ solution (mountainrange.cpp)`](./mountainrange.cpp)

There are $n$ mountains in a row. From mountain $a$, we may glide to mountain $b$ when $a$ is taller than $b$ and every mountain between them.

Find the maximum number of mountains that can be visited in one route.

## Idea

A direct graph would contain an edge from every mountain to every visible lower mountain. There may be $O(n^2)$ such pairs, so constructing all edges is too slow.

The important observation is that an optimal route never needs to skip the nearest strictly taller mountain.

For each position $i$, define

$$
l_i
$$

as the nearest index to the left of $i$ such that

$$
h_{l_i}>h_i,
$$

and define $r_i$ similarly on the right.

These indices can be found with monotonic stacks.

## Why Only the Nearest Taller Mountains Matter

Suppose a route reaches mountain $i$ from some mountain $p$ on its left.

Because $p$ can glide to $i$, $h_p$ is greater than every height between $p$ and $i$.

Let $l_i$ be the nearest strictly taller mountain to the left of $i$. Since $p$ itself is taller than $i$, $l_i$ exists between $p$ and $i$.

If $p\ne l_i$, then:

- $p$ can glide to $l_i$, because $p$ is taller than every mountain between $p$ and $i$;
- $l_i$ can glide to $i$, because every mountain between $l_i$ and $i$ has height at most $h_i<h_{l_i}$.

Therefore,

$$
p\rightarrow l_i\rightarrow i
$$

is valid and visits one more mountain than jumping directly from $p$ to $i$.

Consequently, in a longest route ending at $i$, the previous mountain must be either $l_i$ or $r_i$.

## Dynamic Programming

Let

$$
dp[i]
$$

be the maximum number of mountains in a route ending at mountain $i$.

The route may start at $i$, giving the initial value

$$
dp[i]=1.
$$

Its previous mountain can only be the nearest strictly taller mountain on either side, so

$$
dp[i]=1+\max(dp[l_i],dp[r_i]),
$$

where a missing neighbor contributes nothing.

Every transition goes from a taller mountain to a shorter one. We therefore process positions in decreasing order of height.

The answer is

$$
\max_i dp[i].
$$

## Finding Nearest Taller Mountains

Scan from left to right while maintaining indices whose heights are strictly decreasing.

Before inserting $i$, remove every stack element whose height is at most $h_i$:

```cpp
while (!st.empty() && h[st.back()] <= h[i]) st.pop_back();
```

The remaining top, if one exists, is the nearest mountain to the left that is strictly taller than $i$.

A second scan from right to left finds $r_i$.

Equal heights are removed because they are not strictly taller. A farther taller mountain may still glide over them.

## Correctness

We prove that the algorithm finds the maximum possible route length.

### Lemma

If a longest route ending at $i$ contains a previous mountain, that previous mountain is $l_i$ or $r_i$.

#### Proof

Suppose the previous mountain $p$ lies to the left. Since $p$ can glide to $i$, it is strictly taller than every mountain between them.

The nearest strictly taller mountain $l_i$ lies between $p$ and $i$. If $p\ne l_i$, then $p$ can glide to $l_i$, and $l_i$ can glide to $i$. Inserting $l_i$ creates a longer valid route, contradicting the optimality of the original route.

Thus, $p=l_i$. The argument for a previous mountain on the right is identical. $\square$

### Theorem

For every mountain $i$, $dp[i]$ equals the maximum length of a route ending at $i$.

#### Proof

Mountains are processed in decreasing height, so the DP values of $l_i$ and $r_i$ are already known.

A route may consist only of $i$, giving length 1. Otherwise, by the lemma, its previous mountain must be $l_i$ or $r_i$.

Appending $i$ to an optimal route ending at either valid predecessor gives

$$
dp[l_i]+1
$$

or

$$
dp[r_i]+1.
$$

Taking the maximum therefore considers every possible optimal route ending at $i$.

Hence, $dp[i]$ is correct for every position, and the largest DP value is the maximum number of mountains that can be visited. $\square$

## Complexity

Both monotonic-stack scans take

$$
O(n)
$$

time.

Sorting the positions by height takes

$$
O(n\log n).
$$

The DP phase takes $O(n)$, so the total time complexity is

$$
O(n\log n).
$$

The arrays and stacks use

$$
O(n)
$$

memory.

## Worked Example

Consider

$$
[20,15,17,35,25,40,12,19,13,12].
$$

Processing mountains from tallest to shortest gives, among others:

$$
dp[40]=1,
$$

$$
dp[35]=dp[40]+1=2,
$$

$$
dp[20]=dp[35]+1=3,
$$

$$
dp[17]=dp[20]+1=4,
$$

$$
dp[15]=dp[17]+1=5.
$$

This produces the route

$$
40\rightarrow35\rightarrow20\rightarrow17\rightarrow15.
$$

Therefore, the maximum number of visited mountains is

$$
5.
$$
