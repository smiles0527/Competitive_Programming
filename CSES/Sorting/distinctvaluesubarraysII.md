# Distinct Values Subarrays II

## Problem

- **Source:** [CSES 2428: Distinct Values Subarrays II](https://cses.fi/problemset/task/2428/)
- **Code:** [`View accepted C++ solution (distinctvaluesubarraysII.cpp)`](./distinctvaluesubarraysII.cpp)

Count contiguous subarrays containing at most $k$ distinct values.

## Property of the Sliding Window

For each right endpoint $r$, valid starting positions again form a suffix. Maintain the smallest $l$ for which $[l,r]$ contains at most $k$ distinct values. If adding $a_r$ creates too many, repeatedly remove the leftmost value until the constraint is restored.

Once $[l,r]$ is valid, every suffix of it is valid because deleting elements cannot introduce a new distinct value. No earlier start is valid: $l$ stopped only after the distinct count fell to $k$, so immediately before the final removal the larger window violated the bound. Hence $r-l+1$ valid subarrays end at $r$.

## Algorithm

Maintain frequencies inside a sliding window and a counter `distinct`. Extend the right boundary. While `distinct > k`, decrement the frequency at the left boundary and advance it, reducing `distinct` when a frequency reaches zero. Add the resulting window length.

## Correctness

The frequency map always describes exactly the current window. After the shrinking loop, the window contains at most $k$ distinct values. If the left endpoint moved, the window beginning one position earlier contained more than $k$ distinct values at the moment it was removed; any still earlier window contains all of those values and is also invalid. If it did not move, no earlier position is available beyond the boundary retained from previous iterations.

Thus starts $l$ through $r$ are precisely the valid starts for endpoint $r$. Adding their count for every endpoint counts every qualifying subarray once and no invalid subarray.

### Complexity

Each endpoint moves at most $n$ times, so expected time is $O(n)$ and space is $O(n)$.

## Implementation

References `fr` and `fl` update map entries in place. The load factor and reserve calls are performance safeguards. The answer uses `long long`.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define FOR(i,a,b) for(int i = (a); i < (b); i++)
#define ii pair<int, int>

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, k; cin >> n >> k;
	vector<ll> a(n); for(auto &x : a) cin >> x;

	unordered_map<ll, int> freq;
	freq.reserve((size_t)n*2);
	freq.max_load_factor(0.7f);

	ll ans = 0;
	int distinct = 0;
	int l = 0;

	for(int r = 0; r < n; r++){
		int &fr = freq[a[r]];
		if(fr==0) distinct++;
		fr++;

		while(distinct > k){
			int &fl = freq[a[l]];
			fl--;
			if(fl == 0) distinct--;
			l++;
		}
		ans += (ll)(r-l+1);
	}
	cout << ans;
}
```

## Worked Example

For $1,2,1,3$ and $k=2$, contributions by right endpoint are $1,2,3,2$. At the last step, the window $1,2,1,3$ has three values, so the boundary moves past 2 and leaves $1,3$. The total is 8.

## Takeaway

An at-most constraint is often sliding-window friendly because removing elements can only improve validity. Count all valid suffixes after restoring the constraint.

## Related Problems

Exact-$k$ counts can be obtained as `atMost(k) - atMost(k-1)`.
