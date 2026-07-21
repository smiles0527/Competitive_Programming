# Sliding Window Median

## Problem

- **Source:** [CSES 1076: Sliding Window Median](https://cses.fi/problemset/task/1076/)
- **Code:** [`View accepted C++ solution (median.cpp)`](../median.cpp)
- **Limits:** $1\le k\le n\le2\cdot10^5$ and $1\le x_i\le10^9$.

Find the medians of all contiguous subarrays of length $k$. If $k$ is even, output the smaller of the two middle values.

The required position in sorted order is

$$
t=\lceil k/2\rceil=\frac{k+1}{2},
$$

where the final expression uses integer division.

## Solution Idea

The direct solution that sorts every subarray independently takes $O(nk\log k)$ time in the worst case.

Two consecutive subarrays differ in only two values, so maintain the current subarray in two multisets:

- `l` contains the smallest $t$ elements;
- `r` contains the remaining elements.

Maintain the invariants

$$
|l|=t
$$

and

$$
x\le y
\qquad
\text{for every }x\in l,\ y\in r.
$$

The largest value in `l` is therefore the $t$-th smallest value in the current subarray:

$$
\operatorname{median}=*\operatorname{prev}(\texttt{l.end()}).
$$

Insert a value $x$ into `l` if it is no greater than the largest value currently in `l`; otherwise, insert it into `r`.

After a removal and insertion, rebalance the sizes:

- If `l` is too large, move its largest value to `r`.
- If `l` is too small, move the smallest value of `r` to `l`.

This process preserves the ordering between the two multisets.

## Algorithm

1. Insert the first $k$ values into `l`.
2. Move the largest values from `l` to `r` until $|l|=t$.
3. Output the largest element of `l`.
4. For every index $i$ from $k$ to $n-1$:
   - Remove $a_{i-k}$ from whichever multiset contains it.
   - Insert $a_i$ into `l` or `r` according to the current boundary.
   - Rebalance until $|l|=t$.
   - Output the largest element of `l`.

## Correctness

We prove that every printed value is the required median.

**Lemma 1.** After rebalancing, $|l|=t$.

**Proof.** If $|l|>t$, the algorithm moves its largest value to `r`. If $|l|<t$, it moves the smallest value of `r` to `l`. Each move changes $|l|$ by one toward $t$, so the process stops with $|l|=t$. $\square$

**Lemma 2.** After every update and rebalance, every value in `l` is no greater than every value in `r`.

**Proof.** Initially, all first-window values are inserted into `l`. Rebalancing moves the largest values from `l` to `r`, so the remaining values in `l` are no greater than those in `r`.

Assume the property holds before a sliding update. Removing the outgoing value does not change the relative order of the remaining values. If `l` is nonempty, the incoming value $x$ is inserted into `l` when $x\le\max(l)$ and into `r` otherwise. If `l` is empty, comparing $x$ with $\min(r)$ places it on the correct side of the existing boundary.

If `l` becomes too large, moving its largest value to `r` leaves only smaller values in `l`. If `l` becomes too small, moving the smallest value of `r` to `l` adds a value no greater than every value remaining in `r`. Thus, the ordering property is preserved. $\square$

**Lemma 3.** After rebalancing, `l` contains the smallest $t$ elements of the current window.

**Proof.** By Lemma 1, `l` contains exactly $t$ elements. By Lemma 2, no value in `r` is smaller than a value in `l`. Therefore, `l` contains exactly the smallest $t$ elements of the current subarray. $\square$

**Theorem.** Every value printed by the algorithm is the required median of its window.

**Proof.** By Lemma 3, `l` contains the smallest $t$ elements of the current window. Its largest element is therefore the $t$-th smallest element. For odd $k$, this is the unique middle value. For even $k$, $t=k/2$, so it is the smaller of the two middle values. Thus, `*prev(l.end())` is exactly the required median. $\square$

## Implementation

The median is read using

```cpp
*prev(l.end())
```

because `multiset` is sorted and `prev(l.end())` points to its largest element.

When removing an outgoing value, it may occur in either set:

```cpp
auto it = l.find(x);
if (it != l.end()) l.erase(it);
else r.erase(r.find(x));
```

If duplicate copies of the same value occur in both sets, removing either copy is valid. The complete window multiset remains correct, and rebalancing restores the required size.

Insertion follows the current boundary:

```cpp
if (l.empty()) {
    if (r.empty() || a[i] <= *r.begin()) l.insert(a[i]);
    else r.insert(a[i]);
} else if (a[i] <= *prev(l.end())) {
    l.insert(a[i]);
} else {
    r.insert(a[i]);
}
```

If `l` is empty while `r` is not, the new value is compared with the smallest value in `r`. Inserting a larger value into `r` lets rebalancing move the correct boundary value into `l`. This case can occur for $k=2$ after the sole element of `l` leaves.

Rebalancing moves only boundary elements:

```cpp
auto it = prev(l.end());
r.insert(*it);
l.erase(it);
```

or

```cpp
auto it = r.begin();
l.insert(*it);
r.erase(it);
```

so the ordering invariant remains valid.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

void bal(multiset<int>& l, multiset<int>& r, int t) {
    while ((int)l.size() > t) {
        auto it = prev(l.end());
        r.insert(*it);
        l.erase(it);
    }

    while ((int)l.size() < t) {
        auto it = r.begin();
        l.insert(*it);
        r.erase(it);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    multiset<int> l, r;
    int t = (k + 1) / 2;

    for (int i = 0; i < k; i++) l.insert(a[i]);
    bal(l, r, t);

    cout << *prev(l.end());

    for (int i = k; i < n; i++) {
        int x = a[i - k];

        auto it = l.find(x);
        if (it != l.end()) l.erase(it);
        else r.erase(r.find(x));

        if (l.empty()) {
            if (r.empty() || a[i] <= *r.begin()) l.insert(a[i]);
            else r.insert(a[i]);
        } else if (a[i] <= *prev(l.end())) {
            l.insert(a[i]);
        } else {
            r.insert(a[i]);
        }

        bal(l, r, t);
        cout << ' ' << *prev(l.end());
    }

    cout << '\n';
}
```

## Complexity

Each transition between consecutive subarrays performs one deletion, one insertion, and at most a constant number of balancing moves. Each operation costs $O(\log k)$, so the total time complexity is $O(n\log k)$, where $n$ is the length of the input array.

The two multisets contain exactly $k$ values in total, so the auxiliary space complexity is $O(k)$.

## Worked Example

For

$$
a=[2,4,3,5,8,1,2,1],
\qquad
k=3,
$$

we have $t=(3+1)/2=2$. Thus, `l` contains the smallest two values of each window.

| Window | `l` | `r` | Median |
|---|---|---|---:|
| $[2,4,3]$ | $\{2,3\}$ | $\{4\}$ | $3$ |
| $[4,3,5]$ | $\{3,4\}$ | $\{5\}$ | $4$ |
| $[3,5,8]$ | $\{3,5\}$ | $\{8\}$ | $5$ |
| $[5,8,1]$ | $\{1,5\}$ | $\{8\}$ | $5$ |
| $[8,1,2]$ | $\{1,2\}$ | $\{8\}$ | $2$ |
| $[1,2,1]$ | $\{1,1\}$ | $\{2\}$ | $1$ |

The output is

$$
3\quad4\quad5\quad5\quad2\quad1.
$$
