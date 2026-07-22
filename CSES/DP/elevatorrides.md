# Elevator Rides

## Problem

- **Source:** [CSES 1653: Elevator Rides](https://cses.fi/problemset/task/1653/)
- **Code:** [`View accepted C++ solution (elevatorrides.cpp)`](./elevatorrides.cpp)

There are $n$ people, each with weight $w_i$, and an elevator with maximum capacity $x$.

Every person must be taken to the top, and each person participates in exactly one ride. Find the minimum number of elevator rides.

Since

$$
n\le 20,
$$

a dynamic program over all subsets is possible.

## Observation

Because $n\le20$, dynamic programming over all subsets is possible.

## Idea

A subset state must contain more information than only the number of completed rides.

Suppose two arrangements both use three rides, but the last ride weighs $4$ in one arrangement and $9$ in the other. The first arrangement is better because it leaves more capacity for the remaining people.

For every subset `mask`, define

$$
dp[\text{mask}]=(\text{rides},\text{last}),
$$

where:

* `rides` is the minimum number of rides needed for the people in `mask`;
* `last` is the minimum total weight of the final ride among arrangements using that number of rides.

States are compared lexicographically:

1. fewer rides is better;
2. if the number of rides is equal, a smaller final-ride weight is better.

## Transition

Consider a nonempty subset `mask`. Choose a person $i$ contained in it and remove that person temporarily.

Let

$$
\text{prev}=\text{mask}\setminus\{i\}.
$$

Start from the optimal state for `prev`.

If person $i$ fits in the final ride,

$$
dp[\text{prev}].\text{last}+w_i\le x,
$$

then the candidate state is

$$
\left(
dp[\text{prev}].\text{rides},
dp[\text{prev}].\text{last}+w_i
\right).
$$

Otherwise, person $i$ starts a new ride:

$$
\left(
dp[\text{prev}].\text{rides}+1,
w_i
\right).
$$

Try every possible final added person $i$ and keep the smallest pair.

## Base Case

We use

$$
dp[0]=(1,0).
$$

This represents one initially empty ride. The first added person always fits into it, so a nonempty subset receives the correct ride count without requiring a special case.

## Algorithm

1. Initialize every subset to an impossible pair.
2. Set $dp[0]=(1,0)$.
3. Process every nonempty subset.
4. For each person contained in the subset:

   * remove that person;
   * extend the resulting smaller subset state;
   * either place the person in the final ride or start a new ride;
   * minimize the resulting pair.
5. Output the ride count for the subset containing all people.

## Correctness

We prove that $dp[\text{mask}]$ stores the optimal pair for every subset.

Consider an optimal arrangement for a nonempty subset `mask`. Choose the final person $i$ added when constructing this arrangement.

Before adding $i$, the remaining people form the subset

$$
\text{mask}\setminus\{i\}.
$$

By the DP definition, the algorithm knows the best arrangement for this smaller subset.

If $i$ fits in its final ride, adding $i$ there does not increase the number of rides. Otherwise, a new ride is necessary.

The algorithm tries every person $i$ as the final added person, so it considers the construction corresponding to every possible optimal arrangement.

Among candidates with the same number of rides, retaining the smallest final-ride weight is safe because it leaves at least as much unused capacity for future additions.

Therefore, the lexicographically smallest candidate gives the minimum ride count and, among those solutions, the best final-ride weight. Hence, the state is correct.

For the full subset, the first component of the pair is the minimum number of elevator rides.

## Complexity

There are

$$
2^n
$$

subsets, and each subset checks at most $n$ people.

The time complexity is

$$
O(n2^n).
$$

The DP array stores one pair for every subset, so the memory complexity is

$$
O(2^n).
$$

## Worked Example

Let

$$
x=10
$$

and the weights be

$$
[4,8,6,1].
$$

One optimal construction is:

* first ride: $4+6=10$;
* second ride: $8+1=9$.

Thus, all four people can be transported in

$$
2
$$

rides.

The subset DP considers all possible orders in which people could be added and keeps the arrangement with the fewest rides. When two arrangements use the same number of rides, it keeps the one whose final ride is lighter.
