# K Subset Xors

- **Source:** [CSES 3192: K Subset Xors](https://cses.fi/problemset/task/3192/)
- **Code:** [`ksubsetxors.cpp`](../ksubsetxors.cpp)

## Problem

Consider the xor of every subset, including the empty subset. Output the $k$ smallest results in nondecreasing order, retaining duplicates produced by different subsets.

## Idea

The subset-to-xor operation is a linear map from $\mathrm{GF}(2)^n$. If its rank is $r$, its image contains $2^r$ distinct xors and its kernel has dimension $n-r$. Every attainable xor consequently has exactly

$$
2^{n-r}
$$

preimages.

It remains to enumerate the distinct image values in increasing order. The ordinary triangular basis is refined by clearing each lower pivot bit from every higher-pivot vector. Store the resulting vectors in increasing pivot order.

For a coefficient mask $m$, xor the basis vectors selected by its bits. If $m_1<m_2$, consider their highest differing coefficient bit $j$. Higher coefficients agree. At pivot $j$, lower vectors cannot reach the bit and higher vectors have been cleared there, so the represented values differ in the same direction. Increasing masks therefore produce increasing xor values.

## Algorithm

1. Build a triangular xor basis and obtain rank $r$.
2. For every pivot from low to high, clear it from all higher-pivot vectors.
3. Store nonzero vectors in increasing pivot order.
4. Compute the multiplicity $2^{n-r}$, capped at $k$.
5. Enumerate coefficient masks from zero upward.
6. Output each represented xor with that multiplicity until $k$ values have been printed.

## Correctness

**Lemma 1.** Every distinct subset xor occurs exactly $2^{n-r}$ times.

**Proof.** By rank-nullity, the kernel has dimension $n-r$ and size $2^{n-r}$. The preimages of every attainable xor form one affine coset of this kernel. $\square$

**Lemma 2.** Increasing coefficient masks produce increasing distinct xor values after reduction.

**Proof.** Compare two masks at their highest differing coefficient $j$. All higher coefficients agree. Only vector $j$ contains its pivot bit: lower vectors have lower highest bits, while the reduction cleared that pivot from all higher vectors. The output ordering is therefore decided in the same direction as coefficient $j$. $\square$

**Theorem.** The algorithm prints the $k$ smallest subset xors in nondecreasing order.

**Proof.** Lemma 2 enumerates every distinct attainable xor in increasing order. Lemma 1 gives the exact uniform multiplicity of each value. Repeating each value accordingly constructs the sorted multiset of all subset xors, and stopping after $k$ outputs returns its required prefix. $\square$

## Complexity

Basis construction takes $O(30n)$, reduction takes $O(30^2)$, and at most $k$ represented values are processed with $30$ bits each. The total time is $O(30n+30k)$ and the auxiliary basis space is $O(30)$.

## Implementation

The multiplicity is capped at $k$, preventing overflow because larger multiplicities are indistinguishable within the requested prefix. The number of distinct values generated is $\lceil k/2^{n-r}\rceil$.

## Worked Example

For $[3,5,14,8]$, the rank is $3$ and $n=4$, so every distinct xor appears twice. If the distinct values begin

$$
0,3,5,6,8,\ldots,
$$

then the first nine subset xors are

$$
0,0,3,3,5,5,6,6,8.
$$

## Takeaway

For a linear subset map, rank determines the distinct outputs and nullity determines their uniform multiplicity. A reduced pivot structure can make coefficient order match numeric order.
