# Number of Subset Xors

- **Source:** [CSES 3211: Number of Subset Xors](https://cses.fi/problemset/task/3211/)
- **Code:** [`numbersubsetxors.cpp`](../numbersubsetxors.cpp)

## Problem

Count the distinct xor values obtainable from all subsets. Different subsets producing the same xor are counted once, and the empty subset contributes zero.

## Idea

Choosing a subset is equivalent to choosing binary coefficients in a linear combination over $\mathrm{GF}(2)$. Thus, the distinct subset xors form the span of the input vectors.

If this span has rank $r$, it contains exactly $2^r$ vectors. Compute the rank with a triangular xor basis. When inserting $x$, clear its highest set bits using existing pivots. A nonzero remainder creates a new pivot and increases the rank; a zero remainder is dependent.

## Algorithm

1. Initialize an empty $30$-bit xor basis and `r = 0`.
2. Insert every value by descending-bit elimination.
3. Increase `r` whenever a new pivot is created.
4. Output $2^r$.

## Correctness

**Lemma 1.** The final basis is independent and spans exactly the input values.

**Proof.** Basis vectors have different highest set bits, so no nonempty xor of them can be zero: the greatest participating pivot bit cannot cancel. Elimination preserves the span. A zero remainder was already representable, while a nonzero remainder placed into an empty pivot position adds one independent direction. $\square$

**Lemma 2.** A binary vector space of rank $r$ contains exactly $2^r$ vectors.

**Proof.** There are $2^r$ binary coefficient choices for the basis. If two choices produced the same xor, their difference would be a nonempty basis combination equal to zero, contradicting independence. $\square$

**Theorem.** The algorithm outputs the number of distinct subset xors.

**Proof.** Lemma 1 shows that the basis span is exactly the set of attainable subset xors. Lemma 2 shows that this span contains $2^r$ distinct values. $\square$

## Complexity

The time complexity is $O(30n)=O(n)$ and the auxiliary space is $O(30)=O(1)$.

## Implementation

The rank is incremented at the moment a new pivot is stored. Under the official value bound, $r\le30$, so `1LL << r` fits in a signed 64-bit integer.

## Worked Example

For $[3,6,5]$, only two vectors are independent because $3\oplus6=5$. The rank is $2$, so there are

$$
2^2=4
$$

distinct subset xors: $0,3,5,6$.

## Takeaway

Counting distinct subset xors is a rank problem. Once xor is viewed as binary vector addition, the answer is the size of the span.
