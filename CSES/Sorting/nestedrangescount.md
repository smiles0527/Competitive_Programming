# Nested Ranges Count

## Problem

- **Source:** [CSES 2169: Nested Ranges Count](https://cses.fi/problemset/task/2169/)
- **Code:** [`View accepted C++ solution (nestedrangescount.cpp)`](./nestedrangescount.cpp)

For every interval, count how many other intervals it contains and how many contain it.

## Sorting Reduction

Sort by increasing left endpoint and decreasing right endpoint on ties. In a forward scan, earlier intervals already satisfy $l'\le l$. The current interval is contained by exactly those earlier intervals with $r'\ge r$. In a reverse scan, later intervals satisfy $l'\ge l$, and the current interval contains exactly those with $r'\le r$.

Right endpoints may be large, but only their order matters. Coordinate compression maps them to ranks. A Fenwick tree then counts earlier or later endpoints in a prefix, while total inserted count minus a shorter prefix gives a suffix count.

## Algorithm

Compress all right endpoints and sort intervals with the containment tie rule. Scan forward: `total - query(id-1)` counts earlier right endpoints at least the current one. Clear the tree. Scan backward: `query(id)` counts later endpoints at most the current one. Store answers by original index.

## Correctness

In the forward scan, every inserted interval begins no later than the current one. The Fenwick suffix count includes exactly inserted intervals whose right endpoint reaches at least the current right endpoint, which are precisely its containers.

In the reverse scan, every inserted interval begins no earlier. The Fenwick prefix count includes exactly those ending no later than the current interval, which are precisely the intervals it contains. Compression preserves all endpoint comparisons, so both counts are exact and original indices restore the required order.

### Complexity

Compression and sorting take $O(n\log n)$ time. Each of two scans performs $O(n)$ Fenwick operations at $O(\log n)$ each. Space is $O(n)$.

## Implementation

Equal right endpoints share one compressed id. The tree is cleared between directional scans. The sorting tie rule places wider equal-start intervals before narrower ones, matching the implementation's forward and reverse interpretations.

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
int n, m;
int bit[200005];
void upd(int i, int v){ for(; i <= m; i += i & -i) bit[i] += v; }
int qry(int i){ int r = 0; for(; i > 0; i -= i & -i) r += bit[i]; return r; }
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	vector<array<int,3>> r(n);
	vector<int> ys;
	for(int i = 0; i < n; i++){
		int x, y; cin >> x >> y;
		r[i] = {x, y, i};
		ys.pb(y);
	}
	sort(ys.begin(), ys.end());
	ys.erase(unique(ys.begin(), ys.end()), ys.end());
	m = ys.size();
	auto yid = [&](int y){ return int(lower_bound(ys.begin(), ys.end(), y) - ys.begin()) + 1; };

	sort(r.begin(), r.end(), [](const array<int,3>& a, const array<int,3>& b){
		if(a[0] != b[0]) return a[0] < b[0];
		return a[1] > b[1];
	});

	vector<int> contains(n, 0), contained(n, 0);

	// forward: earlier ranges have x'<=x; current is contained by those with y'>=y
	for(int i = 0; i < n; i++){
		int id = yid(r[i][1]);
		contained[r[i][2]] = qry(m) - qry(id - 1);
		upd(id, 1);
	}
	for(int i = 1; i <= m; i++) bit[i] = 0;

	// reverse: later ranges have x'>=x; current contains those with y'<=y
	for(int i = n-1; i >= 0; i--){
		int id = yid(r[i][1]);
		contains[r[i][2]] = qry(id);
		upd(id, 1);
	}

	for(int i = 0; i < n; i++) cout << contains[i] << (i+1==n?'\n':' ');
	for(int i = 0; i < n; i++) cout << contained[i] << (i+1==n?'\n':' ');
	return 0;
}
```

## Worked Example

For $[1,6],[2,4],[4,8]$, compressed right endpoints are $4,6,8$. In the forward scan, $[2,4]$ sees one earlier endpoint at least 4. In reverse, $[1,6]$ sees one later endpoint at most 6. All other containment counts are zero.

## Takeaway

After sorting one coordinate, dominance counting in the other coordinate becomes prefix or suffix counting in a Fenwick tree.

### Related problems

Nested Ranges Check needs only running extrema. More general offline dominance queries use the same sort-and-Fenwick pattern.
