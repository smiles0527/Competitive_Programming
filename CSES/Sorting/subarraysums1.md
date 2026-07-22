# Subarray Sums I

## Problem

- **Source:** [CSES 1660: Subarray Sums I](https://cses.fi/problemset/task/1660/)
- **Code:** [`View accepted C++ solution (subarraysums1.cpp)`](./subarraysums1.cpp)

Count contiguous subarrays whose sum is exactly $x$. Every array value is positive.

## Window Invariant

Positivity makes window sums monotone with respect to both endpoints. Extending the right endpoint strictly increases the sum, while removing the leftmost value strictly decreases it. Therefore, after adding $a_r$, any sum above $x$ can be repaired by advancing the left endpoint, and a discarded left endpoint can never become useful for a later right endpoint.

After shrinking until the sum is at most $x$, equality identifies one valid subarray ending at $r$. Because all values are positive, two different starts cannot give the same sum for that endpoint.

## Algorithm

Maintain a window sum and left endpoint. Add each new rightmost value. While the sum exceeds $x$, remove values from the left. Increment the answer when the remaining sum equals $x$.

## Correctness

After the shrinking loop for endpoint $r$, the maintained window is the earliest start whose sum is at most $x$. Every earlier start has a larger sum and is invalid. Every later start has a strictly smaller sum, so if the maintained sum equals $x$, it is the unique valid subarray ending at $r$; if it is below $x$, no valid subarray ends there.

The algorithm therefore counts exactly the valid subarrays for each right endpoint. Since every subarray has one right endpoint, the final count is correct.

### Complexity

Both endpoints advance at most $n$ times, giving $O(n)$ time and $O(n)$ input storage.

## Implementation

The shrinking argument relies on strictly positive values and would fail with negative numbers. Sums and the count use `long long`.

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
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> x;
	vector<ll> a(n);
	for(auto &v : a) cin >> v;
	ll sum = 0, cnt = 0;
	int l = 0;
	for(int r = 0; r < n; r++){
		sum += a[r];
		while(sum > x) sum -= a[l++];            // shrink (safe: positives)
		if(sum == x) cnt++;
	}
	cout << cnt << '\n';
	return 0;
}
```

## Worked Example

For $2,1,3,2$ and $x=5$, endpoint 2 gives window $2,1,3$ with sum 6, which shrinks to $1,3$ with sum 4. Endpoint 3 then gives $1,3,2$ with sum 6 and shrinks to $3,2$, producing the single valid subarray.

## Takeaway

Positive values turn exact-sum windows into a monotone two-pointer problem. Without positivity, switch to prefix sums.

## Related Problems

Subarray Sums II handles arbitrary signed values with prefix-sum frequencies.
