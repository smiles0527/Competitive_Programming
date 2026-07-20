# Maximum Xor Subset

- **Source:** [CSES 3191: Maximum Xor Subset](https://cses.fi/problemset/task/3191/)
- **Code:** [`xorsubset.cpp`](./xorsubset.cpp)

## Problem

Choose any subset of the input numbers and maximize the xor of its elements. The empty subset, whose xor is zero, is allowed.

## Idea

Interpret every number as a binary vector. Xor is vector addition over $\mathrm{GF}(2)$, so all attainable subset xors form the linear span of the input vectors.

Construct a triangular xor basis. `b[i]` is either zero or a vector whose highest set bit is $i$. To insert $x$, scan its bits from high to low. If a pivot already exists at its highest bit, xor that pivot into $x$ to clear the bit. Otherwise, store $x$ as the new pivot. A value that reduces to zero is dependent and adds no new attainable xor.

After building the basis, start with `ans = 0` and process pivots from high to low. Replace `ans` with `ans ^ b[i]` exactly when this makes it larger. Lower pivots cannot alter any already optimized higher bit.

## Algorithm

1. Initialize all $30$ basis positions to zero.
2. Insert every input value by descending-bit elimination.
3. Starting from bit $29$, xor a pivot into `ans` whenever it increases `ans`.
4. Output `ans`.

## Correctness

**Lemma 1.** After processing any prefix of the input, the basis spans exactly the subset xors of the processed values.

**Proof.** Xoring an existing pivot into the inserted vector does not change whether that vector belongs to the current span. If it reduces to zero, it was already representable. Otherwise, storing its nonzero remainder adds one independent direction. The invariant follows by induction. $\square$

**Lemma 2.** After processing pivot $i$ in the greedy phase, `ans` is maximal on every bit from $29$ through $i$ among all basis combinations.

**Proof.** Pivot `b[i]` has highest set bit $i$, while all later pivots have lower highest bits. Comparing `ans` and `ans ^ b[i]` therefore makes the optimal choice at the most significant bit that remains changeable. No later choice can alter that decision. $\square$

**Theorem.** The algorithm outputs the maximum subset xor.

**Proof.** Lemma 1 equates basis combinations with attainable subset xors. Lemma 2 shows that the greedy phase constructs the numerically largest basis combination. $\square$

## Complexity

Each insertion examines $30$ bits. The time complexity is $O(30n)=O(n)$ and the auxiliary space is $O(30)=O(1)$.

## Implementation

The basis is triangular but does not need to be fully reduced. Higher-pivot vectors may contain lower bits; the descending greedy comparison decides whether each complete vector improves the answer.

## Worked Example

For $[1,6,12,6]$, the second copy of $6$ is dependent. One optimal subset is $\{1,12\}$, whose xor is

$$
1\oplus12=13.
$$

## Takeaway

Subset xor values form a vector space over $\mathrm{GF}(2)$. Maintain one pivot for each highest bit, then optimize the resulting basis from high bits to low bits.
