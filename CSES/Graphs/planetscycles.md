# Planets Cycles

## Problem

- **Source:** [CSES 1751: Planets Cycles](https://cses.fi/problemset/task/1751/)
- **Code:** [`View accepted C++ solution (planetscycles.cpp)`](./planetscycles.cpp)
- **Constraints:** $1\le n\le200000$.

For every starting planet, count the distinct planets visited before the first repetition.

## Idea

Every component of a functional graph consists of one directed cycle with directed trees feeding into it. A journey is therefore a tail followed by a cycle. Every cycle vertex has answer equal to the cycle length; moving one edge backwards along a tail increases the answer by one.

Use three states:

- 0: unvisited;
- 1: on the current journey;
- 2: completely solved.

Record the current path and each vertex's position. Reaching a state-1 vertex identifies a new cycle suffix. Reaching a state-2 vertex enters a component whose answer is already known. In either case, solve the remaining tail backwards.

## Algorithm

1. Start a successor walk from every state-0 planet, recording vertices until a nonzero state is reached.
2. If the endpoint has state 1, use its recorded position to identify the cycle suffix and assign its length to every cycle vertex.
3. Scan the preceding tail backwards, assigning one plus the successor's answer.
4. If the endpoint had state 2, apply the same backward recurrence to the entire new path.
5. Mark all newly solved vertices as state 2.

## Correctness

### Lemma 1

When a walk reaches a state-1 vertex $v$, the path suffix beginning at `ord[v]` is exactly one directed cycle.

#### Proof

State-1 vertices belong to the current path because earlier traversals finish by changing their states to 2. Successor edges join consecutive path entries, and the final edge returns to $v$. No earlier repetition occurred, so this suffix is a simple directed cycle. $\square$

### Lemma 2

The algorithm assigns the correct answer to every newly solved vertex.

#### Proof

By Lemma 1, each vertex of a newly found cycle visits exactly the cycle length before repeating. For a tail vertex, its successor is already solved during the backward scan, and the vertex itself adds exactly one new visit. The same recurrence applies when the path enters a previously solved component. Backward induction proves all assignments. $\square$

### Theorem

The algorithm computes the required number for every planet.

#### Proof

Every state-0 vertex is eventually selected or encountered. Each traversal ends at either its own cycle or a solved component, and Lemma 2 then solves its entire new path. Thus every planet receives its correct answer. $\square$

## Implementation

`ord[v]` matters only while `state[v] == 1`; stale positions of solved vertices are ignored. For a new cycle, cycle answers are assigned before the preceding tail is scanned, so every successor answer used by the recurrence is already available.

## Complexity

Each planet changes state from 0 to 1 to 2 once. The time complexity is $O(n)$ and the auxiliary space is $O(n)$.

## Worked Example

For $1\to2$, $2\to3$, $3\to4$, and $4\to3$, the path `[1,2,3,4]` returns to position 2. Vertices 3 and 4 form a cycle of length 2, so their answers are 2. Scanning backwards gives answer 3 for vertex 2 and 4 for vertex 1.
