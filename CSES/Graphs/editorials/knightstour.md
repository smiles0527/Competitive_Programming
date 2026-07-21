# Knight's Tour

## Problem

- **Source:** [CSES 1689, Knight's Tour](https://cses.fi/problemset/task/1689/)
- **Code:** [`View accepted C++ solution (knightstour.cpp)`](../knightstour.cpp)
- **Constraints:** The board is 8 by 8, and the starting coordinates satisfy 1 <= x,y <= 8.

Starting from a specified square of an $8\times8$ chessboard, number all 64 squares so that consecutive numbers are connected by a legal knight move. Every square must occur exactly once.

This asks for a Hamiltonian path in the knight-move graph, but the fixed board size permits carefully ordered backtracking.

## Idea

Plain backtracking has up to eight choices at each step and wastes enormous time on paths that trap an unvisited square near the end. The key is not a greedy proof but a search-order heuristic: try the most constrained next square first.

For an unvisited square $(r,c)$, define its onward degree as the number of legal moves from it to other unvisited squares. Warnsdorff's rule sorts candidates by increasing onward degree. A square with few exits is difficult to incorporate later, so visiting it now is more likely to avoid isolation.

Choosing only the minimum-degree candidate would be heuristic and could lose correctness. The implementation still tries every candidate in sorted order and backtracks on failure. Therefore the ordering changes running time, not the set of tours explored.

The board itself is the visited structure. Zero means unvisited; a positive value records the step at which the square was entered. On return from a failed recursive call, resetting the current square to zero restores the exact state that existed before that call.

## Algorithm

At recursive state `(r, c, step)`:

1. Set `board[r][c] = step`.
2. If `step == 64`, return success.
3. Generate every legal knight destination whose board value is zero.
4. For each candidate, compute how many unvisited moves would remain from it.
5. Sort candidates by this onward degree in increasing order.
6. Recursively try them in that order. Return immediately if one completes the tour.
7. If all fail, reset `board[r][c]` to zero and return failure.

The input uses chess coordinates $(x,y)$, while the array is indexed `(row, column)`, so the start is converted to `r = y - 1`, `c = x - 1`.

## Correctness

### Lemma 1

At entry to `solve(r,c,step)`, the positive board entries form a simple legal knight path numbered $1$ through `step-1`, and $(r,c)$ is an unvisited legal continuation of that path, except at the initial call.

#### Proof

The initial call has an empty preceding path. Every recursive call is made only for an in-bounds square with value zero reached by one of the eight knight offsets from the current endpoint. Thus it appends a new, previously unused square by a legal move. Induction proves the invariant. $\square$

### Lemma 2

If `solve` returns true, the board is a valid knight's tour from the requested start.

#### Proof

Success occurs only after assigning step 64. By Lemma 1, every assignment appends a distinct square through a legal knight move. There are 64 positive entries on a 64-square board, so every square is visited exactly once and consecutive numbers form knight moves. The first assignment is the requested start. $\square$

### Lemma 3

If a completion exists from a recursive state, `solve` eventually finds one.

#### Proof

Every legal unvisited next square is included in `cand`. Sorting permutes this complete candidate set without removing any choice. If the first candidate does not lead to a completion, recursive failure restores the board before the next is tried. Induction on the number of unvisited squares shows that the branch matching any existing completion is eventually explored and succeeds. $\square$

### Theorem

The algorithm outputs a valid knight's tour.

#### Proof

The standard $8\times8$ knight graph admits an open tour from every starting square. By Lemma 3, exhaustive backtracking finds a completion from the supplied start; Warnsdorff ordering only determines how soon. Lemma 2 proves that the retained board after success is a valid tour. $\square$

## Implementation

`deg` counts only currently unvisited destinations, so candidate priorities are recomputed for the exact search state. The candidate type stores `(degree, (row, column))`; the default pair ordering provides deterministic tie breaking.

The current square remains numbered while its children are explored. It is cleared only after every continuation fails. On success, recursive calls return without clearing, preserving the completed board.

The coordinate conversion is easy to reverse accidentally: input gives column first and row second.

## Complexity

The worst-case backtracking complexity is exponential in the 64 squares, with at most eight branches per level. The board and recursion stack use $O(64)$ space. On the fixed board, Warnsdorff ordering prunes the practical search dramatically, which is essential even though it does not improve the formal exponential bound.

## Worked Example

Suppose the current endpoint has three legal unvisited candidates with onward degrees 1, 5, and 2. The recursion tries the degree-1 square first. If its sole continuation later fails, the entire branch is undone and the degree-2 candidate is tried next.

This illustrates the distinction between ordering and commitment. Warnsdorff's rule predicts a promising branch, while backtracking preserves completeness when the prediction is wrong.
