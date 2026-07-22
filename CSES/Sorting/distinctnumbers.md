# Distinct Numbers

## Problem

- **Source:** [CSES 1621: Distinct Numbers](https://cses.fi/problemset/task/1621/)
- **Code:** [`View accepted C++ solution (distinctnumbers.cpp)`](./distinctnumbers.cpp)

Count the distinct values among $n\le2\cdot10^5$ integers.

## Idea

After sorting, all occurrences of the same value are adjacent. For example, $[2,3,2,2,3]$ becomes $[2,2,2,3,3]$.

The first element begins the first distinct group. Every later element begins a new group exactly when it differs from the previous element.

## Algorithm

1. Sort the array.
2. Initialize the answer to $1$.
3. For every $i\ge1$, increment the answer when $a_i\ne a_{i-1}$.

## Correctness

After sorting, equal values occupy one contiguous interval. The algorithm counts the first value and then exactly the first position of every later distinct-value interval. Thus, it counts each distinct value once and no value twice, so the result is the number of distinct values.

## Complexity

Sorting takes $O(n\log n)$ time and the scan takes $O(n)$, for $O(n\log n)$ total time. Apart from the input array, the algorithm uses $O(1)$ auxiliary memory.
