# Counting Tilings

## Problem

- **Source:** [CSES 2181: Counting Tilings](https://cses.fi/problemset/task/2181/)
- **Code:** [`View accepted C++ solution (countingtilings.cpp)`](./countingtilings.cpp)

Count the number of ways to completely tile an $n\times m$ grid using:

* $1\times2$ horizontal dominoes;
* $2\times1$ vertical dominoes.

The answer is required modulo $10^9+7$. Since $n\le 10$, we can represent the state of one column using a bitmask.

## Idea

Process the grid from left to right, one column at a time. Horizontal dominoes may cross the boundary between two consecutive columns. Therefore, when processing a column, some of its cells may already be occupied by horizontal dominoes started in the previous column.

Represent these occupied cells using an $n$-bit mask. Bit $r$ is set when row $r$ of the current column is already filled.

For each current mask, fill every remaining cell in the column. A free cell has two possible placements:

1. Place a horizontal domino. It fills the current cell and extends into the same row of the next column, so that row is marked in the next mask.
2. Place a vertical domino. This is possible only if the cell directly below is also free. Both cells are filled inside the current column, so the next mask is unchanged.

Once the whole column is filled, the constructed next mask describes the cells already occupied in the following column.

## Dynamic Programming

Let $dp[\text{mask}]$ be the number of ways to tile all columns processed so far such that `mask` describes the cells occupied in the next column.

Initially, no columns have been processed and no cells are occupied:

$$dp[0]=1.$$

For every valid transition $\text{mask}\rightarrow\text{next}$, update

$$ndp[\text{next}]\mathrel{+}=dp[\text{mask}].$$

After processing all $m$ columns, the required state is $dp[0]$. A nonzero final mask would mean that some horizontal dominoes extend beyond the right edge of the grid.

## Generating Transitions

For every mask, recursively scan rows from top to bottom. Suppose the current row is $r$.

If bit $r$ is already set, the cell is occupied, so continue to row $r+1$. Otherwise, place either:

* a horizontal domino, setting bit $r$ in the next mask;
* a vertical domino, when row $r+1$ exists and is also free.

The vertical placement moves directly to row $r+2$, since both cells have been filled. When $r=n$, the current column is complete and the resulting next mask is stored.

## Correctness

### Transition correctness

For a fixed incoming mask, the recursive generation fills the first unoccupied cell. Every valid tiling of the current column must cover this cell using either a horizontal domino extending into the next column or a vertical domino covering the cell below. These are the only possible placements.

The recursion explores both whenever they are valid. Since it always processes the first remaining free cell, every completed placement of the current column is generated exactly once. Thus, the generated transitions are exactly the valid ways to fill one column for the given incoming mask.

### DP invariant

After processing $c$ columns, $dp[\text{mask}]$ equals the number of ways to tile those columns such that the horizontal dominoes extending into column $c$ occupy exactly the cells represented by `mask`.

This is true initially for $c=0$, because there is one empty tiling with mask $0$.

Assume the invariant holds before processing the next column. For each incoming mask, the transition generation considers every valid way to complete that column and produces the exact outgoing mask. Adding $dp[\text{mask}]$ to each resulting state therefore extends every existing partial tiling in every valid way.

No invalid tiling is added, and no valid tiling is missed or counted twice. After all $m$ columns, only mask $0$ represents a complete tiling contained entirely inside the grid. Therefore, $dp[0]$ is the required number of tilings.

## Implementation

The transition generation uses `gen(row, mask, next)`. A horizontal domino sets a bit in `next`:

```cpp
gen(row + 1, mask, next | (1 << row));
```

A vertical domino fills two current-column cells:

```cpp
if (row + 1 < n && !(mask & (1 << (row + 1)))) {
    gen(row + 2, mask, next);
}
```

All transitions are precomputed once and reused for every column.

## Complexity

There are $2^n$ masks. Across all masks, transition generation and processing require $O(3^n)$ work per column. The total time complexity is $O(m3^n)$.

The DP arrays contain $2^n$ values, while the stored transitions use $O(3^n)$ memory. Thus, the memory complexity is $O(3^n)$.

## Worked Example

Consider a $2\times3$ grid. From mask $00$, the column can be filled with one vertical domino, producing $00$, or two horizontal dominoes, producing $11$. From mask $11$, the column is already full, producing $00$.

Initially, $dp[00]=1$. After one column, $dp[00]=1$ and $dp[11]=1$. After two columns, $dp[00]=2$ and $dp[11]=1$. After three columns, $dp[00]=3$.

Therefore, a $2\times3$ grid has $3$ domino tilings.
