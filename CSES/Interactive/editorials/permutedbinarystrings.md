# Permuted Binary Strings

- **Problem:** [CSES 3228](https://cses.fi/problemset/task/3228)
- **Code:** [View accepted C++ solution (permutedbinarystrings.cpp)](../permutedbinarystrings.cpp)

## Problem

Recover a hidden permutation $a_1,\ldots,a_n$. For a queried binary string $b$, the grader returns $b_{a_1}b_{a_2}\ldots b_{a_n}$. At most ten queries are allowed for $n\le1000$.

## Idea

Each query can reveal one bit of every hidden value simultaneously. For bit position $t$, query the string whose position $j$ contains bit $t$ of the binary representation of $j$. The response at output position $i$ is then precisely bit $t$ of $a_i$.

Repeating for all $B=\lceil\log_2(n+1)\rceil$ bits reconstructs every permutation value. Since $n\le1000$, $B\le10$, meeting the query limit.

## Algorithm

For each bit $t=0,\ldots,B-1$, build a length-$n$ query string with character $j$ equal to bit $t$ of index $j$. After receiving the permuted response, set that bit in every answer $a_i$ whose response character is one. Print all recovered values.

## Correctness

**Lemma 1.** Response position $i$ to query $t$ equals bit $t$ of hidden value $a_i$.

**Proof.** The grader returns query character at original index $a_i$. That character was defined as bit $t$ of its index.

**Theorem.** The algorithm reconstructs the entire hidden permutation.

**Proof.** By Lemma 1, every query recovers one binary digit of every $a_i$. The chosen $B$ bits uniquely encode all integers from $1$ through $n$, so combining them yields each value exactly.

## Complexity

The algorithm asks $B=\lceil\log_2(n+1)\rceil\le10$ queries. Local time is $O(n\log n)$ and space is $O(n)$.

## Implementation

Indices are encoded one-based, matching the hidden permutation values. Responses are accumulated with bitwise OR. Every query and the final answer is flushed immediately.


## Worked Example

For $n=3$ and hidden permutation $(1,3,2)$, bit-zero query `101` returns `110`, giving low bits $(1,1,0)$. Bit-one query `011` returns `110`, giving high bits $(0,1,1)$. Combining them yields $(1,3,2)$.

## Takeaway

Interactive queries can be designed as parallel information channels. Encode object identities bit by bit so one response reveals the same bit for every permuted position.

## Related Problems

Hidden Permutation, Counting Bits, Inverse Suffix Array.
