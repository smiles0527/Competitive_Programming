# Hamiltonian Flights

## Problem

- **Source:** [CSES 1690, Hamiltonian Flights](https://cses.fi/problemset/task/1690/)
- **Code:** [`View accepted C++ solution (hamiltonianflights.cpp)`](../hamiltonianflights.cpp)
- **Constraints:** 2 <= n <= 20 and 1 <= m <= 200000.

Count directed routes from city $1$ to city $n$ that visit every city exactly once. Parallel directed flights are distinct choices. Return the count modulo $10^9+7$.

The requirement to remember which cities have been visited makes ordinary vertex-only dynamic programming insufficient.

## Idea

With $n\le20$, a subset of cities fits in one bitmask. There are $2^n$ subsets, which is large but feasible, while enumerating all $n!$ visit orders is not.

Define

$$
dp[S][v]
=\text{number of routes that start at city 1, visit exactly set }S,
\text{ and end at }v.
$$

The endpoint is required because the possible next flights depend on the current city. If $u\notin S$, extending across an edge $v\to u$ produces state $(S\cup\{u\},u)$. With `cnt[v][u]` parallel edges, each existing vertex sequence gives that many distinct flight choices, so the transition adds

$$
dp[S][v]\cdot \operatorname{cnt}[v][u].
$$

Every valid route has a unique penultimate state obtained by removing its last city and last edge. This gives the exact-once counting argument.

The implementation processes subsets numerically. Every transition adds a bit, so the new mask is larger than the old mask and will be processed later. No separate length loop is necessary.

## Algorithm

1. Count the multiplicity `cnt[v][u]` of every directed endpoint pair.
2. Initialize `dp[1][0] = 1`, representing the route containing only city 1.
3. For every mask `S` containing city 1 and every endpoint $v$ in `S` with nonzero state:
   - inspect every city $u$ not in `S`;
   - if at least one edge $v\to u$ exists, add `dp[S][v] * cnt[v][u]` to `dp[S | (1<<u)][u]` modulo $10^9+7$.
4. Print the state whose mask contains all cities and whose endpoint is city $n$.

## Correctness

### Lemma 1

For every processed state $(S,v)$, `dp[S][v]` equals the number of routes that start at city 1, visit exactly the cities in $S$ once, and end at $v$.

#### Proof

Proceed by increasing mask value, which respects every transition because adding a bit increases the mask. The base state contains the single empty-edge route at city 1.

For a transition to unvisited $u$, each counted route to $v$ can be extended by any of the `cnt[v][u]` distinct parallel edges, creating that many valid routes for the larger state. Conversely, every route represented by the larger state has a unique previous endpoint $v$, previous set $S$ obtained by removing $u$, and chosen final edge. Thus transitions include every valid route exactly once and no invalid route. $\square$

### Theorem

The algorithm prints the number of Hamiltonian routes from city $1$ to city $n$.

#### Proof

By Lemma 1, `dp[(1<<n)-1][n-1]` counts routes starting at city 1, visiting exactly the full set of cities once, and ending at city $n$. These are precisely the required Hamiltonian flights. Modular addition and multiplication preserve the requested answer modulo $10^9+7$. $\square$

## Implementation

Cities are converted to zero-based indices so bit $v$ directly represents city $v$. `cnt` preserves parallel-edge multiplicity rather than reducing adjacency to a boolean.

The multiplication is cast through `long long` before taking the modulus; two `int` factors could otherwise overflow before reduction.

States in which city $n$ was visited early may be generated, but they can never contribute to the final endpoint-$n$ state because revisiting a set bit is forbidden. Skipping them would be an optional optimization, not a correctness requirement.

## Complexity

There are $2^n n$ states and each potentially scans $n$ next cities, so time is $O(2^n n^2)$. The DP table uses $O(2^n n)$ space. At $n=20$, the table contains about 21 million integers, which is feasible but explains why factorial enumeration is not.

## Worked Example

Let the directed edges be $1\to2$, two parallel edges $1\to3$, $2\to3$, $3\to2$, $2\to4$, and $3\to4$. From base state `{1}`, the algorithm creates one route ending at 2 and two ending at 3.

The Hamiltonian city orders are $1,2,3,4$ and $1,3,2,4$. The first has one edge choice throughout. The second has two choices for its first parallel flight, so it contributes two. The final DP answer is 3.
