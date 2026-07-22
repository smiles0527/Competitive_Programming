# Projects

## Problem

- **Source:** [CSES 1140: Projects](https://cses.fi/problemset/task/1140/)
- **Code:** [`View accepted C++ solution (projects.cpp)`](./projects.cpp)

There are $n$ projects. Project $i$ starts on day $a_i$, ends on day $b_i$, and gives reward $p_i$.

Only one project can be attended during any day. Find the maximum total reward.

Since both endpoints are occupied, two projects are compatible only when one ends strictly before the other begins.

## Idea

Sort the projects by ending day.

Let

$$
dp[i]
$$

be the maximum reward obtainable using the first $i$ projects in the sorted order.

Consider project $i$, using zero-based indexing in the implementation.

There are two choices.

### Skip the project

The reward remains

$$
dp[i].
$$

### Attend the project

We receive reward $p_i$. Any earlier selected project must end before day $a_i$.

Because projects are sorted by ending day, binary search finds the first earlier project whose ending day is at least $a_i$. Let its index be $j$. Then exactly the first $j$ projects end strictly before $a_i$.

The best reward when attending project $i$ is therefore

$$
dp[j]+p_i.
$$

Thus,

$$
dp[i+1]=\max(dp[i],dp[j]+p_i).
$$

## Algorithm

1. Sort all projects by ending day.
2. Store their ending days in a separate sorted array.
3. Set $dp[0]=0$.
4. For each project $i$:

   * use `lower_bound` to find the number $j$ of earlier projects with ending day smaller than $a_i$;
   * update

$$
dp[i+1]=\max(dp[i],dp[j]+p_i).
$$

5. Output $dp[n]$.

## Correctness

We prove that $dp[i]$ is the maximum reward obtainable using the first $i$ projects.

The base case $dp[0]=0$ is correct because no reward can be earned without projects.

Now consider project $i$. Any optimal selection among the first $i+1$ projects either excludes project $i$ or includes it.

If it excludes project $i$, its reward is at most $dp[i]$.

If it includes project $i$, every other selected project must end before $a_i$. The binary search finds exactly the first $j$ projects satisfying this condition. Their maximum possible reward is $dp[j]$, so the total reward is

$$
dp[j]+p_i.
$$

The transition takes the maximum of these two complete possibilities. Therefore, $dp[i+1]$ is optimal.

By induction, $dp[n]$ is the maximum reward obtainable from all projects.

## Implementation

The projects are sorted by ending day:

```cpp
sort(v.begin(), v.end(), [](const Project& x, const Project& y) {
    return x.b < y.b;
});
```

For project $i$,

```cpp
int j = lower_bound(ends.begin(), ends.begin() + i, v[i].a) - ends.begin();
```

finds the first ending day satisfying

$$
b_j\ge a_i.
$$

Therefore, indices before $j$ have

$$
b<a_i
$$

and are compatible with the current project.

`long long` is required because the total reward may be as large as

$$
2\cdot10^5\cdot10^9=2\cdot10^{14}.
$$

## Complexity

Sorting takes

$$
O(n\log n).
$$

Each project performs one binary search, also giving total time

$$
O(n\log n).
$$

The arrays use

$$
O(n)
$$

memory.

## Worked Example

Consider the projects

$$
(2,4,4),\quad (3,6,6),\quad (6,8,2),\quad (5,7,3).
$$

After sorting by ending day:

$$
(2,4,4),\quad (3,6,6),\quad (5,7,3),\quad (6,8,2).
$$

For project $(2,4,4)$, no earlier project is compatible:

$$
dp[1]=4.
$$

For $(3,6,6)$, the first project overlaps with it:

$$
dp[2]=\max(4,6)=6.
$$

For $(5,7,3)$, project $(2,4,4)$ ends before day $5$, so

$$
dp[3]=\max(6,4+3)=7.
$$

For $(6,8,2)$, only projects ending before day $6$ may precede it. The best result remains

$$
7.
$$

Therefore, the maximum reward is

$$
7.
$$
