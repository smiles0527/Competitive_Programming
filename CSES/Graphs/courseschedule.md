# Course Schedule

## Problem

- **Source:** [CSES 1679: Course Schedule](https://cses.fi/problemset/task/1679/)
- **Code:** [`View accepted C++ solution (courseschedule.cpp)`](./courseschedule.cpp)
- **Constraints:** $1\le n\le100000$ and $1\le m\le200000$.

Arrange the courses in a linear order so that every prerequisite appears before the course depending on it, or report that this is impossible.

## Idea

Represent each prerequisite relation by a directed edge from the prerequisite to the dependent course. A consistent course order is exactly a topological ordering of this graph.

A vertex of indegree zero has no prerequisite left and can be scheduled next. Removing it decreases the indegrees of its outgoing neighbors. Repeating this procedure is Kahn's algorithm.

If fewer than $n$ vertices are selected, every remaining vertex has positive indegree inside the remaining subgraph. Following incoming edges must eventually revisit a vertex, producing a directed cycle. Such a cycle makes a valid schedule impossible.

## Algorithm

Compute all indegrees and initialize a queue with the zero-indegree vertices. Repeatedly remove one vertex, append it to the order, decrement the indegrees of its outgoing neighbors, and enqueue every neighbor whose indegree becomes zero. Accept the result exactly when it contains all $n$ vertices.

## Correctness

Each vertex is appended only after all its incoming edges have been removed, so every prerequisite is already present earlier in the order. Any complete output is therefore a valid schedule.

If the procedure stops early, the remaining subgraph contains a directed cycle, so no topological ordering exists. Conversely, every nonempty directed acyclic graph has a vertex of indegree zero, so an acyclic remainder cannot cause early termination. Hence the algorithm reports impossibility exactly when required.

## Implementation

Each incoming edge is removed from an indegree exactly once. The queue may choose among several zero-indegree vertices, so different valid outputs are possible. Uniqueness is not required.

## Complexity

The time complexity is $O(n+m)$ and the space complexity is $O(n+m)$.

## Worked Example

With edges $1\to3$ and $2\to3$, the initial queue contains courses 1 and 2. After both are emitted, course 3 reaches indegree zero. Both `1 2 3` and `2 1 3` are valid schedules.
