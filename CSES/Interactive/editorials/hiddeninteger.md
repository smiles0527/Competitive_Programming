# Hidden Integer

- **Problem:** [CSES 3112](https://cses.fi/problemset/task/3112)
- **Code:** [View accepted C++ solution (hiddeninteger.cpp)](../hiddeninteger.cpp)

## Problem

Find a hidden integer in $[1,10^9]$. A query at $m$ reports whether the hidden value is greater than $m$.

## Idea

The response predicate is monotone: all values below the target receive `YES`, and the target and all larger values receive `NO`. Maintain an inclusive interval $[lo,hi]$ known to contain the target.

At midpoint $mid$, a `YES` response excludes every value through $mid$, so set $lo=mid+1$. Otherwise the target is at most $mid$, so set $hi=mid$. Each query roughly halves the interval.

## Algorithm

Initialize $lo=1,hi=10^9$. While $lo<hi$, query the lower midpoint and update the appropriate inclusive boundary. Report the common value.

## Correctness

**Invariant.** Before every iteration, the hidden integer lies in $[lo,hi]$.

**Proof.** It holds initially. If the answer is `YES`, the target is strictly above $mid$, so discarding $[lo,mid]$ is safe. Otherwise it lies in $[lo,mid]$, so discarding the upper part is safe.

**Theorem.** The reported value is the hidden integer.

**Proof.** The invariant is preserved and the interval strictly shrinks. On termination $lo=hi$; the only remaining candidate must be the target.

## Complexity

At most $\lceil\log_2 10^9\rceil=30$ queries are used. Local time is $O(\log 10^9)$ and space is $O(1)$.

## Implementation

The midpoint formula avoids overflow. Every query and final answer ends with `flush`; without flushing, the grader may wait indefinitely for buffered output.


## Worked Example

If the current interval is $[1,8]$ and the target is $6$, querying $4$ returns `YES` and leaves $[5,8]$. Querying $6$ returns `NO` and leaves $[5,6]$; querying $5$ returns `YES`, isolating $6$.

## Takeaway

Interactive binary search uses the same interval invariant as offline search, but query meaning, boundary strictness, and output flushing must all match the protocol exactly.

## Related Problems

Hidden Permutation, K-th Highest Score, Factory Machines.
