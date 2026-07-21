# Trailing Zeros

## Problem

- **Source:** [CSES 1618: Trailing Zeros](https://cses.fi/problemset/task/1618/)
- **Code:** [`View accepted C++ solution (trailingzeros.cpp)`](../trailingzeros.cpp)
- **Limits:** $1\le n\le10^9$.

Find the number of trailing zero digits in $n!$.

## Idea

A decimal trailing zero is a factor of 10, and $10=2\cdot5$. Thus the answer is

$$\min(v_2(n!),v_5(n!)),$$

where $v_p(x)$ denotes the exponent of prime $p$ in $x$. Every second factor contributes a 2, while only every fifth contributes a 5, so $v_2(n!)>v_5(n!)$ for positive $n$. It is enough to count factors of 5.

Counting multiples of 5 once is not enough. A value such as 25 contributes two factors of 5, and 125 contributes three. Multiples of $5$ contribute the first factor, multiples of $25$ contribute one additional factor, and so on. Therefore

$$v_5(n!)=\left\lfloor\frac n5\right\rfloor+
\left\lfloor\frac n{25}\right\rfloor+
\left\lfloor\frac n{125}\right\rfloor+\cdots.$$

The sum stops once $5^j>n$.

### Procedure

Initialize `ans = 0`. For powers $p=5,25,125,\ldots$ not exceeding $n$, add $\lfloor n/p\rfloor$ to `ans`. Output `ans`.

For each positive integer $j$, exactly $\lfloor n/5^j\rfloor$ factors among $1,2,\ldots,n$ are divisible by $5^j$. Counting a number once for every power of 5 dividing it counts all of its factors of 5. Summing over $j$ therefore gives $v_5(n!)$. Since factors of 2 are more numerous, each factor of 5 can pair with a factor of 2, and the number of such pairs is the number of trailing zeros. The algorithm outputs that sum.

## Implementation

Both `i` and `n` use `long long`. With the official bound $n\le10^9$, the final multiplication after the last useful power also remains within 64-bit range.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n; cin >> n;
	ll ans = 0;

	for(ll i=5;i<=n;i*=5)
		ans += n/i;

	cout << ans << '\n';
	return 0;
}
```

## Complexity

There are $\lfloor\log_5 n\rfloor$ relevant powers, giving $O(\log n)$ time and $O(1)$ space.

## Example

For $n=100$,

$$\left\lfloor\frac{100}{5}\right\rfloor+
\left\lfloor\frac{100}{25}\right\rfloor=20+4=24.$$

The first term counts one factor of 5 from every multiple of 5. The second counts the extra factor contributed by 25, 50, 75, and 100.
