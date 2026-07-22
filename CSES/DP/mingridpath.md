# Minimal Grid Path

## Problem

- **Code:** [`View accepted C++ solution (mingridpath.cpp)`](./mingridpath.cpp)

An $n\times n$ grid contains uppercase letters. Starting from the upper-left cell, move only right or down until reaching the lower-right cell.

The letters of the visited cells form a string of length

$$
2n-1.
$$

Find the lexicographically smallest possible string.

## Idea

Every move increases the sum of the coordinates by one. Therefore, every path visits exactly one cell from each diagonal

$$
i+j=d.
$$

Suppose we have already constructed the smallest possible prefix ending on diagonal $d$. There may be several cells reachable with that same prefix, so keeping only one cell would be unsafe: different cells may allow different future suffixes.

Instead, maintain all cells reachable with the current smallest prefix.

From these cells, inspect every valid neighbor on diagonal $d+1$. Let the smallest letter among them be $c$.

Any path choosing a letter larger than $c$ has a worse prefix at the first position where it differs. No later letters can make that path lexicographically smaller. Therefore, all such neighbors can be discarded.

We keep every neighbor containing $c$, append $c$ to the answer, and continue to the next diagonal.

## Algorithm

The current frontier contains cells on one diagonal that are reachable using the smallest prefix found so far.

Initially, the frontier contains only the upper-left cell, and the answer begins with its letter.

For each following diagonal:

1. Examine the right and down neighbors of every frontier cell.
2. Find the smallest letter among those neighbors.
3. Append that letter to the answer.
4. Keep every neighbor containing that letter.
5. Remove duplicate cells reached from multiple parents.

A cell on diagonal $d$ is uniquely determined by its row because its column is

$$
j=d-i.
$$

Thus, the frontier only needs to store row indices.

## Correctness

We prove that after processing diagonal $d$, `ans` is the lexicographically smallest prefix obtainable on the first $d+1$ cells of a path, and `cur` contains exactly the cells reachable with that prefix.

The claim is true for $d=0$, since every path begins at the upper-left cell.

Assume it is true for diagonal $d$. Every path extending the current minimum prefix must move from a frontier cell to one of its right or down neighbors.

Let $c$ be the smallest letter among all these neighbors. A path choosing a letter larger than $c$ produces a larger prefix immediately at the next position. Later characters cannot change this comparison, so such a path cannot belong to a lexicographically minimum complete path.

Every neighbor containing $c$ extends the current prefix by the smallest possible next character. The algorithm keeps all such neighbors, so it does not discard any position that could lead to the best suffix.

Therefore, after the update, the answer is the smallest possible prefix through diagonal $d+1$, and the new frontier contains all cells reachable with that prefix.

By induction, this remains true through the final diagonal. At that point the frontier contains the lower-right cell, so the constructed string is the lexicographically smallest complete path string.

## Implementation

For a frontier row $i$ on diagonal $d$, its column is

$$
j=d-i.
$$

Its possible next cells are:

- $(i+1,j)$, moving down;
- $(i,j+1)$, moving right.

Different frontier cells may reach the same next cell. The `seen` array ensures that each row is inserted only once during a diagonal.

The full grid is stored, but each frontier contains at most $n$ cells.

## Complexity

There are $2n-1$ diagonals, and each contains at most $n$ cells. Each frontier cell checks at most two neighbors.

The time complexity is

$$
O(n^2).
$$

The grid requires

$$
O(n^2)
$$

memory, while the frontier and duplicate-removal arrays require

$$
O(n)
$$

additional memory.

## Worked Example

Consider

$$
\begin{matrix}
A&A&C&A\\
B&A&B&C\\
A&B&D&A\\
A&A&C&A
\end{matrix}
$$

The process begins with

$$
A.
$$

On the next diagonal, the available letters are $A$ and $B$, so only the cell containing $A$ is kept:

$$
AA.
$$

On the following diagonal, the smallest reachable letter is again $A$:

$$
AAA.
$$

Continuing this process across all diagonals produces

$$
\text{AAABACA}.
$$

At every step, all positions producing the smallest current prefix are retained, so the best future continuation remains available.
