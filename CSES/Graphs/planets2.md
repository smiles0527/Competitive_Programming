# Planets Queries II

## Problem

- **Source:** [CSES 1160: Planets Queries II](https://cses.fi/problemset/task/1160/)
- **Code:** [`View accepted C++ solution (planets2.cpp)`](./planets2.cpp)
- **Constraints:** $1\le n,q\le200000$.

For each ordered pair $(a,b)$ in a functional graph, find the minimum number of teleports needed to reach $b$ from $a$, or print `-1` if this is impossible.

## Idea

Each component contains one directed cycle with directed trees feeding into it. Precompute for every vertex:

- `cyc[v]`: its cycle component;
- `dep[v]`: its distance to the cycle;
- `ent[v]`: the first cycle vertex it reaches;
- `pos[v]`: its position if it lies on the cycle.

```mermaid
flowchart LR
    A[tail vertex a] --> B[tail]
    B --> E[entry ent[a]]
    E --> C1[cycle position p]
    C1 --> C2[cycle position p+1]
    C2 --> C3[cycle position p+2]
    C3 --> C1
```

Queries split according to the target. If $b$ lies on a cycle, $a$ must belong to the same component; walk `dep[a]` steps to `ent[a]`, then move forward around the cycle to $b$. If $b$ lies in a tail, depth must decrease by exactly `dep[a] - dep[b]`; binary lifting checks whether that jump from $a$ lands on $b$.

## Algorithm

1. Follow successor paths with three colors to identify and label every directed cycle.
2. Run multi-source BFS from all cycle vertices over reversed edges, assigning each tail's cycle, depth, and entry.
3. Build the binary-lifting successor table.
4. For each query $(a,b)$:
   - if $b$ is on a cycle, require `cyc[a] == cyc[b]` and add the tail distance to the forward cyclic distance;
   - otherwise, lift $a$ by `dep[a] - dep[b]` when this value is nonnegative, and accept only if the result equals $b$.

## Correctness

### Lemma 1

Preprocessing assigns every vertex its correct cycle, depth, and first cycle entry.

#### Proof

Reaching a color-1 vertex on the current successor path identifies exactly the cycle suffix. Those vertices receive depth zero and themselves as entries. In reverse BFS, a predecessor has the processed vertex as its unique successor, so it reaches the same cycle and entry in one additional step. Induction over BFS layers labels every tail correctly. $\square$

### Lemma 2

When $b$ is a cycle vertex, the algorithm returns the minimum distance from $a$ to $b$, or `-1` exactly when $b$ is unreachable.

#### Proof

The unique trajectory from $a$ reaches `ent[a]` after `dep[a]` steps and then follows its cycle forward. It reaches $b$ exactly when both vertices have the same cycle identifier. The modular position difference is the unique smallest nonnegative forward distance from the entry to $b$. $\square$

### Lemma 3

When $b$ is a tail vertex, the algorithm returns the minimum distance from $a$ to $b$, or `-1` exactly when $b$ is unreachable.

#### Proof

Every tail edge decreases depth by one. Therefore reaching $b$ requires exactly `dep[a] - dep[b]` steps and requires this difference to be nonnegative. Binary lifting follows the unique trajectory by that distance, so equality with $b$ is both necessary and sufficient. $\square$

### Theorem

The algorithm answers every query correctly.

#### Proof

Every target is either on a cycle or in a tail. Lemmas 2 and 3 correctly handle these exhaustive cases. $\square$

## Implementation

`onc[v]` distinguishes cycle targets from tail targets. The cycle distance is normalized as `((pos[b] - pos[entry]) % L + L) % L`. With $n\le200000<2^{18}$, 18 lifting layers cover every relevant tail-depth difference.

## Complexity

Preprocessing takes $O(n\log n)$ time and $O(n\log n)$ space. Each query takes $O(1)$ when the target is on a cycle and $O(\log n)$ otherwise, for total time $O((n+q)\log n)$.

## Worked Example

Let $1\to2$, $2\to3$, $3\to4$, $4\to3$, and $5\to2$. The cycle is $3\to4\to3$. Query $(1,4)$ takes two tail steps to 3 and one cycle step to 4, so the answer is 3. Query $(5,2)$ has depth difference 1 and lifting lands on 2. Query $(2,5)$ fails because the unique forward trajectory from 2 never reaches 5.
