# Sliding Window Mode

## Problem

- **Source:** [CSES 3224: Sliding Window Mode](https://cses.fi/problemset/task/3224/)
- **Code:** [`View accepted C++ solution (mode.cpp)`](./mode.cpp)
- **Limits:** $1\le k\le n\le2\cdot10^5$ and $1\le x_i\le10^9$.

For every contiguous window of length $k$, output its mode. The mode is the value with greatest frequency. If several values have the same maximum frequency, choose the smallest one.

## Idea

Calculating a new frequency table for every window takes $O(nk)$ time in the worst case. Consecutive windows differ only in the outgoing value $a_{i-k}$ and the incoming value $a_i$, so maintain each value's frequency while sliding.

Knowing the frequencies alone is insufficient. After every update, we must efficiently find the value maximizing

$$
(\text{frequency},-\text{value}).
$$

Equivalently, store each present value $v$ in an ordered set as

$$
(-\operatorname{cnt}[v],v).
$$

C++ orders pairs lexicographically. Therefore:

1. A smaller $-\operatorname{cnt}[v]$ means a larger frequency.
2. If frequencies are equal, the smaller $v$ comes first.

The first pair in the set consequently represents the mode.

Values may reach $10^9$, so compress them. After sorting all distinct values, replace each value by its position in the sorted list. The compressed indices preserve numerical order:

$$
u<v
\iff
\operatorname{id}(u)<\operatorname{id}(v).
$$

Using a compressed index as the second component of the pair therefore preserves the required smallest-value tie-break.

Whenever a frequency changes, remove the value's old pair before changing its count, then insert the updated pair. Values with frequency zero are not stored.

## Algorithm

1. Read the array.
2. Sort a copy and remove duplicates.
3. Replace every value with its compressed index.
4. Maintain:
   - `cnt[v]`, the frequency of compressed value $v$;
   - a set `s` containing $(-\operatorname{cnt}[v],v)$ for every present value.
5. Insert the first $k$ elements.
6. Output the original value represented by `s.begin()`.
7. For every later index $i$:
   - Remove one occurrence of $a_{i-k}$.
   - Add one occurrence of $a_i$.
   - Output the value represented by `s.begin()`.

If the outgoing and incoming compressed values are equal, the frequency table does not change, so no set update is needed.

## Correctness

We prove that every value output by the algorithm is the mode of its window.

**Lemma 1.** For every value $v$ present in the current window, the set contains exactly the pair

$$
(-\operatorname{cnt}[v],v).
$$

It contains no pair for a value absent from the window.

**Proof.** When a value is inserted, the algorithm removes its previous pair if one exists, increments its frequency, and inserts the updated pair. When a value is removed, the algorithm removes its previous pair and decrements its frequency. It reinserts the value exactly when the new frequency is positive. Thus, every positive-frequency value has exactly one pair containing its current frequency, while zero-frequency values have none. $\square$

**Lemma 2.** The first pair in the set represents the mode of the current window.

**Proof.** Consider two present values $u$ and $v$. If $\operatorname{cnt}[u]>\operatorname{cnt}[v]$, then

$$
-\operatorname{cnt}[u]<-\operatorname{cnt}[v],
$$

so the pair for $u$ appears first. If their frequencies are equal, the pair with the smaller compressed index appears first. Since compression preserves numerical order, this is also the smaller original value. Therefore, the first set element has maximum frequency and, among all such values, minimum value. $\square$

**Lemma 3.** After each sliding update, `cnt` and `s` represent the new window.

**Proof.** Suppose the structures represent

$$
a_{i-k},a_{i-k+1},\ldots,a_{i-1}.
$$

The next window is

$$
a_{i-k+1},a_{i-k+2},\ldots,a_i.
$$

The algorithm decreases the frequency of $a_{i-k}$ and increases the frequency of $a_i$. Frequencies of all shared elements remain unchanged. By Lemma 1, updating the corresponding set pairs makes `s` represent exactly these new frequencies. $\square$

**Theorem.** Every value printed by the algorithm is the mode of its corresponding window.

**Proof.** After initialization, the maintained frequencies represent the first window. By Lemma 3, every sliding update transforms them into the frequencies of the next window. By Lemma 2, `s.begin()` represents the mode of the currently maintained window. Therefore, every printed value is correct. $\square$

## Implementation

The pair

```cpp
{-cnt[x], x}
```

uses negative frequency so that the ascending order of `set` places the greatest frequency first.

When adding a value, remove the old pair before incrementing:

```cpp
s.erase({-cnt[x], x});
s.insert({-++cnt[x], x});
```

When removing a value, insert its updated pair only if it remains present:

```cpp
s.erase({-cnt[x], x});
if (--cnt[x]) s.insert({-cnt[x], x});
```

Convert the answer back to its original value using

```cpp
b[s.begin()->second]
```

because `b[id]` is the original value represented by compressed index `id`.

If the outgoing and incoming values are equal, the multiset of window values is unchanged. Skipping both updates avoids unnecessary tree operations.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

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

    vector<int> cnt(b.size());
    set<pair<int, int>> s;

    for (int i = 0; i < k; i++) {
        int x = a[i];
        s.erase({-cnt[x], x});
        s.insert({-++cnt[x], x});
    }

    cout << b[s.begin()->second];

    for (int i = k; i < n; i++) {
        int x = a[i - k], y = a[i];

        if (x != y) {
            s.erase({-cnt[x], x});
            if (--cnt[x]) s.insert({-cnt[x], x});

            s.erase({-cnt[y], y});
            s.insert({-++cnt[y], y});
        }

        cout << ' ' << b[s.begin()->second];
    }

    cout << '\n';
}
```

## Complexity

Sorting and coordinate compression take $O(n\log n)$ time. Each element causes a constant number of ordered-set operations, each taking $O(\log n)$. The total time complexity is $O(n\log n)$.

The array, compressed values, frequency table, and ordered set use $O(n)$ memory.

## Worked Example

For

$$
a=[1,2,3,2,5,2,4,4],
\qquad
k=3,
$$

the windows are:

| Window | Frequencies | Mode |
|---|---|---:|
| $[1,2,3]$ | $1:1,\ 2:1,\ 3:1$ | $1$ |
| $[2,3,2]$ | $2:2,\ 3:1$ | $2$ |
| $[3,2,5]$ | $2:1,\ 3:1,\ 5:1$ | $2$ |
| $[2,5,2]$ | $2:2,\ 5:1$ | $2$ |
| $[5,2,4]$ | $2:1,\ 4:1,\ 5:1$ | $2$ |
| $[2,4,4]$ | $2:1,\ 4:2$ | $4$ |

The output is

$$
1\quad2\quad2\quad2\quad2\quad4.
$$
