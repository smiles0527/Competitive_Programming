# Apple Division

## Problem

- **Source:** [CSES 1623: Apple Division](https://cses.fi/problemset/task/1623/)
- **Code:** [`View accepted C++ solution (appledivision.cpp)`](./appledivision.cpp)
- **Limits:** $1\le n\le20$, $1\le p_i\le10^9$.

Partition the apple weights into two groups so their sum difference is minimum.

## Search strategy

The bound $n\le20$ permits all $2^n$ subsets. If the total weight is $S$ and one group has weight $X$, the other has weight $S-X$, so the difference is

$$|X-(S-X)|=|S-2X|.$$

Every partition is represented by choosing one of its groups as a subset. The complementary subset represents the same partition again, but duplicate evaluation does not affect a minimum.

### Procedure

Compute $S$. For each bitmask from 0 through $2^n-1$, sum the weights whose bits are set and minimize $|S-2X|$.

## Why it works

Each mask defines a valid partition between selected and unselected apples. Conversely, every partition has a mask for either group. The expression evaluated for that mask is its true sum difference. Taking the minimum over all masks therefore returns the optimum.

## Implementation

Weights, subset sums, and the answer use `long long`. The shift `1 << n` is safe because $n\le20$.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n; cin >> n;
	vector<ll> a(n);
	ll sum = 0;
	for(auto &x : a) cin >> x, sum += x;

	ll best = (ll)4e18;
	for(int i = 0; i < (1 << n); i++){
		ll x = 0;
		for(int j = 0; j < n; j++) if( i & (1 << j)) x += a[j];
		best = min(best, llabs(sum - 2 * x));
	}

	cout << best << '\n';
	return 0;
}
```

## Complexity

There are $2^n$ masks and $n$ bit tests per mask, giving $O(n2^n)$ time and $O(n)$ input storage.

## Example

For weights $[3,2,7,4,1]$, selecting $3,2,4$ gives $X=9$ and total $S=17$, so the difference is $|17-18|=1$.
