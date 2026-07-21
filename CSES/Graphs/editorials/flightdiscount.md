# Flight Discount

## Problem

- **Source:** [CSES 1195: Flight Discount](https://cses.fi/problemset/task/1195/)
- **Code:** [`View accepted C++ solution (flightdiscount.cpp)`](../flightdiscount.cpp)
- **Constraints:** $2\le n\le100000$, $1\le m\le200000$, and $1\le w\le10^9$.

Compute the minimum cost of travelling from city 1 to city $n$ when one flight may be bought at half price, rounded down.

## Idea

Because the availability of the discount affects future choices, a vertex alone is not a sufficient shortest-path state. Introduce two layers:

$$
(v,0)=\text{at city }v\text{ with the discount unused},
$$

$$
(v,1)=\text{at city }v\text{ with the discount used}.
$$

Every original edge of cost $w$ exists inside both layers at cost $w$. An additional transition goes from layer 0 to layer 1 at cost $\lfloor w/2\rfloor$. Every edge in the expanded graph has nonnegative weight, so Dijkstra's algorithm applies.

## Algorithm

Run Dijkstra on states `(vertex, used)`, where `used` indicates whether the discount has been spent. Relax every flight at full cost without changing the layer. From layer 0, also relax the discounted transition into layer 1. Output the smaller target-layer distance.

## Correctness

Every path in the expanded graph corresponds to an original route with at most one discounted edge, because the layer can change from 0 to 1 only once. Conversely, any original route with one chosen discounted edge maps to an expanded path with exactly the same cost.

Dijkstra finds shortest distances in this nonnegative expanded graph. Therefore the smaller distance to city $n$ across the two layers is the cheapest route using at most one discount. Since every official edge cost is positive and a route exists, applying the discount to some route never increases its cost, so this value also equals the optimum required by the task.

## Implementation

The priority queue stores `{distance, node, used}`, ordered lexicographically. Integer division `w/2` performs the required rounding down. Stale entries are skipped by comparing them with the two-dimensional distance table.

## Complexity

The expanded graph has $2n$ states and at most $3m$ transitions. The time complexity is $O((n+m)\log n)$ and the space complexity is $O(n+m)$.

## Worked Example

For route costs $1\to2=5$ and $2\to3=4$, discounting the first flight costs $2+4=6$, while discounting the second costs $5+2=7$. The layered search returns 6.
