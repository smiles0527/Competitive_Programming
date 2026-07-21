# Hidden Permutation

- **Problem:** [CSES 3139](https://cses.fi/problemset/task/3139)
- **Code:** [View accepted C++ solution (hiddenpermutation.cpp)](../hiddenpermutation.cpp)

## Problem

Recover a hidden permutation. A query comparing positions $i$ and $j$ reports whether the hidden value at $i$ is smaller than the hidden value at $j$.

## Idea

The interaction provides a comparison oracle for the unknown values. Because a permutation has distinct values, these comparisons define a strict total order on the indices. Sorting indices by this oracle reconstructs their rank order.

If sorted indices are $p_1,p_2,\ldots,p_n$, then position $p_r$ contains value $r$: exactly $r-1$ hidden values are smaller. Thus the inverse mapping from sorted order to original position is the permutation itself.

Comparison sorting is also query-efficient, using $O(n\log n)$ comparisons instead of testing all pairs.

## Algorithm

Create index list $1,\ldots,n$. Stable-sort it with the interactive comparison as comparator. For each sorted position $r$, assign answer value $r$ to that original index. Print the reconstructed array.

## Correctness

**Lemma 1.** The sorted index list is ordered by increasing hidden value.

**Proof.** The comparator returns true exactly for the hidden strict order. Standard comparison sorting returns a sequence consistent with all such comparisons, and the total order is unique because values are distinct.

**Lemma 2.** Assigning rank $r$ to index $p_r$ recovers its hidden value.

**Proof.** In a permutation of $1\ldots n$, the value with exactly $r-1$ smaller values is $r$. Lemma 1 places $p_r$ at that rank.

**Theorem.** The reported permutation is correct.

**Proof.** Lemma 2 proves every position receives its exact hidden value.

## Complexity

Sorting uses $O(n\log n)$ oracle queries and local time, with $O(n)$ space.

## Implementation

The comparator prints and flushes before reading. `stable_sort` is used as a comparison-based implementation with bounded merge-style behavior; the hidden order has no equal elements, so stability does not affect the result.


## Worked Example

If comparisons order indices as $(2,4,1,3)$, then hidden ranks are $a_2=1,a_4=2,a_1=3,a_3=4$. The reported permutation in position order is $(3,1,4,2)$.

## Takeaway

When an interactive oracle compares hidden values, sort the identities and convert order positions into ranks. Do not attempt to guess values independently.

## Related Problems

Hidden Integer, Permuted Binary Strings, Sorting Methods.
