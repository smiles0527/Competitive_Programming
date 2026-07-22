# Sum of Four Values

## Problem

- **Source:** [CSES 1642: Sum of Four Values](https://cses.fi/problemset/task/1642/)
- **Code:** [`View accepted C++ solution (sumoffourvalues.cpp)`](./sumoffourvalues.cpp)

Find four distinct indices whose values sum to $x$, or report that none exist.

## Pair-Sum Reduction

Four nested loops are infeasible. Split a solution $i<j<k<l$ into two pairs. While fixing $k$, store sums of pairs whose second index is below $k$, then query pairs $(k,l)$. This ordering makes the two stored indices automatically disjoint from $k$ and $l$.

Before querying a particular $k$, the implementation inserts every pair $(i,k-1)$ with $i<k-1$. Together with pairs retained from previous iterations, the table then contains at least one representative of every sum from indices $i<j<k$.

## Algorithm

Maintain a hash map from pair sum to one index pair. For each $k$ from 2 through $n-1$, insert all pairs ending at $k-1$. Then for every $l>k$, search for `x - a[k] - a[l]`. Output the stored pair with $k,l$ when found.

## Correctness

Every reported stored pair has second index below $k$, and $l>k$, so all four indices are distinct and ordered. The successful complement lookup proves their values sum to $x$.

Conversely, consider any solution $i<j<k<l$. At iteration $k$, pair $(i,j)$ has been inserted because all pairs ending no later than $k-1$ are present. The query for $(k,l)$ requests exactly $a_i+a_j$, so it succeeds. Storing only one pair per sum is sufficient because every stored pair satisfies the same index separation from the current query pair.

### Complexity

There are $O(n^2)$ insertions and queries. Expected time and space are both $O(n^2)$.

## Implementation

Insertion occurs before queries for the current $k$, establishing strict index separation. `emplace` retains one representative per sum. The custom hash and reserved capacity improve robustness, while arithmetic uses `long long`.

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
	vector<ll> a(n);
	for(auto &v : a) cin >> v;

	unordered_map<ll, pair<int,int>, H> sp;
	sp.reserve(n*(n-1)/2 + 16);
	sp.max_load_factor(0.5);
	for(int k = 2; k < n; k++){
		for(int i = 0; i < k-1; i++)
			sp.emplace(a[i] + a[k-1], make_pair(i, k-1));   // pairs with larger index = k-1
		for(int l = k + 1; l < n; l++){
			auto it = sp.find(x - a[k] - a[l]);
			if(it != sp.end()){
				cout << it->s.first+1 << ' ' << it->s.second+1 << ' ' << k+1 << ' ' << l+1 << '\n';
				return 0;
			}
		}
	}
	cout << "IMPOSSIBLE\n";
	return 0;
}
```

## Worked Example

For $2,7,5,1,4$ and target 14, when $k$ reaches the value 1 at index 4, stored earlier pairs include $2+7=9$. Pairing current 1 with later 4 requests 9, so indices of $2,7,1,4$ are returned.

## Takeaway

Meet-in-the-middle within an ordered scan can enforce disjoint indices structurally, avoiding expensive overlap checks between arbitrary stored pairs.

### Related problems

Sum of Three Values uses sorting and two pointers. General meet-in-the-middle algorithms trade exponential time for exponential memory on two half-sized sets.
