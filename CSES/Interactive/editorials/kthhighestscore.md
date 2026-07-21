# K-th Highest Score

- **Problem:** [CSES 3305](https://cses.fi/problemset/task/3305)
- **Code:** [View accepted C++ solution (kthhighestscore.cpp)](../kthhighestscore.cpp)

## Problem

Finland and Sweden each have $n$ distinct scores sorted implicitly from highest to lowest. Querying a country and rank reveals that score. Find the $k$th highest score overall with at most one hundred queries.

## Idea

Choose $i$ Finnish scores and $j=k-i$ Swedish scores for the combined top-$k$ prefix. This partition is valid exactly when neither first excluded score should replace the other country's last included score:

$$F_i>S_{j+1},\qquad S_j>F_{i+1}.$$

Sentinels $F_0=S_0=+\infty$ and $F_{n+1}=S_{n+1}=-\infty$ handle empty sides. For a valid partition, the $k$th score is the smaller of the two last included scores, $\min(F_i,S_j)$.

Binary-search $i$ over $\max(0,k-n)\le i\le\min(k,n)$. If $F_i<S_{j+1}$, too few Swedish scores were included, so decrease $i$. If $S_j<F_{i+1}$, increase $i$.

## Algorithm

Maintain the feasible range of $i$. At each midpoint query the four boundary scores, using cached results and sentinels. Move left or right according to the violated partition inequality. When both hold, report the smaller included boundary.

## Correctness

**Lemma 1.** A partition $(i,j)$ is valid exactly when both boundary inequalities hold.

**Proof.** Within each country the included prefix already dominates its excluded suffix. The only possible violations cross countries, and the two inequalities compare each included boundary with the opposite first excluded score.

**Lemma 2.** Each binary-search direction preserves at least one valid partition.

**Proof.** If $F_i<S_{j+1}$, the excluded Swedish score outranks an included Finnish score, so any valid partition must use fewer Finnish selections. The opposite inequality symmetrically requires more Finnish selections.

**Theorem.** The algorithm reports the global $k$th highest score.

**Proof.** Lemma 2 finds a valid partition. By Lemma 1 its $k$ included values are exactly the global top $k$, whose smallest is $\min(F_i,S_j)$.

## Complexity

There are $O(\log n)$ iterations and at most four newly queried scores per iteration, within one hundred for $n\le10^5$. Local time is $O(\log n)$ and cache space is $O(n)$.

## Implementation

Rank zero and $n+1$ are returned as sentinels without interaction. Real score queries are cached because neighboring binary-search iterations often reuse boundaries. Every request is flushed.


## Worked Example

Let Finland be $(9,4,3)$, Sweden be $(8,6,1)$, and $k=3$. Choosing $i=1,j=2$ gives included boundaries $9$ and $6$, excluded boundaries $4$ and $1$. Both inequalities hold, so the third highest score is $\min(9,6)=6$.

## Takeaway

Selecting an order statistic from two sorted arrays reduces to binary-searching how many elements come from one array, using boundary inequalities to certify a partition.

## Related Problems

Hidden Integer, K Subset Sums I, Median of Two Sorted Arrays.
