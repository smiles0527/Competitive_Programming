# All Subarray Xors

- **Source:** [CSES 3233: All Subarray Xors](https://cses.fi/problemset/task/3233/)
- **Code:** [`allsubarrayxors.cpp`](./allsubarrayxors.cpp)

## Problem

Output, in increasing order, every distinct integer that occurs as the xor of a nonempty contiguous subarray.

## Idea

Let

$$
P_0=0,
\qquad
P_i=a_1\oplus\cdots\oplus a_i.
$$

Every subarray xor is $P_r\oplus P_{l-1}$. If `f[x]` is the frequency of prefix xor $x$, the xor convolution

$$
g[z]=\sum_x f[x]f[x\oplus z]
$$

counts ordered pairs of prefix positions whose values xor to $z$.

The Walsh-Hadamard transform diagonalizes xor convolution. Transform `f`, square each transformed coordinate, transform again, and divide every coordinate by the transform size.

For $z>0$, any contributing pair has different prefix values and therefore different positions, so it defines a nonempty subarray. For $z=0$, the convolution also includes every position paired with itself. Zero is valid only when some prefix xor occurs at least twice.

## Algorithm

1. Compute all prefix xors and their frequencies.
2. Record whether any prefix value repeats.
3. Apply FWHT to the frequency array.
4. Square every transformed coordinate.
5. Apply FWHT again and divide by the transform size.
6. Include zero exactly when a prefix repeats. Include each positive value whose convolution count is positive.

## Correctness

**Lemma 1.** For $z>0$, $g[z]>0$ exactly when a nonempty subarray has xor $z$.

**Proof.** A positive convolution term gives two prefix values whose xor is $z$. Since $z$ is nonzero, the values and their positions are distinct; ordering the positions gives a nonempty subarray. Conversely, every nonempty subarray supplies such a pair. $\square$

**Lemma 2.** A nonempty zero-xor subarray exists exactly when a prefix xor repeats.

**Proof.** A subarray xor is zero exactly when its boundary prefix values are equal. It is nonempty exactly when the two prefix positions are distinct. $\square$

**Theorem.** The algorithm outputs exactly all distinct nonempty subarray xors.

**Proof.** The FWHT procedure computes the xor self-convolution. Lemma 1 characterizes every positive result, while Lemma 2 gives the necessary special handling for zero. Scanning the universe once outputs every attainable value exactly once and in increasing order. $\square$

## Complexity

For transform size $M\le2^{20}$, the time complexity is $O(M\log M+n)$ and the memory usage is $O(M+n)$.

## Implementation

The transform uses `long long` because its intermediate coordinates and their squares exceed 32-bit range. The array uses prefix frequencies rather than mere presence, so the second transform is divided by $M$ to recover exact convolution counts.

## Worked Example

For $[5,1,5,9]$, the prefix xors are $0,5,4,1,8$. Their pairwise xor support is

$$
1,4,5,8,9,12,13.
$$

No prefix repeats, so zero is not included.

## Takeaway

When all desired values are xor differences of elements from a bounded universe, xor convolution can compute the complete support at once.
