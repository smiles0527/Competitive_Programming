# Array Division

## Problem

- **Source:** [CSES 1085: Array Division](https://cses.fi/problemset/task/1085/)
- **Code:** [`View accepted C++ solution (arraydivision.cpp)`](./arraydivision.cpp)

Divide an array of positive integers into at most $k$ contiguous nonempty parts while minimizing the largest part sum.

## Binary Search on the Threshold

Suppose a candidate maximum sum $S$ is fixed. The fewest parts respecting this cap can be found greedily: extend the current part until the next value would make its sum exceed $S$, then start a new part.

This greedy cut is forced in the following sense. Any valid first part cannot extend past the greedy first part, because adding the next value already violates the cap. Cutting earlier only leaves more elements for later parts and cannot reduce the number of parts required. Repeating this argument proves the scan uses the minimum possible number of parts for cap $S$.

Feasibility, defined as needing at most $k$ parts, is monotone. Increasing $S$ never creates a violation. The answer lies between the largest single value and the total sum, so binary search applies.

## Algorithm

Set `lo` to the maximum array value and `hi` to the total sum. For a candidate cap, scan greedily and count required parts. If at most $k$ are needed, move the upper boundary to the candidate; otherwise move the lower boundary above it.

## Correctness

For any cap $S$, the greedy scan uses the minimum possible number of parts. Indeed, its first cut is as late as the cap permits, while no valid division can place that cut later. Removing this prefix leaves the same claim for the suffix, so induction proves the result.

The binary search maintains that the optimal largest sum lies in `[lo, hi]`. A feasible midpoint admits a division into at most $k$ parts, so the optimum is no larger. An infeasible midpoint needs more than $k$ parts even under the minimum-part greedy scan, so no cap at most that midpoint can work. At termination the sole remaining value is feasible and every smaller value is infeasible, hence it is optimal.

### Complexity

Each check takes $O(n)$ time. Binary search performs $O(\log S)$ checks, where $S$ is the total sum, for $O(n\log S)$ time and $O(n)$ storage for the input.

## Implementation

Positivity makes extending a segment monotone and justifies the greedy check. The lower bound must be the maximum element because no element may be split. Sums and boundaries use `long long`.

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
int n, k;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> k;
	vector<ll> x(n);
	ll lo = 0, hi = 0;
	for(auto &v : x){ cin >> v; lo = max(lo, v); hi += v; }

	auto need = [&](ll S)->int{                  // subarrays needed with cap S
		int cnt = 1;
		ll cur = 0;
		for(ll v : x){
			if(cur + v > S){ cnt++; cur = v; }
			else cur += v;
		}
		return cnt;
	};

	while(lo < hi){
		ll mid = lo + (hi - lo) / 2;
		if(need(mid) <= k) hi = mid;
		else lo = mid + 1;
	}
	cout << lo << '\n';
	return 0;
}
```

## Worked Example

For $2,4,7,3,5$ with $k=3$, cap 8 greedily creates $[2,4]$, $[7]$, and $[3,5]$, so it is feasible. Cap 7 requires $[2,4]$, $[7]$, $[3]$, $[5]$, so it is infeasible. The optimum is 8.

## Takeaway

Binary search on the answer becomes especially effective when a proposed threshold turns optimization into a linear greedy feasibility test.

## Related Problems

Factory Machines searches the first feasible time. Maximum Subarray Sum II instead uses prefix sums because it imposes length rather than sum caps.
