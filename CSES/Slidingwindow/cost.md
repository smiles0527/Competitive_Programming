# Sliding Window Cost

## Problem

- **Source:** [CSES 1077: Sliding Window Cost](https://cses.fi/problemset/task/1077/)
- **Code:** [`View accepted C++ solution (cost.cpp)`](./cost.cpp)
- **Limits:** $1\le k\le n\le2\cdot10^5$ and $1\le x_i\le10^9$.

For every contiguous window of length $k$, select a value $m$ and replace all elements in the window with $m$. The replacement cost is the sum of the absolute deviations from $m$. Output the minimum possible cost for every window.

## Idea

For a window containing $x_1,x_2,\ldots,x_k$, the cost of choosing $m$ is

$$
f(m)=\sum_{i=1}^{k}|x_i-m|.
$$

This cost is minimized when $m$ is a median of the window. If $k$ is even, every value between the two central elements gives the same minimum cost, so choosing the smaller one is sufficient.

Maintain the current window in two multisets:

- `l` contains the smallest

  $$
  t=\frac{k+1}{2}
  $$

  elements, using integer division;
- `r` contains the remaining elements.

The invariants are

$$
|l|=t
$$

and

$$
x\le y
\qquad
\text{for every }x\in l,\ y\in r.
$$

Therefore,

$$
m=\max(l)
$$

is the lower median.

In addition, maintain

$$
s_l=\sum_{x\in l}x,
\qquad
s_r=\sum_{x\in r}x.
$$

Every value in `l` is at most $m$, so changing those values to $m$ costs

$$
\sum_{x\in l}(m-x)=m|l|-s_l.
$$

Every value in `r` is at least $m$, so its contribution is

$$
\sum_{x\in r}(x-m)=s_r-m|r|.
$$

Therefore, the minimum window cost is

$$
m|l|-s_l+s_r-m|r|.
$$

## Algorithm

1. Set $t=(k+1)/2$ using integer division.
2. Insert the first $k$ values into `l` and maintain their sum `sl`.
3. Move the largest values from `l` to `r` until $|l|=t$.
4. Compute the first cost using the lower median and the two sums.
5. For every later index $i$:
   - Remove $a_{i-k}$ from whichever multiset contains it.
   - Insert $a_i$ according to the current median boundary.
   - Rebalance until $|l|=t$.
   - Output the cost formula.

## Correctness

We prove that every output is the minimum cost for its window.

**Lemma 1.** After balancing, `l` contains the smallest $t$ elements of the current window.

**Proof.** Balancing ensures that $|l|=t$. Initially, all elements are inserted into `l`, and its largest elements are moved to `r`, so every remaining element of `l` is no greater than every element of `r`.

During a sliding update, removing an element preserves this ordering. If `l` is nonempty, the incoming value is inserted into `l` when it is at most the current boundary and into `r` otherwise. If `l` is empty, it is compared with the smallest value in `r`, preserving the same partition boundary.

If `l` is too large, its largest value moves to `r`. If it is too small, the smallest value of `r` moves to `l`. Both operations preserve the ordering. Thus, `l` has size $t$ and contains exactly the smallest $t$ window elements. $\square$

**Lemma 2.** The value $m=\max(l)$ is a median of the current window.

**Proof.** By Lemma 1, `l` contains the smallest $t$ elements. Its largest value is therefore the $t$-th smallest window value. For odd $k$, this is the unique middle value. For even $k$, $t=k/2$, so it is the smaller middle value. In either case, $m$ is a median. $\square$

**Lemma 3.** Changing every window value to $m$ costs

$$
m|l|-s_l+s_r-m|r|.
$$

**Proof.** For every $x\in l$, Lemma 1 gives $x\le m$, so $|x-m|=m-x$. Summing over `l` gives $m|l|-s_l$. For every $x\in r$, we have $x\ge m$, so $|x-m|=x-m$. Summing over `r` gives $s_r-m|r|$. Adding both parts produces the stated formula. $\square$

**Theorem.** For every window, the algorithm outputs the minimum possible total cost.

**Proof.** By Lemma 2, $m$ is a median of the current window, and a median minimizes the sum of absolute deviations. By Lemma 3, the algorithm calculates exactly the cost of replacing every value with $m$. Therefore, the reported cost is minimum. $\square$

## Implementation

The two sums must use `long long`. A window cost may be as large as approximately

$$
k\cdot10^9\le2\cdot10^{14}.
$$

When moving a value between sets, update both its multiset membership and its contribution to `sl` or `sr`:

```cpp
int x = *it;
l.erase(it);
sl -= x;
r.insert(x);
sr += x;
```

The outgoing value may occur in both multisets when duplicates cross the partition. Removing one copy from either valid set is sufficient:

```cpp
auto it = l.find(x);
if (it != l.end()) {
    l.erase(it);
    sl -= x;
} else {
    r.erase(r.find(x));
    sr -= x;
}
```

If `l` is empty while `r` is nonempty, compare the incoming value with `*r.begin()`. This avoids violating the ordering invariant when $k=2$ and the only value in `l` has just left.

The cost is computed directly from the maintained aggregates:

```cpp
ll m = *prev(l.end());
return m * l.size() - sl + sr - m * r.size();
```

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void bal(multiset<int>& l, multiset<int>& r, ll& sl, ll& sr, int t) {
    while ((int)l.size() > t) {
        auto it = prev(l.end());
        int x = *it;
        l.erase(it);
        sl -= x;
        r.insert(x);
        sr += x;
    }

    while ((int)l.size() < t) {
        auto it = r.begin();
        int x = *it;
        r.erase(it);
        sr -= x;
        l.insert(x);
        sl += x;
    }
}

ll get(const multiset<int>& l, const multiset<int>& r, ll sl, ll sr) {
    ll m = *prev(l.end());
    return m * l.size() - sl + sr - m * r.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    multiset<int> l, r;
    ll sl = 0, sr = 0;
    int t = (k + 1) / 2;

    for (int i = 0; i < k; i++) {
        l.insert(a[i]);
        sl += a[i];
    }

    bal(l, r, sl, sr, t);
    cout << get(l, r, sl, sr);

    for (int i = k; i < n; i++) {
        int x = a[i - k], y = a[i];

        auto it = l.find(x);
        if (it != l.end()) {
            l.erase(it);
            sl -= x;
        } else {
            r.erase(r.find(x));
            sr -= x;
        }

        if (l.empty()) {
            if (r.empty() || y <= *r.begin()) {
                l.insert(y);
                sl += y;
            } else {
                r.insert(y);
                sr += y;
            }
        } else if (y <= *prev(l.end())) {
            l.insert(y);
            sl += y;
        } else {
            r.insert(y);
            sr += y;
        }

        bal(l, r, sl, sr, t);
        cout << ' ' << get(l, r, sl, sr);
    }

    cout << '\n';
}
```

## Complexity

Each window transition performs one multiset deletion, one insertion, and at most a constant number of balancing moves. Each operation costs $O(\log k)$, so the total time complexity is $O(n\log k)$.

The two multisets contain $k$ values in total, so the auxiliary space complexity is $O(k)$.

## Worked Example

For

$$
a=[2,4,3,5,8,1,2,1],
\qquad
k=3,
$$

the maintained partitions and costs are:

| Window | `l` | `r` | Median $m$ | Cost |
|---|---|---|---:|---:|
| $[2,4,3]$ | $\{2,3\}$ | $\{4\}$ | $3$ | $2$ |
| $[4,3,5]$ | $\{3,4\}$ | $\{5\}$ | $4$ | $2$ |
| $[3,5,8]$ | $\{3,5\}$ | $\{8\}$ | $5$ | $5$ |
| $[5,8,1]$ | $\{1,5\}$ | $\{8\}$ | $5$ | $7$ |
| $[8,1,2]$ | $\{1,2\}$ | $\{8\}$ | $2$ | $7$ |
| $[1,2,1]$ | $\{1,1\}$ | $\{2\}$ | $1$ | $1$ |

The output is

$$
2\quad2\quad5\quad7\quad7\quad1.
$$
