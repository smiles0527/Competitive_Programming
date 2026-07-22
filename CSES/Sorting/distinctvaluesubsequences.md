# Distinct Values Subsequences

## Problem

- **Source:** [CSES 3421: Distinct Values Subsequences](https://cses.fi/problemset/task/3421/)
- **Code:** [`View accepted C++ solution (distinctvaluesubsequences.cpp)`](./distinctvaluesubsequences.cpp)

Count nonempty subsequences whose selected values are pairwise distinct, modulo $10^9+7$.

## Key Observation

Only the frequency of each value matters. If a value occurs $c$ times, a valid subsequence has $c+1$ choices concerning that value: omit it, or select exactly one of its $c$ positions. Choices for different values are independent, so the product rule gives

$$
\prod_v(c_v+1)
$$

subsequences including the empty choice. Subtracting one removes the empty subsequence. Selecting positions in increasing index order determines exactly one subsequence, so this product neither loses nor duplicates any valid selection.

## Algorithm

Count occurrences of each distinct value. Multiply `frequency + 1` for all map entries modulo $10^9+7$, then subtract one modulo the same modulus.

## Correctness

Map every valid subsequence to one choice for each distinct input value: omission or one selected occurrence. Pairwise distinctness guarantees exactly one such choice per value, and the selected indices uniquely recover the subsequence. Conversely, any collection of these independent choices produces a subsequence with no repeated value after its selected positions are ordered.

This is a bijection between valid subsequences including the empty one and the Cartesian product of $c_v+1$ choices for each value. The algorithm computes its size and removes exactly the empty selection, so its answer is correct.

### Complexity

Expected time is $O(n)$ and space is $O(d)$, where $d$ is the number of distinct values.

## Implementation

The multiplication is reduced after each factor. `(prod - 1 + MOD) % MOD` avoids a negative representative after removing the empty subsequence.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int MOD = 1e9+7;
int n;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	unordered_map<int,int> cnt;
	cnt.reserve(2*n);
	for(int i = 0, x; i < n; i++){ cin >> x; cnt[x]++; }
	ll prod = 1;
	for(auto &e : cnt) prod = prod * ((e.s + 1) % MOD) % MOD;
	ll ans = (prod - 1 + MOD) % MOD;
	cout << ans << '\n';
	return 0;
}
```

## Worked Example

For $4,4,7$, value 4 offers three choices and value 7 offers two. Their product is 6. Removing the empty choice leaves 5 subsequences: either occurrence of 4, the 7, and the two choices pairing one 4 with 7.

## Takeaway

When a global restriction says at most one object from each value class, separate the input into independent classes and apply the product rule.

### Related problems

Ordinary distinct-subsequence counting treats equal resulting sequences as identical and requires a different dynamic program. Here selected positions remain distinct choices.
