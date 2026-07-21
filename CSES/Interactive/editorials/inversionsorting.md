# Inversion Sorting

- **Problem:** [CSES 3140](https://cses.fi/problemset/task/3140)
- **Code:** [View accepted C++ solution (inversionsorting.cpp)](../inversionsorting.cpp)

## Problem

Sort a hidden permutation using subarray reversals. After each reversal, the grader reveals the current inversion count. At most $4n$ operations are allowed.

## Idea

Maintain that the first $k$ positions are sorted. Let $v$ be the value at position $k+1$, and let $r$ be the number of prefix values greater than $v$. These are the final $r$ values of the sorted prefix, so inserting $v$ before them extends the sorted prefix.

We can recover $r$ from one reversible probe. Let $L=k+1$ and $C=\binom L2$. Before reversing $[1,L]$, the only inversions inside it are the $r$ pairs involving $v$. Reversal flips the relative order of every internal pair, so afterward there are $C-r$ internal inversions. Pairs with outside positions do not change. If inversion count changes from $I$ to $I'$, then

$$I'-I=C-2r,
\qquad
r=\frac{C-(I'-I)}2.$$

Reverse the prefix again to restore it. To insert $v$, reverse the block consisting of the $r$ larger values followed by $v$, then reverse only the formerly larger values. This rotates $v$ before them while restoring their increasing order. The case $r=1$ needs one swap reversal, and $r=0$ needs none.

## Algorithm

First reverse $[1,2]$ twice to learn the original inversion count while restoring the permutation. For $k=1$ through $n-1$, probe and restore prefix $[1,k+1]$, derive $r$, then perform zero, one, or two insertion reversals as above. Stop immediately whenever the grader reports zero inversions.

## Correctness

**Lemma 1.** The probe formula computes the exact number $r$ of prefix elements greater than the next value.

**Proof.** Reversal complements all $C$ internal pair orders, changing internal inversions from $r$ to $C-r$. No pair with an outside position changes because all probed positions remain before every outside position. Rearranging the observed difference gives the formula.

**Lemma 2.** The insertion reversals transform a sorted length-$k$ prefix followed by $v$ into a sorted length-$(k+1)$ prefix.

**Proof.** Write the prefix as $A B$, where $B$ contains the $r$ values greater than $v$. Reversing $Bv$ produces $v\,reverse(B)$, and reversing the trailing `reverse(B)` restores $B$, yielding $AvB$. All values in $A$ are smaller than $v$, and all in $B$ are larger.

**Theorem.** The algorithm sorts the hidden permutation within the operation limit.

**Proof.** The length-one prefix is sorted. Lemmas 1 and 2 extend the invariant by one each iteration, so eventually the full permutation is sorted. Each iteration uses two probes and at most two insertion reversals; the initial two operations fit within the $4n$ allowance, with early termination when inversion count reaches zero.

## Complexity

At most $4n$ interactive reversals are issued. Local work is $O(n)$ and space is $O(1)$.

## Implementation

`rev(l,r)` both performs the action and reads the resulting inversion count. A zero response terminates immediately as required by the protocol. The special $n=1$ case uses the only legal trivial reversal.


## Worked Example

Suppose the sorted prefix is $(1,4,7)$ and the next value is $3$. Here $L=4,C=6$, and $r=2$. The probe changes internal inversions from $2$ to $4$, confirming $r=(6-2)/2=2$. The block $(4,7,3)$ is reversed to $(3,7,4)$, then $(7,4)$ is reversed, producing sorted prefix $(1,3,4,7)$.

## Takeaway

An aggregate interactive response can reveal hidden local structure through a reversible probe. Derive the exact change caused by an operation, undo it, then use the recovered parameter constructively.

## Related Problems

Hidden Permutation, Reversal Sorting, Sorting Methods.
