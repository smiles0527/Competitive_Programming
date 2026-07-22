# Maximum Subarray Sum II

## Problem

- **Source:** [CSES 1644: Maximum Subarray Sum II](https://cses.fi/problemset/task/1644/)
- **Code:** [`View accepted C++ solution (maximumsubarraysum2.cpp)`](./maximumsubarraysum2.cpp)

Find the maximum sum of a contiguous subarray whose length is between $a$ and $b$ inclusive.

## Prefix-Sum Formulation

With prefix sums $P_i$, a subarray ending at $r$ and beginning after prefix index $l$ has sum $P_r-P_l$. Its length constraint requires

$$
r-b\le l\le r-a.
$$

For fixed $r$, maximizing the sum means subtracting the minimum prefix sum in this sliding index range. The range advances one step per endpoint. A monotonic deque maintains its minimum: indices remain in increasing order, while their prefix sums remain strictly increasing.

When a new prefix becomes eligible, any larger prefix at the back is permanently dominated by this later, no-larger prefix. Expired indices leave from the front.

## Algorithm

Build prefix sums. For each $r$ from $a$ through $n$, insert index $r-a$ into an increasing-prefix deque, remove front indices below $r-b$, and maximize `pre[r] - pre[dq.front()]`.

## Correctness

Before evaluating endpoint $r$, the deque contains exactly the undominated indices in $[r-b,r-a]$. Back removals are safe because the new index is later and has no greater prefix sum, so it gives at least as large a subarray sum for every future endpoint where both are eligible. Front removals discard exactly indices outside the length bound.

Consequently the deque front has the minimum eligible prefix sum, and the algorithm computes the best valid subarray ending at $r$. Taking the maximum over all endpoints considers every allowed subarray, so the final answer is optimal.

### Complexity

Every prefix index enters and leaves the deque at most once. Time is $O(n)$ and space is $O(n)$ for prefix sums and the deque.

## Implementation

Insertion occurs before expiration, but the new index $r-a$ always satisfies the upper eligibility boundary. `best` begins at `LLONG_MIN` because all valid sums may be negative.

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
int n, a, b;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> a >> b;
	vector<ll> pre(n+1, 0);
	for(int i = 1; i <= n; i++){
		ll v; cin >> v;
		pre[i] = pre[i-1] + v;
	}
	deque<int> dq;                               // indices, increasing pre
	ll best = LLONG_MIN;
	for(int r = a; r <= n; r++){
		int add = r - a;                         // newly eligible left index
		while(!dq.empty() && pre[dq.back()] >= pre[add]) dq.pop_back();
		dq.pb(add);
		int lo = r - b;                          // expire indices < lo
		while(!dq.empty() && dq.front() < lo) dq.pop_front();
		best = max(best, pre[r] - pre[dq.front()]);
	}
	cout << best << '\n';
	return 0;
}
```

## Worked Example

For $1,-3,5,2,-1$ with lengths 2 through 3, prefix sums are $0,1,-2,3,5,4$. At $r=4$, eligible left indices are 1 and 2; their prefix sums are 1 and $-2$. Choosing index 2 gives sum $5-(-2)=7$, corresponding to $5,2$.

## Takeaway

When a prefix-sum optimization asks for a minimum over a sliding range, a monotonic deque can replace a balanced tree and reduce $O(n\log n)$ to $O(n)$.

## Related Problems

Maximum Subarray Sum has no length window and collapses to Kadane's one-state recurrence.
