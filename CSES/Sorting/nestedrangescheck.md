# Nested Ranges Check

## Problem

- **Source:** [CSES 2168: Nested Ranges Check](https://cses.fi/problemset/task/2168/)
- **Code:** [`View accepted C++ solution (nestedrangescheck.cpp)`](./nestedrangescheck.cpp)

For every interval, determine whether it contains another interval and whether another interval contains it.

## Sorting the Ranges

Sort intervals by increasing left endpoint and, for equal left endpoints, decreasing right endpoint. Then any earlier interval begins no later. The current interval is contained by an earlier one exactly when some earlier right endpoint is at least its right endpoint, which a running maximum detects.

In the reverse direction, every later interval begins no earlier. The current interval contains a later one exactly when some later right endpoint is at most its right endpoint, which a running minimum detects. The tie order is essential: among equal left endpoints, wider intervals appear first.

## Algorithm

Sort `(left, right, original index)` with right endpoints descending on ties. Scan forward with maximum right endpoint to mark `contained`. Scan backward with minimum right endpoint to mark `contains`. Print both arrays in original order.

## Correctness

During the forward scan, all earlier intervals have left endpoint at most the current left endpoint. A running maximum at least as large as the current right endpoint exists exactly when one earlier interval covers both boundaries, so `contained` is marked exactly when required.

During the reverse scan, all later intervals have left endpoint at least the current left endpoint. A running minimum no larger than the current right endpoint exists exactly when the current interval covers one of those later intervals. Therefore `contains` is also marked exactly when required. Restoring original indices changes only output order.

### Complexity

Sorting takes $O(n\log n)$ time, both scans take $O(n)$ time, and space is $O(n)$.

## Implementation

Descending right endpoints on equal left endpoints ensures a wider equal-start interval can mark narrower ones during the forward scan. `INT_MIN` and `INT_MAX` represent empty running extrema.

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
	vector<array<int,3>> r(n);                   // {x, y, idx}
	for(int i = 0; i < n; i++){
		int x, y; cin >> x >> y;
		r[i] = {x, y, i};
	}
	vector<int> contains(n, 0), contained(n, 0);

	// contained-by-another: sort x asc, y desc; running max y over earlier (x' <= x)
	sort(r.begin(), r.end(), [](const array<int,3>& a, const array<int,3>& b){
		if(a[0] != b[0]) return a[0] < b[0];
		return a[1] > b[1];
	});
	int maxY = INT_MIN;
	for(int i = 0; i < n; i++){
		if(maxY >= r[i][1]) contained[r[i][2]] = 1;   // earlier range with x'<=x, y'>=y
		maxY = max(maxY, r[i][1]);
	}

	// contains-another: same order, scan from end; min y over later (x' >= x)
	int minY = INT_MAX;
	for(int i = n-1; i >= 0; i--){
		if(minY <= r[i][1]) contains[r[i][2]] = 1;    // later range with x'>=x, y'<=y
		minY = min(minY, r[i][1]);
	}

	for(int i = 0; i < n; i++) cout << contains[i] << (i+1==n?'\n':' ');
	for(int i = 0; i < n; i++) cout << contained[i] << (i+1==n?'\n':' ');
	return 0;
}
```

## Worked Example

For intervals $[1,6],[2,4],[4,8]$, sorted order is unchanged. The forward maximum 6 marks $[2,4]$ as contained. In reverse, the minimum right endpoint after $[1,6]$ is 4, so $[1,6]$ is marked as containing another interval.

## Takeaway

Two-dimensional containment often becomes a one-dimensional extremum after sorting one boundary with the correct tie rule.

### Related problems

Nested Ranges Count replaces existence extrema with Fenwick counts over compressed right endpoints.
