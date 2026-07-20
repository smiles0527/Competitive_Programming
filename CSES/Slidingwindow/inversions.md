# Sliding Window Inversions

## Problem

- **Source:** [CSES 3223: Sliding Window Inversions](https://cses.fi/problemset/task/3223/)
- **Code:** [`View accepted C++ solution (inversions.cpp)`](./inversions.cpp)
- **Limits:** $1\le k\le n\le2\cdot10^5$ and $1\le x_i\le10^9$.

Print the inversion count for every contiguous sliding window of length $k$. An inversion is a pair of positions $(i,j)$ satisfying $i<j$ and $x_i>x_j$.

## Idea

The direct solution counts inversions independently in every window and takes at least $O(nk)$ time, which is too slow.

Consecutive windows differ in two values:

- The leftmost value leaves.
- A new rightmost value enters.

These two changes have asymmetric effects on inversion pairs.

Suppose the outgoing value is $x=a_p$. Since it is the leftmost element of the current window, it cannot be the second element of an inversion. Every inversion containing it has the form

$$
(a_p,a_q)
\qquad\text{with}\qquad
p<q\text{ and }a_p>a_q.
$$

Removing $x$ therefore deletes exactly

$$
\lvert\{z:z<x\}\rvert
$$

inversions.

After removing $x$, suppose the incoming value is $y=a_r$. Since it is inserted at the rightmost position, it cannot be the first element of an inversion. Every new inversion has the form

$$
(a_j,a_r)
\qquad\text{with}\qquad
j<r\text{ and }a_j>a_r.
$$

Thus, inserting $y$ creates exactly

$$
\lvert\{z:z>y\}\rvert
$$

inversions.

We need dynamic frequency queries for values smaller or greater than a given value. Coordinate compression followed by a Fenwick tree provides both operations in $O(\log n)$ time.

Let `sum(p)` be the number of current-window values whose compressed index is at most $p$. Then

$$
\lvert\{z:z<x\}\rvert=\operatorname{sum}(x-1),
$$

and, after removing the outgoing value,

$$
\lvert\{z:z>y\}\rvert=(k-1)-\operatorname{sum}(y).
$$

The strict inequalities are important because equal values do not form inversions.

## Algorithm

1. Coordinate-compress the array.
2. Build the first window from left to right. For each value $a_i$:
   - Add the number of earlier values greater than it:

     $$
     i-\operatorname{sum}(a_i).
     $$

   - Insert $a_i$ into the Fenwick tree.
3. Output the first inversion count.
4. For every later index $i$:
   - Let $x=a_{i-k}$ and $y=a_i$.
   - Subtract $\operatorname{sum}(x-1)$.
   - Remove $x$ from the Fenwick tree.
   - Add $(k-1)-\operatorname{sum}(y)$.
   - Insert $y$.
   - Output the updated inversion count.

## Correctness

We prove that every output is the inversion count of its corresponding window.

**Lemma 1.** After constructing the first window, `cur` equals its number of inversions.

**Proof.** When processing $a_i$, the Fenwick tree contains exactly the $i$ earlier values

$$
a_0,a_1,\ldots,a_{i-1}.
$$

Among these $i$ values, `sum(a[i])` are at most $a_i$. Therefore,

$$
i-\operatorname{sum}(a_i)
$$

are strictly greater than $a_i$. Each such value forms an inversion ending at $i$. Every inversion has one unique right endpoint, so these contributions count every inversion exactly once. $\square$

**Lemma 2.** Removing the leftmost value $x$ decreases the inversion count by $\operatorname{sum}(x-1)$.

**Proof.** Because $x$ is the leftmost element, it cannot be the second element of an inversion inside the window. Every inversion containing it pairs $x$ with a later value smaller than $x$. The query `sum(x - 1)` counts exactly these values. $\square$

**Lemma 3.** After removing the outgoing value, inserting $y$ increases the inversion count by

$$
(k-1)-\operatorname{sum}(y).
$$

**Proof.** The incoming value $y$ is placed at the rightmost position, so it cannot be the first element of a new inversion. It forms an inversion with every existing value strictly greater than $y$. There are $k-1$ existing values, and `sum(y)` of them are at most $y$. Their difference is exactly the number of new inversions. $\square$

**Theorem.** Every value printed by the algorithm is the inversion count of the corresponding window.

**Proof.** By Lemma 1, the first maintained count is correct. During each slide, pairs consisting only of elements shared by the two windows do not change. By Lemma 2, the algorithm removes exactly the inversions involving the outgoing value. By Lemma 3, it adds exactly the inversions involving the incoming value. Thus, the updated count is the inversion count of the next window. By induction, every printed value is correct. $\square$

## Implementation

Compression preserves comparisons:

$$
x<y
\iff
\operatorname{id}(x)<\operatorname{id}(y).
$$

The first-window contribution is

```cpp
cur += i - sum(a[i]);
```

because the tree currently contains $i$ values, and `sum(a[i])` counts those not greater than $a_i$.

The outgoing contribution must be queried before removing the value:

```cpp
cur -= sum(x - 1);
add(x, -1);
```

The incoming contribution is queried after removal, when the tree contains exactly $k-1$ values:

```cpp
cur += k - 1 - sum(y);
add(y, 1);
```

The inversion count requires `long long` because its maximum is

$$
\frac{k(k-1)}{2},
$$

which can approach $2\cdot10^{10}$.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int bit[200005], m;

void add(int i, int v) {
    for (i++; i <= m; i += i & -i) bit[i] += v;
}

int sum(int i) {
    int s = 0;
    for (i++; i; i -= i & -i) s += bit[i];
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n), b;
    for (int i = 0; i < n; i++) cin >> a[i];

    b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());

    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    }

    m = b.size();
    ll cur = 0;

    for (int i = 0; i < k; i++) {
        cur += i - sum(a[i]);
        add(a[i], 1);
    }

    cout << cur;

    for (int i = k; i < n; i++) {
        int x = a[i - k], y = a[i];

        cur -= sum(x - 1);
        add(x, -1);

        cur += k - 1 - sum(y);
        add(y, 1);

        cout << ' ' << cur;
    }

    cout << '\n';
}
```

## Complexity

Coordinate compression takes $O(n\log n)$ time. Each value causes a constant number of Fenwick updates and queries, each costing $O(\log n)$. Therefore, the total time complexity is $O(n\log n)$.

The array, compressed values, and Fenwick tree use $O(n)$ memory.

## Worked Example

For

$$
a=[1,2,3,2,5,2,4,4],
\qquad
k=3,
$$

the windows are:

| Window | Outgoing contribution | Incoming contribution | Inversions |
|---|---:|---:|---:|
| $[1,2,3]$ | - | - | $0$ |
| $[2,3,2]$ | $0$ from $1$ | $1$ for $2$ | $1$ |
| $[3,2,5]$ | $0$ from $2$ | $0$ for $5$ | $1$ |
| $[2,5,2]$ | $1$ from $3$ | $1$ for $2$ | $1$ |
| $[5,2,4]$ | $0$ from $2$ | $1$ for $4$ | $2$ |
| $[2,4,4]$ | $2$ from $5$ | $0$ for $4$ | $0$ |

The output is

$$
0\quad1\quad1\quad1\quad2\quad0.
$$
