# Sliding Window Sum

## Problem

- **Source:** [CSES 3220: Sliding Window Sum](https://cses.fi/problemset/task/3220/)
- **Code:** [`View accepted C++ solution (sum.cpp)`](../sum.cpp)
- **Limits:** $1\le k\le n\le10^7$, $0\le x,a,b\le10^9$, and $1\le c\le10^9$.

The sequence is computed by

$$
x_1=x,
\qquad
x_i=(ax_{i-1}+b)\bmod c.
$$

For every window of size $k$, calculate its sum. Output the XOR of all window sums.

## Idea

Naively recalculating the sum of every window takes $O(nk)$ time. Since $n$ may be as large as $10^7$, the algorithm must process each generated value in constant time.

Let $S_i$ be the sum of the window starting at index $i$. Consecutive windows overlap in $k-1$ elements. Therefore,

$$
S_{i+1}=S_i-x_i+x_{i+k}.
$$

After calculating the first sum, every later sum can be obtained from the element leaving the window and the element entering it.

The sequence generator produces incoming elements one by one. To recover outgoing elements, maintain the current window in an array `v` of length $k$. With zero-based indices, the value at sequence index $i$ is stored at position $i\bmod k$. When the value at index $i+k$ arrives,

$$
(i+k)\bmod k=i\bmod k,
$$

so that position contains exactly the value leaving the window. The array therefore acts as a circular buffer. Its physical order does not matter because the algorithm needs only the outgoing value and the current sum.

Both the window sum and the generator arithmetic require `long long`:

$$
k(c-1)<10^{16},
\qquad
ax+b\le10^9(10^9-1)+10^9<10^{18}+10^9.
$$

These values fit in a signed 64-bit integer.

## Algorithm

1. Generate the first $k$ values, store them in `v`, and accumulate their sum in `sum`.
2. Set `ans = sum` to account for the first window.
3. For every zero-based sequence index $i$ from $k$ to $n-1$:
   - Let $p=i\bmod k$.
   - Subtract `v[p]` from `sum`.
   - Replace `v[p]` with the newly generated value `x` and add `x` to `sum`.
   - Perform `ans ^= sum`.
   - Advance the generator.
4. Output `ans`.

## Correctness

We prove that the algorithm calculates the XOR of all window sums of size $k$.

**Lemma 1.** After initialization, `sum` equals the sum of the first window.

**Proof.** Each iteration of the initialization loop stores the current generated value and adds it to `sum` before advancing the generator. After $k$ iterations, exactly the first $k$ values have been added. Thus, `sum` equals the first window sum. $\square$

**Lemma 2.** Before the sliding iteration for index $i\ge k$, `v[i % k]` stores the value at sequence index $i-k$.

**Proof.** The value at index $i-k$ was stored at position

$$
(i-k)\bmod k=i\bmod k.
$$

The following $k-1$ values use different buffer positions, so this position is not overwritten before iteration $i$. Therefore, it still contains the outgoing value at index $i-k$. $\square$

**Lemma 3.** After every sliding update, `sum` equals the sum of the new window.

**Proof.** Before processing index $i$, `sum` is the sum of the window ending at index $i-1$. By Lemma 2, `v[i % k]` is its leftmost value. The algorithm subtracts this value and adds the new value at index $i$. This applies the transition

$$
S_{l+1}=S_l-x_l+x_{l+k},
$$

so `sum` becomes the next window sum. $\square$

**Theorem.** The final value of `ans` equals the required answer.

**Proof.** The first window sum initializes `ans`. By Lemma 3, every sliding iteration calculates the next window sum, which is XORed into `ans` exactly once. There are $1+(n-k)=n-k+1$ windows, so every required sum contributes exactly once. $\square$

## Implementation

After initialization, `x` already contains the first value not included in the initial window. During a sliding iteration, the outgoing value must be subtracted before `v[p]` is overwritten. The generator advances only after the current value of `x` has been inserted.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    ll x, a, b, c;
    cin >> n >> k;
    cin >> x >> a >> b >> c;

    vector<int> v(k);
    ll sum = 0;

    for (int i = 0; i < k; i++) {
        v[i] = x;
        sum += x;
        x = (a * x + b) % c;
    }

    ll ans = sum;

    for (int i = k; i < n; i++) {
        int p = i % k;

        sum -= v[p];
        v[p] = x;
        sum += x;

        ans ^= sum;
        x = (a * x + b) % c;
    }

    cout << ans << '\n';
}
```

## Complexity

The initialization performs $k$ iterations, and the sliding phase performs $n-k$ iterations. The total time complexity is $O(n)$.

The circular buffer contains $k$ integers, so the auxiliary space complexity is $O(k)$.

## Worked Example

For $n=8$, $k=5$, $x=3$, $a=7$, $b=1$, and $c=11$, the generated sequence is

$$
[3,0,1,8,2,4,7,6].
$$

| Incoming index | Buffer position | Outgoing | Incoming | New sum | XOR answer |
|---:|---:|---:|---:|---:|---:|
| initial | - | - | $3,0,1,8,2$ | $14$ | $14$ |
| $5$ | $0$ | $3$ | $4$ | $15$ | $1$ |
| $6$ | $1$ | $0$ | $7$ | $22$ | $23$ |
| $7$ | $2$ | $1$ | $6$ | $27$ | $12$ |

The final answer is $12$.
