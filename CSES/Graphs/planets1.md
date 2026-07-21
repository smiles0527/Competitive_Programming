# Planets Queries I

## Problem

- **Source:** [CSES 1750: Planets Queries I](https://cses.fi/problemset/task/1750/)
- **Code:** [`View accepted C++ solution (planets1.cpp)`](./planets1.cpp)
- **Constraints:** $1\le n,q\le200000$ and $1\le k\le10^9$.

Each planet has one outgoing teleport. For every query $(x,k)$, find the planet reached after exactly $k$ teleports.

## Idea

Step-by-step simulation costs $O(k)$ per query. Instead, precompute

$$
up[j][v]=\text{the planet reached from }v\text{ after }2^j\text{ teleports}.
$$

The base layer is the given teleport function. Two consecutive $2^{j-1}$ jumps form a $2^j$ jump:

$$
up[j][v]=up[j-1][up[j-1][v]].
$$

Decompose each query count into powers of two and apply the corresponding jumps.

## Algorithm

1. Read direct teleports into `up[0]`.
2. Build layers 1 through 29 by composing the preceding layer with itself.
3. For each query, process every set bit $j$ of $k$ and update `x = up[j][x]`.
4. Print the final planet.

## Correctness

### Lemma 1

For every $j$ and $v$, `up[j][v]` is the destination after exactly $2^j$ teleports from $v$.

#### Proof

The claim is the input definition for $j=0$. For $j>0$, the recurrence performs two jumps of $2^{j-1}$ teleports, totaling $2^j$. Induction proves every layer. $\square$

### Theorem

Every query is answered correctly.

#### Proof

Each set bit $j$ applies exactly $2^j$ teleports by Lemma 1. Their sum is the binary representation of $k$, so the final state is reached after exactly $k$ applications of the teleport function. $\square$

## Implementation

Thirty layers cover all $k\le10^9$. Every table entry is a valid planet because the teleport function is total, so no sentinel state is needed.

## Complexity

Preprocessing takes $O(n\log 10^9)$ time and space. Each query takes $O(\log 10^9)$ time.

## Worked Example

Suppose $1\to2$, $2\to3$, $3\to4$, and $4\to2$. For $(1,5)$, binary $5=101_2$ applies a one-step jump and a four-step jump. The trajectory is $1,2,3,4,2,3$, so the reported planet is 3.
