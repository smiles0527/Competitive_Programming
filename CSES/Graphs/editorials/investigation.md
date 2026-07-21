# Investigation

## Problem

- **Source:** [CSES 1202: Investigation](https://cses.fi/problemset/task/1202/)
- **Code:** [`View accepted C++ solution (investigation.cpp)`](../investigation.cpp)
- **Constraints:** $2\le n\le100000$, $1\le m\le200000$, and $1\le w\le10^9$.

For shortest routes from city 1 to city $n$, output the minimum cost, the number of shortest routes, the minimum number of flights among them, and the maximum number of flights among them.

## Idea

Because all edge costs are positive, Dijkstra's algorithm finds the shortest distances. Alongside each distance, maintain aggregate information for every route attaining that distance.

When relaxing edge $(u,v,w)$, if `dist[u] + w` is strictly smaller than `dist[v]`, every previously known route to $v$ is suboptimal. Replace all statistics at $v$ with the statistics from $u$, adding one flight. If the new distance equals `dist[v]`, it contributes another disjoint set of shortest routes, so add route counts and update the minimum and maximum flight counts.

Strictly positive edge costs guarantee that every shortest-path predecessor has a strictly smaller distance than its successor. Therefore a predecessor's aggregates are complete before they are propagated.

## Algorithm

Run Dijkstra. For every vertex, store its distance, number of shortest routes, minimum number of flights among shortest routes, and maximum number of flights among shortest routes. Replace these values on a strict improvement and aggregate them on a tie. Print the four values for city $n$.

## Correctness

Every shortest route to $v$ ends with an edge $(u,v,w)$ satisfying `dist[u] + w = dist[v]`. When that edge is relaxed, the algorithm transfers every shortest route to $u$ and appends one flight. Different predecessor routes or final edges produce different routes, so their counts add.

A strict improvement removes only routes longer than the new optimum. A tie preserves the distance and combines every optimal candidate. Processing vertices by increasing distance ensures that predecessor aggregates are final. Hence all four maintained values exactly describe the shortest routes to every vertex, including city $n$.

## Implementation

`mn` starts at infinity, while the source minimum and maximum flight counts start at zero. Route counts are reduced modulo $10^9+7$. The strictly positive weights prevent dependencies between vertices at the same shortest distance.

## Complexity

The time complexity is $O((n+m)\log n)$ and the space complexity is $O(n+m)$.

## Worked Example

If two shortest routes to the destination use 2 and 4 flights, both with cost 10, the algorithm adds their route counts, keeps minimum 2 and maximum 4, and leaves the distance equal to 10.
