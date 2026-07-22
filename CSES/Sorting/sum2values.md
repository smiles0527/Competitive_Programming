# Sum of Two Values

## Problem

- **Source:** [CSES 1640: Sum of Two Values](https://cses.fi/problemset/task/1640/)
- **Code:** [`View accepted C++ solution (sum2values.cpp)`](./sum2values.cpp)

Find two values at distinct positions whose sum is $x$, with $n\le2\cdot10^5$, or report that no such pair exists.

## Idea

Store every value with its original index, sort the pairs, and use pointers `l` and `r`.

If $a_l+a_r<x$, then $a_l$ cannot form the target with any remaining value because every candidate paired with it is at most $a_r$. Increase `l`.

If $a_l+a_r>x$, then $a_r$ cannot form the target with any remaining value because every candidate paired with it is at least $a_l$. Decrease `r`.

If the sum equals $x$, print the stored original indices.

## Algorithm

1. Store $(\text{value},\text{original index})$ pairs and sort them.
2. Start pointers at both ends.
3. Move the left pointer for a sum below $x$, move the right pointer for a sum above $x$, and print the indices for equality.
4. If the pointers meet, print `IMPOSSIBLE`.

## Correctness

At every step, the algorithm either finds the target or removes a value that cannot participate in any remaining valid pair. Removing the left value is safe when the sum is too small, and removing the right value is safe when it is too large. Therefore, no valid pair is discarded. If the pointers meet without equality, no valid pair exists.

The original indices are stored with the values, so sorting does not prevent printing the required positions.

## Worked Example

For $[2,7,5,1]$ and $x=8$, the sorted value-index pairs are $(1,4),(2,1),(5,3),(7,2)$. The first and last values satisfy $1+7=8$, so positions $4$ and $2$ form a valid answer.

## Complexity

Sorting costs $O(n\log n)$ and the two-pointer scan costs $O(n)$. Total time is $O(n\log n)$ and memory usage is $O(n)$.
