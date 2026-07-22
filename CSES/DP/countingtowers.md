# Counting Towers

## Problem

- **Source:** [CSES 2413: Counting Towers](https://cses.fi/problemset/task/2413/)
- **Code:** [`View accepted C++ solution (countingtowers.cpp)`](./countingtowers.cpp)

For each query $n$, count the number of ways to divide a $2\times n$ tower into rectangular blocks with integer dimensions.

Different arrangements are counted separately, including mirrored arrangements.

The answer is required modulo

$$
10^9+7.
$$

## Conceptual Model

When extending a tower by one row, the important information is how the blocks touching the current top boundary are arranged.

There are two possible states:

$$
a_i
$$

is the number of towers of height $i$ where the two top cells belong to different blocks.

$$
b_i
$$

is the number of towers of height $i$ where the two top cells belong to the same width-2 block.

These two states contain all information needed to add the next row.

### Separate Top Blocks

Suppose the previous tower is counted by $a_{i-1}$.

To keep the new top cells separate, each of the two previous blocks may independently:

- continue upward;
- end, with a new block starting above it.

This gives

$$
2\cdot2=4
$$

possibilities.

A joined top can also be created by ending both previous blocks and starting one new width-2 block. This gives one possibility.

### Joined Top Block

Suppose the previous tower is counted by $b_{i-1}$.

To create separate top blocks, the joined block must end and two new blocks must begin. This gives one possibility.

To keep the top joined, either:

- continue the existing width-2 block;
- end it and begin a new width-2 block.

This gives two possibilities.

Therefore,

$$
a_i=4a_{i-1}+b_{i-1},
$$

$$
b_i=a_{i-1}+2b_{i-1}.
$$

The answer for height $i$ is

$$
a_i+b_i.
$$

## Base Case

For height 1, there are two towers:

- two separate $1\times1$ blocks;
- one $2\times1$ block.

Thus,

$$
a_1=1,\qquad b_1=1.
$$

## Algorithm

Read all queries and find the largest requested height $m$.

Starting from

$$
a_1=b_1=1,
$$

compute the two states for every height from 2 to $m$. Store

$$
ans[i]=(a_i+b_i)\bmod(10^9+7).
$$

Then answer every query using the precomputed array.

## Correctness

We prove that $a_i$ and $b_i$ count exactly the towers described by their states.

For height 1, the two possible towers are correctly divided into one separate-state tower and one joined-state tower.

Now assume the states are correct for height $i-1$.

A tower with separate top cells can come from:

- a separate-state tower in one of four ways, depending on whether each top block continues or ends;
- a joined-state tower in one way, by ending the joined block and starting two separate blocks.

Therefore,

$$
a_i=4a_{i-1}+b_{i-1}.
$$

A tower with joined top cells can come from:

- a separate-state tower in one way, by ending both blocks and starting one joined block;
- a joined-state tower in two ways, by either continuing the block or replacing it with a new joined block.

Therefore,

$$
b_i=a_{i-1}+2b_{i-1}.
$$

Every tower has either separate or joined top cells, and the two cases cannot overlap. Hence,

$$
a_i+b_i
$$

counts every tower of height $i$ exactly once.

## Implementation

Only the current values of $a_i$ and $b_i$ are needed while precomputing:

```cpp
ll na = (4 * a + b) % MOD;
ll nb = (a + 2 * b) % MOD;
```

The new values are calculated before replacing the old ones because both transitions depend on the previous height.

`long long` is needed for expressions such as

$$
4a+b,
$$

which may exceed the range of `int` before taking the modulus.

## Complexity

Let $m$ be the largest queried height.

The precomputation takes

$$
O(m)
$$

time, and answering the queries takes

$$
O(t).
$$

The total time complexity is

$$
O(m+t).
$$

The answer array uses

$$
O(m)
$$

memory.

## Worked Example

For height 1,

$$
a_1=1,\qquad b_1=1,
$$

so the answer is

$$
2.
$$

For height 2,

$$
a_2=4a_1+b_1=4\cdot1+1=5,
$$

$$
b_2=a_1+2b_1=1+2\cdot1=3.
$$

Thus,

$$
a_2+b_2=5+3=8.
$$

For height 3,

$$
a_3=4\cdot5+3=23,
$$

$$
b_3=5+2\cdot3=11.
$$

Therefore, the number of towers of height 3 is

$$
23+11=34.
$$
