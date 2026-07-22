# Josephus Problem II

## Problem

- **Source:** [CSES 2163: Josephus Problem II](https://cses.fi/problemset/task/2163/)
- **Code:** [`View accepted C++ solution (josephus2.cpp)`](./josephus2.cpp)

Children $1,2,\ldots,n$ stand in a circle. Repeatedly skip $k$ surviving children and remove the next. Output the removal order.

## Rank Transition

With $m$ survivors, keep `idx` as a zero-based rank in their circular order. Skipping $k$ children makes the victim rank

$$
\texttt{idx}\leftarrow(\texttt{idx}+k)\bmod m.
$$

After removing that rank, its successor slides into the same rank, so this value is also the next cursor, modulo the new survivor count.

The missing operation is selecting and deleting the child of a given surviving rank. A Fenwick tree stores 1 for alive positions and 0 for removed positions. Its prefix sum is the number alive through an original index, so Fenwick binary lifting finds the smallest index whose prefix count reaches a requested rank.

## Algorithm

Initialize a Fenwick tree with one at every position. Repeatedly update the victim rank modulo the current survivor count, locate the corresponding one with `findkth`, output and delete it, then normalize the rank for the smaller circle.

## Correctness

Before each iteration, `idx` denotes the next cursor among the $m$ survivors. Advancing it by $k$ modulo $m$ selects exactly the child after skipping $k$. `findkth(idx+1)` returns that survivor because Fenwick prefix sums count alive children in original circular order.

Deleting the child changes its successor's rank to the removed rank. The final modulo operation wraps this rank to zero when the last survivor in order was removed. Thus the invariant holds for the next iteration. Every iteration outputs exactly the required victim and deletes it once, so the complete order is correct.

### Complexity

Each selection and deletion costs $O(\log n)$, for $O(n\log n)$ time and $O(n)$ space.

## Implementation

`k` and the rank addition use `long long` before reduction. `findkth` performs Fenwick binary lifting: it advances over blocks whose alive count is still smaller than the desired rank. The update with $-1$ marks a child removed.

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
ll k;
int N;
int bit[200005];
int LOGN;
void upd(int i, int v){ for(; i <= n; i += i & -i) bit[i] += v; }
int findkth(int j){                              // smallest index with prefix sum == j
	int pos = 0;
	for(int pw = LOGN; pw >= 0; pw--){
		int nx = pos + (1 << pw);
		if(nx <= n && bit[nx] < j){ pos = nx; j -= bit[nx]; }
	}
	return pos + 1;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> k;
	LOGN = 0; while((1 << (LOGN+1)) <= n) LOGN++;
	for(int i = 1; i <= n; i++) upd(i, 1);
	int m = n;
	int idx = 0;                                 // 0-based pointer among survivors
	vector<int> out; out.reserve(n);
	for(int step = 0; step < n; step++){
		idx = (int)(((ll)idx + k) % m);          // 0-based victim index
		int child = findkth(idx + 1);            // (idx+1)-th alive child
		out.pb(child);
		upd(child, -1);
		m--;
		// pointer now references the child after the removed one, still at 'idx'
		// but if idx == m (removed last in current ordering), wrap to 0
		if(m > 0) idx %= m;
	}
	for(int i = 0; i < n; i++) cout << out[i] << (i+1 == n ? '\n' : ' ');
	return 0;
}
```

## Worked Example

For $n=5$ and $k=2$, the first victim rank is 2, so child 3 is removed. The next cursor remains at rank 2 among $1,2,4,5$; advancing by 2 wraps to rank 0, removing child 1. The same process continues without rotating an explicit list.

## Takeaway

When a dynamic ordered set needs deletion by rank, store occupancy counts in a Fenwick tree and use prefix-sum selection.

### Related problems

List Removals uses the same order-statistic Fenwick operation. Josephus Problem I admits a simpler queue because its movement is constant.
