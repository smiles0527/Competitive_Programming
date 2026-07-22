# Restaurant Customers

## Problem

- **Source:** [CSES 1619: Restaurant Customers](https://cses.fi/problemset/task/1619/)
- **Code:** [`View accepted C++ solution (restaurantcustomers.cpp)`](./restaurantcustomers.cpp)

Each customer has a distinct arrival and departure time. Find the maximum number of customers simultaneously present.

## Idea

The customer count changes only at arrivals and departures. Represent every arrival by $(a,+1)$ and every departure by $(b,-1)$. Sort all events and process them chronologically. The running sum is the number currently inside.

Because pairs sort by their second component when times are equal, departures are processed before arrivals. This is consistent with a customer leaving at that time before another is counted as present.

## Algorithm

1. Create one $+1$ arrival event and one $-1$ departure event per customer.
2. Sort the events.
3. Sweep through them, updating the current count and its maximum.

## Correctness

Initially, the restaurant is empty. An arrival increases the exact occupancy by one, and a departure decreases it by one. Between consecutive events, occupancy does not change. Therefore, every possible occupancy occurs during the sweep, and the maximum running value is the maximum simultaneous occupancy.

## Worked Example

For intervals $[5,8]$, $[2,4]$, and $[3,9]$, the events are

$$(2,+1),(3,+1),(4,-1),(5,+1),(8,-1),(9,-1).$$

The running counts are $1,2,1,2,1,0$, so the maximum is $2$.

## Complexity

There are $2n$ events. Sorting costs $O(n\log n)$ and sweeping costs $O(n)$. Memory usage is $O(n)$.
