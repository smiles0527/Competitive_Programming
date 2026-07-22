# Apartments

## Problem

- **Source:** [CSES 1084: Apartments](https://cses.fi/problemset/task/1084/)
- **Code:** [`View accepted C++ solution (apartment.cpp)`](./apartment.cpp)

Applicant $i$ accepts an apartment whose size lies between $a_i-k$ and $a_i+k$. Maximize the number of matches, with $n,m\le2\cdot10^5$.

## Idea

Sort both lists and point $i$ and $j$ to the smallest unmatched applicant and apartment.

If $b_j<a_i-k$, the apartment is too small. Every later applicant wants an apartment at least as large, so discard this apartment.

If $b_j>a_i+k$, the apartment is too large. Every later apartment is at least as large, so this applicant cannot receive any remaining apartment.

Otherwise, $|a_i-b_j|\le k$, and they can be matched.

## Why Matching Them Is Safe

Suppose an optimal solution does not match the current compatible pair. If one is unmatched, replace the other's match with the current pair without reducing the number of matches.

Otherwise, suppose applicant $i$ is matched with a later apartment $b_q$, while apartment $b_j$ is matched with a later applicant $a_p$. Replace these matches by $(a_i,b_j)$ and $(a_p,b_q)$. The second remains valid because

$$b_j\ge a_p-k$$

and

$$b_q\le a_i+k\le a_p+k.$$

Thus, an optimal matching exists that uses the current compatible pair.

## Algorithm

1. Sort applicants and apartments.
2. Compare the smallest unmatched pair.
3. Discard an apartment if it is too small, discard an applicant if the apartment is too large, and otherwise match both.

## Correctness

The two rejection cases discard an item that cannot participate in any remaining match. In the compatible case, the exchange argument above proves that some optimal solution contains the current pair. Therefore, every pointer move preserves the possibility of an optimal answer, and the final number of matches is maximum.

## Complexity

Sorting costs $O(n\log n+m\log m)$. Each pointer advances only once per item, so matching costs $O(n+m)$. Memory usage is $O(n+m)$.
