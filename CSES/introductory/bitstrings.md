# Bit Strings

## Problem

- **Source:** [CSES 1617: Bit Strings](https://cses.fi/problemset/task/1617/)
- **Code:** [`View accepted C++ solution (bitstrings.cpp)`](./bitstrings.cpp)
- **Limits:** $1\le n\le10^6$; output modulo $10^9+7$.

Count binary strings of length $n$.

## Idea

Each of the $n$ positions has two independent choices, 0 or 1. By the product rule, the number of strings is

$$\underbrace{2\cdot2\cdots2}_{n\text{ factors}}=2^n.$$

The exact value is far too large when $n=10^6$, so start from 1 and multiply by 2 exactly $n$ times, taking the result modulo $10^9+7$ after every multiplication.

## Implementation

`MOD` is an integer constant. `ans` is `long long`, so doubling a residue below $10^9+7$ is safe before the modulus is applied.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n; cin >> n;
	ll ans = 1;

	for(int i=0;i<n;i++){
		ans *= 2;
		ans %= MOD;
	}

	cout << ans << '\n';
	return 0;
}
```

## Complexity

The implementation performs $n$ constant-time updates, so it takes $O(n)$ time and $O(1)$ space. Binary exponentiation would reduce this to $O(\log n)$, but the linear loop still fits $n=10^6$ comfortably and matches the accepted code.
