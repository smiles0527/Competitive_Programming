# Flight Routes

## Problem

- **Source:** [CSES 1196: Flight Routes](https://cses.fi/problemset/task/1196/)
- **Code:** [`View accepted C++ solution (flightroutes.cpp)`](./flightroutes.cpp)
- **Constraints:** $2\le n\le100000$, $1\le m\le200000$, $1\le k\le10$, and $1\le w\le10^9$.

Print the costs of the $k$ cheapest routes from city 1 to city $n$, allowing repeated vertices and counting equal-cost routes with multiplicity.

## Idea

Ordinary Dijkstra settles one distance for each vertex. Here, retain the first $k$ times each vertex is removed from the min-priority queue. Every queue entry represents one concrete route prefix, ordered by cost.

With strictly positive edge weights, extending a later and more expensive prefix cannot produce a cheaper route than the extensions exposed by earlier prefixes. Therefore the first, second, through $k$th accepted pops of a vertex are its first $k$ route costs, including multiplicities.

After a vertex has been accepted $k$ times, every later prefix ending there can be skipped.

## Algorithm

1. Push `(0,1)` into the min-priority queue.
2. Repeatedly pop the cheapest route prefix.
3. Skip it if its endpoint has already been accepted $k$ times. Otherwise increment that endpoint's counter.
4. If the endpoint is city $n$, record its cost.
5. Push every one-edge extension whose endpoint still needs candidates.
6. Stop after city $n$ has been accepted $k$ times.

## Correctness

The min-priority queue contains extensions of every accepted prefix that may still matter. Its minimum is the globally cheapest prefix not yet accepted. Induction on accepted pops shows that the $j$th accepted pop at vertex $v$ has the $j$th cheapest route cost to $v$.

Discarding prefixes after the first $k$ accepted arrivals at $v$ is safe. Any route using a later prefix can be paired with at least $k$ no-more-expensive prefixes to $v$ followed by the same suffix, so it cannot enter the target's first $k$ routes. The recorded target costs are therefore exactly the required sequence.

## Implementation

`cnt[v]` stores accepted pops, not discovered routes. A target cost is recorded only after its pop is accepted. The problem guarantees at least $k$ routes, so exactly $k$ answers are available.

## Complexity

Each vertex is expanded at most $k$ times, producing at most $km$ edge extensions. A safe bound is $O(km\log(kn))$ time and $O(km+kn)$ space for the queue and counters.

## Worked Example

If target routes have costs 5, 5, 7, and 9, the two distinct prefixes with cost 5 are both accepted and printed. Equal costs are not deduplicated.
