# Colored Chairs

- **Problem:** [CSES 3273](https://cses.fi/problemset/task/3273)
- **Code:** [View accepted C++ solution (coloredchairs.cpp)](../coloredchairs.cpp)

## Problem

An odd number of red or blue chairs form a circle. Find two adjacent chairs of the same color using at most twenty color queries.

## Idea

If chairs $1$ and $n$ match, the circular edge between them is already an answer. Otherwise cut the circle there and consider the line.

Define encoded predicate

$$f(i)=color(i)\oplus color(1)\oplus((i-1)\bmod2).$$

Then $f(1)=0$. Because $n$ is odd, $(n-1)$ is even, and the differing endpoint colors give $f(n)=1$. Binary search does not require $f$ to be globally monotone: maintaining endpoints with different $f$ values is enough. Query the midpoint and keep the half whose endpoint values differ.

When adjacent endpoints $i,i+1$ have different $f$ values, expanding the definition shows their actual colors are equal, because the parity term toggles between adjacent indices.

## Algorithm

Query chairs $1$ and $n$. If equal, report $n$. Otherwise maintain `lo=1`, `hi=n` with $f(lo)=0,f(hi)=1$. Query each midpoint and replace the endpoint having the same encoded value. When adjacent, report `lo`.

## Correctness

**Invariant.** The maintained endpoints satisfy $f(lo)=0$, $f(hi)=1$, and $lo<hi$.

**Proof.** It holds after the endpoint queries. A midpoint has encoded value zero or one; replacing the endpoint with the same value preserves both endpoint values and strictly reduces the interval.

**Lemma.** If $f(i)\ne f(i+1)$, chairs $i$ and $i+1$ have equal colors.

**Proof.** The parity terms differ by one. For the total XOR values also to differ, the two color bits must be equal.

**Theorem.** The algorithm reports an adjacent equal-colored pair.

**Proof.** The immediate endpoint case is valid. Otherwise the invariant terminates with adjacent endpoints of different encoded values, and the lemma proves their colors match.

## Complexity

The algorithm uses two endpoint queries plus at most $\lceil\log_2 n\rceil$ midpoint queries, within twenty for $n\le2\cdot10^5$. Local time is $O(\log n)$ and cached space is $O(n)$.

## Implementation

Queried colors are cached. Blue is encoded as one and red as zero, though swapping the encoding changes nothing. Every interaction is flushed.


## Worked Example

For five chairs with endpoint colors different, $f(1)=0$ and $f(5)=1$. If querying chair $3$ gives $f(3)=0$, replace `lo` by $3$. Querying chair $4$ then leaves adjacent endpoints whose encoded values differ, proving chairs $3$ and $4$ match.

## Takeaway

Binary search can maintain a change between endpoints even when the predicate is not monotone. Transform the target local relation into a guaranteed endpoint disagreement.

## Related Problems

Hidden Integer, Inversion Sorting, Binary Subsequence.
