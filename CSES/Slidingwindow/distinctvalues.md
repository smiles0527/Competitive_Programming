# Sliding Window Distinct Values

## Problem

- **Source:** [CSES 3222: Sliding Window Distinct Values](https://cses.fi/problemset/task/3222/)
- **Code:** [`View accepted C++ solution (distinctvalues.cpp)`](./distinctvalues.cpp)
- **Limits:** $1\le k\le n\le2\cdot10^5$ and $1\le x_i\le10^9$.

For every contiguous window of length $k$, output the number of distinct values in that window. There are $n-k+1$ windows.

## Idea

Counting every window independently with a set takes $O(nk\log k)$ time in the worst case. Since consecutive windows share $k-1$ elements, only the outgoing and incoming values should be processed.

Maintain

$$
\operatorname{cnt}[v]=\text{the number of occurrences of }v
$$

in the current window, together with

$$
\texttt{cur}=\lvert\{v:\operatorname{cnt}[v]>0\}\rvert.
$$

When inserting $v$, it becomes a new distinct value exactly when its old frequency is zero:

$$
\operatorname{cnt}[v]:0\longrightarrow1.
$$

When removing $v$, it disappears from the window exactly when its frequency becomes zero:

$$
\operatorname{cnt}[v]:1\longrightarrow0.
$$

Values can be as large as $10^9$, so a direct frequency array is impossible. An `unordered_map` stores frequencies only for values currently present.

The full input array is also unnecessary. Store the current window in an array `q` of length $k$. Using zero-based indices, value $a_i$ is written to position $i\bmod k$. When $a_{i+k}$ arrives,

$$
(i+k)\bmod k=i\bmod k,
$$

so the same position contains exactly $a_i$, the value that must leave. Thus, `q` acts as a circular buffer.

## Algorithm

For each zero-based index $i$ from $0$ to $n-1$:

1. Read the incoming value $x$.
2. If $i\ge k$:
   - Set $y=\texttt{q}[i\bmod k]$.
   - Decrement `cnt[y]`.
   - If the frequency becomes zero, erase $y$ and decrement `cur`.
3. Store $x$ at `q[i % k]`.
4. Increment `cnt[x]`.
5. If its previous frequency was zero, increment `cur`.
6. If $i\ge k-1$, output `cur`.

## Correctness

We prove that every output is the number of distinct values in its corresponding window.

**Lemma 1.** Before each output, $\operatorname{cnt}[v]$ equals the number of occurrences of $v$ in the current window.

**Proof.** During the first $k$ iterations, every read value is inserted and no value is removed. After index $k-1$, the table therefore represents the first window.

Now consider an index $i\ge k$. The position $i\bmod k$ was last written at index $i-k$, so it contains the outgoing value $a_{i-k}$. The algorithm decrements its frequency and then inserts $a_i$. The values

$$
a_{i-k+1},a_{i-k+2},\ldots,a_{i-1}
$$

belong to both consecutive windows and remain unchanged. Thus, the updated table represents exactly

$$
a_{i-k+1},a_{i-k+2},\ldots,a_i.
$$

$\square$

**Lemma 2.** `cur` equals the number of values with positive frequency.

**Proof.** When inserting $v$, `cur` increases only if $\operatorname{cnt}[v]$ changes from $0$ to $1$, exactly when $v$ begins appearing in the window. When removing $v$, `cur` decreases only if its count changes from $1$ to $0$, exactly when its final occurrence leaves. No other frequency change affects whether a value is present. $\square$

**Theorem.** Every printed value is the number of distinct values in its corresponding window.

**Proof.** By Lemma 1, the frequency table represents the current window whenever an answer is printed. By Lemma 2, `cur` counts exactly the values occurring at least once in that window. Therefore, `cur` is its number of distinct values. $\square$

## Implementation

The outgoing value must be read before its circular-buffer position is overwritten:

```cpp
int y = q[i % k];
if (--cnt[y] == 0) {
    cnt.erase(y);
    cur--;
}
```

Erasing zero-frequency entries keeps the hash table proportional to the number of distinct values in the current window.

Insertion tests the frequency before incrementing it:

```cpp
if (cnt[x]++ == 0) cur++;
```

The hash table reserves space in advance:

```cpp
cnt.reserve(2 * k);
cnt.max_load_factor(0.7);
```

This reduces rehashing and keeps the implementation fast at the official limit.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> q(k);
    unordered_map<int, int> cnt;
    cnt.reserve(2 * k);
    cnt.max_load_factor(0.7);

    int cur = 0;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        if (i >= k) {
            int y = q[i % k];
            if (--cnt[y] == 0) {
                cnt.erase(y);
                cur--;
            }
        }

        q[i % k] = x;
        if (cnt[x]++ == 0) cur++;

        if (i >= k - 1) {
            if (i >= k) cout << ' ';
            cout << cur;
        }
    }

    cout << '\n';
}
```

## Complexity

Each value causes one expected constant-time hash-table insertion and, after the first window, one removal. The expected time complexity is $O(n)$.

The circular buffer contains $k$ values, and the hash table contains at most $k$ keys. The auxiliary space complexity is $O(k)$.

## Worked Example

For

$$
a=[1,2,3,2,5,2,2,2],
\qquad
k=3,
$$

the maintained states are:

| Window | Outgoing | Incoming | Frequencies | Distinct |
|---|---:|---:|---|---:|
| $[1,2,3]$ | - | $1,2,3$ | $1:1,\ 2:1,\ 3:1$ | $3$ |
| $[2,3,2]$ | $1$ | $2$ | $2:2,\ 3:1$ | $2$ |
| $[3,2,5]$ | $2$ | $5$ | $2:1,\ 3:1,\ 5:1$ | $3$ |
| $[2,5,2]$ | $3$ | $2$ | $2:2,\ 5:1$ | $2$ |
| $[5,2,2]$ | $2$ | $2$ | $2:2,\ 5:1$ | $2$ |
| $[2,2,2]$ | $5$ | $2$ | $2:3$ | $1$ |

The output is

$$
3\quad2\quad3\quad2\quad2\quad1.
$$
