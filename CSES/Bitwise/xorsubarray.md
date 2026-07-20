# Maximum Xor Subarray

- **Source:** [CSES 1655: Maximum Xor Subarray](https://cses.fi/problemset/task/1655/)
- **Code:** [`xorsubarray.cpp`](./xorsubarray.cpp)

## Problem

Find the maximum xor of a nonempty contiguous subarray of nonnegative integers.

## Idea

Define prefix xor values by

$$
P_0=0,
\qquad
P_i=a_1\oplus a_2\oplus\cdots\oplus a_i.
$$

Equal values cancel under xor, so

$$
a_l\oplus\cdots\oplus a_r=P_r\oplus P_{l-1}.
$$

For a fixed right endpoint $r$, we need an earlier prefix $P_j$ that maximizes $P_r\oplus P_j$. Store all earlier prefix values in a binary trie.

Xor results are compared as ordinary integers. At the highest bit where two choices differ, producing a one is always better than producing a zero, regardless of all lower bits. During a trie query, we therefore prefer the child whose bit is opposite to the current prefix bit.

Insert $P_0=0$ before reading the array so that subarrays beginning at the first position are represented.

## Algorithm

1. Insert zero into an empty binary trie.
2. Maintain `pref = 0` and `ans = 0`.
3. For each array value:
   - update `pref ^= value`;
   - query the maximum xor of `pref` with a stored prefix;
   - update `ans`;
   - insert `pref` into the trie.
4. Output `ans`.

## Correctness

**Lemma 1.** Before querying $P_i$, the trie contains exactly $P_0,P_1,\ldots,P_{i-1}$.

**Proof.** Initially the trie contains only $P_0$. After querying $P_i$, the algorithm inserts it, establishing the invariant for the next iteration. Induction proves the claim. $\square$

**Lemma 2.** `get(x)` returns the maximum value of $x\oplus y$ over all stored values $y$.

**Proof.** Bits are processed from most significant to least significant. If an opposite-bit child exists, taking it sets the current result bit to one. Taking the same-bit child sets it to zero, and no decisions at lower bits can compensate for losing the current power of two. If no opposite child exists, the same-bit child is forced. Repeating this argument yields the maximum result. $\square$

**Theorem.** The algorithm outputs the maximum xor of a nonempty subarray.

**Proof.** By Lemma 1, the query for $P_r$ considers every legal earlier prefix. By Lemma 2, it finds the best subarray ending at $r$. The prefix identity represents every nonempty subarray in this form, so taking the maximum over all right endpoints gives the global optimum. $\square$

## Complexity

Each insertion and query examines $30$ bits. The time complexity is $O(30n)=O(n)$ and the trie uses $O(30n)=O(n)$ memory.

## Implementation

Node zero is the trie root. The implementation processes bits $29$ through $0$, which cover every value below $2^{30}$. Querying before inserting the current prefix prevents pairing a prefix with itself, which would represent an empty subarray.

## Worked Example

For $[5,1,5,9]$, the prefix xor values are

$$
0,5,4,1,8.
$$

When $8$ is queried, pairing it with the earlier prefix $5$ gives $8\oplus5=13$. This corresponds to subarray $[1,5,9]$.

## Takeaway

Transform a subarray xor into a pair of prefix xors. To maximize xor against a dynamic set, use a most-significant-bit-first binary trie.
