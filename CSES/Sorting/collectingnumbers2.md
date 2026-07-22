# Collecting Numbers II

## Problem

- **Source:** [CSES 2217: Collecting Numbers II](https://cses.fi/problemset/task/2217/)
- **Code:** [`View accepted C++ solution (collectingnumbers2.cpp)`](./collectingnumbers2.cpp)

Maintain the number of collection passes for a permutation after each swap of two positions.

## Round Boundaries

As in Collecting Numbers, the answer is

$$
1+\sum_{v=1}^{n-1}[\operatorname{pos}(v+1)<\operatorname{pos}(v)].
$$

Recomputing this sum after every swap costs $O(nm)$. A swap changes the positions of only two values, say $u$ and $w$. The term indexed by $v$ depends only on positions of $v$ and $v+1$. Consequently, only terms with indices

$$
u-1,\ u,\ w-1,\ w
$$

can change. This constant-size dependency boundary is the central observation.

## Algorithm

Maintain both the permutation `arr` and its inverse `pos`, plus `breaks`, the number of reversed consecutive-value pairs. For a swap, deduplicate the four potentially affected indices. Subtract their old contributions, perform the swap in both arrays, add their new contributions, and output `breaks + 1`.

## Correctness

Before each query, `breaks` equals the sum of all reversal indicators. For swapped values $u$ and $w$, every indicator outside the set $\{u-1,u,w-1,w\}$ depends on two positions that do not change, so its contribution remains valid.

The algorithm removes exactly the old contributions of all potentially changed indicators. It then updates `arr` and `pos` consistently and adds exactly their new contributions. Therefore the invariant is restored after the swap. Since the number of passes is always one plus this reversal count, every printed answer is correct.

### Complexity

Initialization takes $O(n)$ time. Each query performs operations on a set of at most four integers, so it takes $O(1)$ time in asymptotic terms. The arrays use $O(n)$ space.

## Implementation

`isbreak` rejects indices outside $[1,n-1]$. A `set` deduplicates affected indices, which matters when the swapped values are consecutive or otherwise make the four expressions overlap. Contributions are removed before changing `pos` and restored afterward.

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
int arr[200005], pos[200005];
int breaks = 0;
bool isbreak(int v){                              // contributes if pos[v+1] < pos[v]
	if(v < 1 || v+1 > n) return false;
	return pos[v+1] < pos[v];
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		cin >> arr[i];
		pos[arr[i]] = i;
	}
	for(int v = 1; v < n; v++) if(isbreak(v)) breaks++;
	while(m--){
		int a, b;
		cin >> a >> b;
		int u = arr[a], w = arr[b];
		// affected adjacency indices: {u-1,u,w-1,w}, dedup
		set<int> aff = {u-1, u, w-1, w};
		for(int v : aff) if(isbreak(v)) breaks--;   // remove old contributions
		swap(arr[a], arr[b]);
		pos[u] = b; pos[w] = a;
		for(int v : aff) if(isbreak(v)) breaks++;   // add new contributions
		cout << (breaks + 1) << '\n';
	}
	return 0;
}
```

## Worked Example

For $4,2,1,5,3$, the reversal indices are 1 and 3, so the answer is 3. Swap positions 1 and 3, exchanging values 4 and 1. Only indices $0,1,3,4$ need inspection. The new permutation $1,2,4,5,3$ has one reversal, from 3 to 4, so the answer becomes 2.

## Takeaway

If an answer is a sum of local predicates, an update only requires revisiting predicates whose dependencies intersect the changed data.

### Related problems

This dependency-boundary method appears in dynamic inversion variants, local string statistics, and maintaining graph quantities after a small set of edge changes.
