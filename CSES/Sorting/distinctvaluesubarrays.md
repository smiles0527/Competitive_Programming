# Distinct Values Subarrays

## Problem

- **Source:** [CSES 3420: Distinct Values Subarrays](https://cses.fi/problemset/task/3420/)
- **Code:** [`View accepted C++ solution (distinctvaluesubarrays.cpp)`](./distinctvaluesubarrays.cpp)

Count contiguous subarrays whose values are all distinct.

## Idea

For a fixed right endpoint $r$, let $l$ be the smallest index such that $a_l,\ldots,a_r$ contains no duplicate. Every suffix beginning at $l,l+1,\ldots,r$ is also distinct, while every earlier beginning is invalid. Thus exactly $r-l+1$ valid subarrays end at $r$.

When $a_r$ previously occurred at $p\ge l$, any window beginning at or before $p$ contains both copies, so the new minimal boundary is $p+1$. An occurrence before $l$ is irrelevant. Storing the last position of every value lets us update this boundary directly.

## Algorithm

Scan right endpoints from left to right. Maintain `last[value]` and the minimal valid left endpoint `l`. Move `l` past a conflicting last occurrence, record the current occurrence, and add `r - l + 1` to the answer.

## Correctness

After processing $r$, the window $[l,r]$ is distinct. If $a_r$ occurred at $p\ge l$, moving to $p+1$ removes the sole new duplication; if not, the old window remains valid. Moreover, no start before the chosen $l$ is valid, either because it was already excluded at the previous step or because it contains positions $p$ and $r$ with equal values.

Therefore the valid subarrays ending at $r$ are exactly those with starts from $l$ through $r$, and the algorithm adds each of them once. Every subarray has a unique right endpoint, so the final sum counts every valid subarray exactly once.

### Complexity

Expected time is $O(n)$ and space is $O(n)$. The answer requires `long long` because there can be $n(n+1)/2$ valid subarrays.

## Implementation

The condition `last >= l` prevents the boundary from moving backward. `reserve(2*n)` reduces hash-table reallocation.

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
	vector<int> x(n);
	for(auto &v : x) cin >> v;
	unordered_map<int,int> last;
	last.reserve(2*n);
	ll ans = 0;
	int l = 0;
	for(int r = 0; r < n; r++){
		auto it = last.find(x[r]);
		if(it != last.end() && it->s >= l) l = it->s + 1;
		last[x[r]] = r;
		ans += (r - l + 1);                      // subarrays ending at r
	}
	cout << ans << '\n';
	return 0;
}
```

## Worked Example

For $1,2,1,3$, the minimal left endpoints are $0,0,1,1$. The contributions are $1,2,2,3$, totaling 8 distinct-value subarrays.

## Takeaway

If valid starts for each right endpoint form a suffix, maintain its first position and count the entire suffix at once.

### Related problems

Playlist maximizes the same window length. Distinct Values Subarrays II replaces uniqueness by a bound on the number of distinct values.
