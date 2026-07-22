# Edit Distance

## Problem

- **Source:** [CSES 1639: Edit Distance](https://cses.fi/problemset/task/1639/)
- **Code:** [`View accepted C++ solution (editdistance.cpp)`](./editdistance.cpp)

Given two strings $a$ and $b$, find the minimum number of operations needed to transform $a$ into $b$.

The allowed operations are:

- insert one character;
- delete one character;
- replace one character.

## Operations Allowed

The allowed transformations are inserting one character, deleting one character, or replacing one character.

## Idea

Let

$$
dp[i][j]
$$

be the minimum number of operations needed to transform the first $i$ characters of $a$ into the first $j$ characters of $b$.

Consider the final characters of these prefixes.

If

$$
a[i-1]=b[j-1],
$$

they can be matched without an operation:

$$
dp[i][j]=dp[i-1][j-1].
$$

Otherwise, the final operation has three possibilities.

### Delete

Delete $a[i-1]$. The remaining problem is transforming the first $i-1$ characters of $a$ into the first $j$ characters of $b$:

$$
dp[i-1][j]+1.
$$

### Insert

Insert $b[j-1]$ at the end. Before this insertion, the first $i$ characters of $a$ must already match the first $j-1$ characters of $b$:

$$
dp[i][j-1]+1.
$$

### Replace

Replace $a[i-1]$ with $b[j-1]$. The preceding prefixes must already match:

$$
dp[i-1][j-1]+1.
$$

Thus, when the characters differ,

$$
dp[i][j]=1+\min\left(dp[i-1][j],dp[i][j-1],dp[i-1][j-1]\right).
$$

## Base Cases

Transforming an empty string into a prefix of length $j$ requires $j$ insertions:

$$
dp[0][j]=j.
$$

Transforming a prefix of length $i$ into an empty string requires $i$ deletions:

$$
dp[i][0]=i.
$$

## Memory Optimization

Each row depends only on the previous row and the current row, so storing the full $n\times m$ table is unnecessary.

Use a one-dimensional array where, while processing row $i$:

- `dp[j]` before the update represents $dp[i-1][j]$;
- `dp[j-1]` represents $dp[i][j-1]$;
- `prev` represents $dp[i-1][j-1]$.

The old value of `dp[j]` is saved before overwriting it so that it becomes the diagonal value for the next column.

## Algorithm

Initialize

$$
dp[j]=j
$$

for every $0\le j\le m$.

For every prefix length $i$ of the first string:

1. Store the old $dp[0]$ as the diagonal value.
2. Set $dp[0]=i$.
3. Process the second string from left to right.
4. If the current characters match, copy the diagonal value.
5. Otherwise, take one plus the minimum of deletion, insertion, and replacement.

After all rows are processed, $dp[m]$ is the edit distance.

## Correctness

We prove that after processing row $i$, $dp[j]$ equals the minimum number of operations needed to transform the first $i$ characters of $a$ into the first $j$ characters of $b$.

The initialization is correct because transforming the empty prefix into a prefix of length $j$ requires exactly $j$ insertions.

For a state $(i,j)$, suppose the final characters are equal. An optimal transformation does not need to modify them, so the answer equals the edit distance of the preceding prefixes:

$$
dp[i-1][j-1].
$$

If the characters differ, the final operation must be a deletion, insertion, or replacement. The recurrence considers all three possibilities and adds one operation to the optimal solution of the resulting smaller prefixes.

Every value considered by the recurrence represents a valid transformation. Conversely, every valid transformation must finish with one of these operations. Taking the minimum therefore gives the optimal edit distance.

Thus, after processing both complete strings, $dp[m]$ is the required answer.

## Implementation

The important part of the one-row implementation is preserving the previous diagonal value:

```cpp
int old = dp[j];

if (a[i - 1] == b[j - 1]) {
    dp[j] = prev;
} else {
    dp[j] = 1 + min(prev, min(dp[j], dp[j - 1]));
}

prev = old;
```

Here:

- `old` is $dp[i-1][j]$;
- `prev` is $dp[i-1][j-1]$;
- `dp[j-1]` is $dp[i][j-1]$.

All answers are at most $\max(n,m)$, so `int` is sufficient.

## Complexity

There are $nm$ states, and each state is processed in constant time.

The time complexity is

$$
O(nm).
$$

The one-dimensional DP array uses

$$
O(m)
$$

memory.

## Worked Example

For

$$
a=\text{LOVE},\qquad b=\text{MOVIE},
$$

one optimal transformation is

$$
\text{LOVE}\rightarrow\text{MOVE}\rightarrow\text{MOVIE}.
$$

The first operation replaces `L` with `M`, and the second inserts `I`.

Therefore, the edit distance is

$$
2.
$$
