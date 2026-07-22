# Subarray Sums II

## Problem

- **Source:** [CSES 1661: Subarray Sums II](https://cses.fi/problemset/task/1661/)
- **Code:** [`View accepted C++ solution (subarraysums2.cpp)`](./subarraysums2.cpp)

Count contiguous subarrays whose sum is $x$, allowing negative values.

## Prefix Sums

Let prefix sum $P_i=a_1+\cdots+a_i$, with $P_0=0$. The sum from $j+1$ through $i$ is

$$
P_i-P_j.
$$

It equals $x$ precisely when $P_j=P_i-x$. Thus, when processing $P_i$, the number of valid subarrays ending at $i$ is the number of earlier prefix sums equal to $P_i-x$.

This reformulation removes the need for monotonicity and works with arbitrary signs.

## Algorithm

Maintain a frequency map of prefix sums already seen, initially with one occurrence of 0. For each input value, update the running prefix, add the frequency of `prefix - target` to the answer, then increment the frequency of the current prefix.

## Correctness

When processing endpoint $i$, the map contains exactly $P_0,\ldots,P_{i-1}$. Each occurrence of $P_i-x$ corresponds to one earlier index $j$ for which $P_i-P_j=x$, hence one valid subarray ending at $i$. No other earlier prefix yields sum $x$.

The lookup happens before inserting $P_i$, so only nonempty subarrays are counted. Summing these exact counts over all endpoints counts every valid subarray once.

### Complexity

Expected time is $O(n)$ and space is $O(n)$.

## Implementation

`cnt[0] = 1` represents the empty prefix and permits subarrays starting at the first element. The custom hash reduces sensitivity to adversarial collision patterns. Prefix sums, frequencies, and the answer use `long long`.

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
ll x;
struct H {
	size_t operator()(ll k) const {
		k += 0x9e3779b97f4a7c15ULL;
		k = (k ^ (k >> 30)) * 0xbf58476d1ce4e5b9ULL;
		k = (k ^ (k >> 27)) * 0x94d049bb133111ebULL;
		return k ^ (k >> 31);
	}
};
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> x;
	unordered_map<ll,ll,H> cnt;
	cnt.reserve(2*n);
	cnt[0] = 1;                                  // empty prefix
	ll pre = 0, ans = 0;
	for(int i = 0; i < n; i++){
		ll v; cin >> v;
		pre += v;
		auto it = cnt.find(pre - x);
		if(it != cnt.end()) ans += it->s;        // earlier prefixes giving sum x
		cnt[pre]++;
	}
	cout << ans << '\n';
	return 0;
}
```

## Worked Example

For $1,-1,2$ and $x=2$, prefix sums are $0,1,0,2$. At the final prefix 2, the needed value is 0, which has occurred twice. These occurrences produce subarrays $[1,-1,2]$ and $[2]$.

## Conclusion

Convert a subarray condition into an equation between two prefix states, then count earlier states satisfying the forced complement.

## Extensions

Subarray Divisibility replaces equality of a difference with equality of prefix residues.
