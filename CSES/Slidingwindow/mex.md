# Sliding Window Mex

## Problem

- **Source:** [CSES 3225: Sliding Window Mex](https://cses.fi/problemset/task/3225/)
- **Code:** [`View accepted C++ solution (mex.cpp)`](./mex.cpp)
- **Limits:** $1\le k\le n\le2\cdot10^5$ and $0\le x_i\le10^9$.

Output the mex of every contiguous window of length $k$. The mex is the smallest nonnegative integer that does not appear in the window.

## Idea

Computing the mex independently for each window takes $O(k)$ time per window, resulting in $O(nk)$ time overall.

An important observation is that the mex of a length-$k$ window cannot exceed $k$, because the window contains only $k$ elements. There are $k+1$ values

$$
0,1,\ldots,k,
$$

but only $k$ positions in the window. Thus, at least one value in $[0,k]$ does not appear, and values greater than $k$ cannot affect the mex.

Maintain

$$
\operatorname{cnt}[v]=\text{the frequency of }v
$$

for every $0\le v\le k$, together with the set

$$
s=\{v\in[0,k]:\operatorname{cnt}[v]=0\}.
$$

The current mex is the smallest element of `s`:

$$
\operatorname{mex}=*\texttt{s.begin()}.
$$

During an insertion, remove $v$ from `s` if its frequency increases from $0$ to $1$. During a deletion, insert $v$ into `s` if its frequency decreases from $1$ to $0$.

The input can be processed online. Store the current window in a circular array `q` of length $k$. When processing zero-based index $i\ge k$, position $i\bmod k$ contains the value from index $i-k$, which must leave before the position is overwritten.

## Algorithm

1. Initialize `s` with all values from $0$ through $k$.
2. For each zero-based index $i$:
   - Input the new value $x$.
   - If $i\ge k$, remove `q[i % k]` from the maintained window.
   - Store $x$ at `q[i % k]`.
   - Add $x$ to the maintained window.
   - If $i\ge k-1$, output `*s.begin()`.

Values greater than $k$ are stored in the circular buffer but do not update `cnt` or `s`.

## Correctness

We prove that every output is the mex of its corresponding window.

**Lemma 1.** After each update, $\operatorname{cnt}[v]$ equals the number of occurrences of $v$ in the current window for every $0\le v\le k$.

**Proof.** During the first $k$ iterations, the algorithm inserts exactly the elements of the first window, so `cnt` contains their frequencies. For every later index $i$, `q[i % k]` contains the outgoing element from index $i-k$. The algorithm decreases its frequency and increases the frequency of the incoming value. All elements shared by the two consecutive windows keep their frequencies. Thus, `cnt` contains exactly the current frequencies. $\square$

**Lemma 2.** After each update,

$$
s=\{v\in[0,k]:\operatorname{cnt}[v]=0\}.
$$

**Proof.** Initially, every frequency is zero and every value from $0$ through $k$ belongs to `s`. When a value's frequency changes from $0$ to $1$, the algorithm removes it from `s`. When its frequency changes from $1$ to $0$, the algorithm inserts it into `s`. Frequency changes that remain positive do not affect whether the value is missing. Thus, `s` always contains exactly the zero-frequency values. $\square$

**Theorem.** Every printed value is the mex of the current window.

**Proof.** A length-$k$ window has mex at most $k$, so its mex belongs to $[0,k]$. By Lemma 1, `cnt` contains the current frequencies. By Lemma 2, `s` contains exactly the values in $[0,k]$ absent from the window. Therefore, its smallest element is the smallest absent nonnegative integer, which is precisely the mex. $\square$

## Implementation

The outgoing value is read before its circular-buffer position is overwritten:

```cpp
int y = q[i % k];
if (y <= k && --cnt[y] == 0) s.insert(y);
```

Insertion removes a value from the missing set only when its previous frequency was zero:

```cpp
if (x <= k && cnt[x]++ == 0) s.erase(x);
```

Values greater than $k$ are ignored by the frequency structure because they cannot be the mex.

The set is never empty. A window of length $k$ cannot contain all $k+1$ values from $0$ through $k$.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> q(k), cnt(k + 1);
    set<int> s;
    for (int i = 0; i <= k; i++) s.insert(i);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        if (i >= k) {
            int y = q[i % k];
            if (y <= k && --cnt[y] == 0) s.insert(y);
        }

        q[i % k] = x;
        if (x <= k && cnt[x]++ == 0) s.erase(x);

        if (i >= k - 1) {
            if (i >= k) cout << ' ';
            cout << *s.begin();
        }
    }

    cout << '\n';
}
```

## Complexity

Every element causes at most one set insertion and one set deletion, each costing $O(\log k)$. The total time complexity is $O(n\log k)$.

The circular buffer, frequency array, and missing-value set use $O(k)$ auxiliary space.

## Worked Example

For

$$
a=[1,2,1,0,5,1,1,0],
\qquad
k=3,
$$

the maintained windows are:

| Window | Present relevant values | Missing values begin with | Mex |
|---|---|---|---:|
| $[1,2,1]$ | $1,2$ | $0,3,\ldots$ | $0$ |
| $[2,1,0]$ | $0,1,2$ | $3,4,\ldots$ | $3$ |
| $[1,0,5]$ | $0,1$ | $2,3,\ldots$ | $2$ |
| $[0,5,1]$ | $0,1$ | $2,3,\ldots$ | $2$ |
| $[5,1,1]$ | $1$ | $0,2,\ldots$ | $0$ |
| $[1,1,0]$ | $0,1$ | $2,3,\ldots$ | $2$ |

The output is

$$
0\quad3\quad2\quad2\quad0\quad2.
$$
