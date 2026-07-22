# Book Shop

## Problem

- **Source:** [CSES 1158: Book Shop](https://cses.fi/problemset/task/1158/)
- **Code:** [`View accepted C++ solution (bookshop.cpp)`](./bookshop.cpp)

There are $n$ books. Book $i$ has price $h_i$ and contains $s_i$ pages.

Choose books whose total price is at most $x$, maximizing the total number of pages. Each book may be bought at most once.

## Idea

This is a 0/1 knapsack problem.

Let

$$
dp[c]
$$

be the maximum number of pages obtainable with total price at most $c$, using only the books processed so far.

When processing book $i$, there are two choices for capacity $c$:

- do not buy the book, keeping $dp[c]$;
- buy it, gaining $s_i$ pages in addition to the best result for capacity $c-h_i$.

Therefore,

$$
dp[c]=\max\left(dp[c],dp[c-h_i]+s_i\right).
$$

The update is valid when

$$
c\ge h_i.
$$

## Update Order

Capacities must be processed in decreasing order:

$$
x,x-1,\dots,h_i.
$$

Before updating $dp[c]$, the value $dp[c-h_i]$ must still represent a solution using only earlier books.

If capacities were processed in increasing order, $dp[c-h_i]$ might already include the current book. The transition could then use the same book multiple times, which is not allowed.

## Algorithm

Initialize every DP value to 0.

For each book $i$:

- process capacities from $x$ down to $h_i$;
- update

  $$
  dp[c]=\max(dp[c],dp[c-h_i]+s_i).
  $$

After all books are processed, output $dp[x]$.

## Correctness

We prove that after processing the first $i$ books, $dp[c]$ is the maximum number of pages obtainable with price at most $c$.

Before any books are processed, buying nothing gives 0 pages for every capacity, so the initialization is correct.

Consider book $i$. Any optimal selection for capacity $c$ belongs to one of two cases.

If it does not contain book $i$, its page count is already represented by the previous value of $dp[c]$.

If it contains book $i$, removing that book leaves a selection of earlier books costing at most

$$
c-h_i.
$$

The maximum number of pages for that remaining capacity is $dp[c-h_i]$, so this case gives

$$
dp[c-h_i]+s_i.
$$

Taking the maximum of these two possibilities gives the optimal result for capacity $c$.

Because capacities are processed in decreasing order, $dp[c-h_i]$ has not yet been updated using book $i$. Thus, the current book is used at most once.

Therefore, after all books are processed, $dp[x]$ is the maximum number of pages obtainable within the budget.

## Implementation

The DP array has $x+1$ entries:

```cpp
vector<int> dp(x + 1);
```

For each book, the capacities are updated backwards:

```cpp
for (int c = x; c >= h[i]; c--) {
    dp[c] = max(dp[c], dp[c - h[i]] + s[i]);
}
```

No impossible-state marker is needed because every capacity allows the empty selection with 0 pages.

## Complexity

For each of the $n$ books, at most $x$ capacities are processed.

The time complexity is

$$
O(nx).
$$

The DP array uses

$$
O(x)
$$

memory.

## Worked Example

Suppose

$$
h=[4,8,5,3]
$$

and

$$
s=[5,12,8,1],
$$

with budget

$$
x=10.
$$

After processing the first book, price 4 and 5 pages, every capacity from 4 to 10 can obtain 5 pages.

After processing the second book, buying the book of price 8 gives 12 pages for capacities 8, 9, and 10.

When processing the third book, price 5 and 8 pages, capacity 9 is updated using

$$
dp[9]=\max(dp[9],dp[4]+8).
$$

Since $dp[4]=5$,

$$
dp[9]=13.
$$

This corresponds to buying books 1 and 3, whose total price is

$$
4+5=9
$$

and whose total pages are

$$
5+8=13.
$$

No later update produces more pages within budget 10, so the answer is

$$
13.
$$
