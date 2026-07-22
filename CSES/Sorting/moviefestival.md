# Movie Festival

## Problem

- **Source:** [CSES 1629: Movie Festival](https://cses.fi/problemset/task/1629/)
- **Code:** [`View accepted C++ solution (moviefestival.cpp)`](./moviefestival.cpp)

Each movie has a starting and ending time. Find the maximum number of movies that can be watched completely.

## Idea

Among the compatible movies, choose the one ending earliest. Finishing earlier leaves at least as much time for every later choice as finishing later.

## Greedy Proof

Let $g$ be the movie with the earliest ending time, and let the first movie of an optimal schedule be $f$. Then

$$\operatorname{end}(g)\le\operatorname{end}(f).$$

Replace $f$ with $g$. Every later movie begins at or after $\operatorname{end}(f)$ and therefore also begins at or after $\operatorname{end}(g)$. The replacement is valid and preserves the schedule size.

Thus, some optimal schedule begins with the greedy choice. Repeating the argument after every selected movie proves the full algorithm.

## Algorithm

1. Sort movies by ending time.
2. Track the ending time `last` of the most recently selected movie.
3. Select each movie satisfying $\text{start}\ge\text{last}$ and update `last`.

## Correctness

The exchange argument proves that the earliest-ending compatible movie can always be chosen without reducing the optimum. After selecting it, the remaining problem has the same form. Induction over the chosen movies proves that the algorithm watches the maximum possible number.

## Worked Example

For $(3,5)$, $(4,9)$, and $(5,8)$, select $(3,5)$ first because it ends earliest. Movie $(5,8)$ starts when it ends, so it is also selected. The answer is $2$.

## Complexity

Sorting takes $O(n\log n)$ and scanning takes $O(n)$. Memory usage is $O(n)$.
