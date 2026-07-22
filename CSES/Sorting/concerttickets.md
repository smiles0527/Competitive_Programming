# Concert Tickets

## Problem

- **Source:** [CSES 1091: Concert Tickets](https://cses.fi/problemset/task/1091/)
- **Code:** [`View accepted C++ solution (concerttickets.cpp)`](./concerttickets.cpp)

Customers arrive one at a time. Each receives the most expensive unsold ticket whose price does not exceed their limit.

## Idea

Available prices must support finding the largest value at most $x$ and deleting one occurrence. A multiset supports both in logarithmic time and preserves duplicate prices.

For a customer limit $x$, `upper_bound(x)` returns the first price greater than $x$. If it equals `begin()`, every ticket is too expensive. Otherwise, its predecessor is the largest affordable ticket.

## Algorithm

1. Insert all ticket prices into a multiset.
2. For each customer, find `upper_bound(x)`.
3. Print $-1$ if it is `begin()`; otherwise, move back once, print that price, and erase that occurrence.

## Correctness

Before every customer, the multiset contains exactly the unsold tickets. `upper_bound(x)` separates prices at most $x$ from prices above $x$, so its predecessor is precisely the largest affordable ticket. Printing and removing it maintains the invariant for the next customer.

## Worked Example

For tickets $[3,5,5,7,8]$, limit $4$ receives $3$, then limit $8$ receives $8$. A later limit $3$ receives $-1$ because no affordable ticket remains.

## Complexity

Building the multiset takes $O(n\log n)$. Each of $m$ customers performs a logarithmic search and at most one deletion, giving $O((n+m)\log n)$ time and $O(n)$ memory.
