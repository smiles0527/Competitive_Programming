# Ferris Wheel

## Problem

- **Source:** [CSES 1090: Ferris Wheel](https://cses.fi/problemset/task/1090/)
- **Code:** [`View accepted C++ solution (ferriswheel.cpp)`](./ferriswheel.cpp)

Each gondola holds at most two children whose total weight cannot exceed $x$. Minimize the number of gondolas.

## Idea

Consider the heaviest remaining child. If the heaviest and lightest weights satisfy $a_l+a_r>x$, the heaviest cannot pair with anyone because every other child is at least as heavy as $a_l$. The heaviest must ride alone.

Otherwise, pair the heaviest with the lightest.

## Why the Pairing Is Safe

If the heaviest child is paired with someone heavier than the lightest, replacing that partner with the lightest remains within the limit and leaves the heavier child available. Therefore, pairing the heaviest with the lightest never increases the required gondolas.

## Algorithm

After sorting, let `l` point to the lightest and `r` to the heaviest remaining child. For each gondola, move `l` if both children fit, always place and remove the heaviest child, and increment the answer.

## Correctness

If the lightest cannot fit with the heaviest, nobody can, so sending the heaviest alone is forced. Otherwise, the exchange argument proves pairing the two is safe. Applying this reasoning repeatedly gives an optimal assignment.

## Worked Example

For $[7,2,3,9]$ and $x=10$, sorting gives $[2,3,7,9]$. Weight $9$ rides alone, $7$ pairs with $2$, and $3$ rides alone. The answer is $3$.

## Complexity

Sorting takes $O(n\log n)$ and the two-pointer scan takes $O(n)$. Memory usage is $O(n)$.
