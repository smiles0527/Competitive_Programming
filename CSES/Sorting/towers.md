# Towers

## Problem

- **Source:** [CSES 1073: Towers](https://cses.fi/problemset/task/1073/)
- **Code:** [`View accepted C++ solution (towers.cpp)`](./towers.cpp)

Process cubes in order. A cube may be placed on a tower only when it is strictly smaller than the current top. Find the minimum number of towers.

## Greedy Choice

For a cube of size $k$, any tower with top greater than $k$ is feasible. Among them, choose the smallest such top. Replacing a larger feasible top would leave the smaller top unchanged, producing a pair of tops that is never more useful for future cubes. Using the smallest feasible top instead leaves the larger top available and preserves at least as many future choices.

If no top is greater than $k$, no existing tower can accept the cube, so opening a new tower is forced. The maintained tower tops therefore contain all information needed about the past.

## Algorithm

Store current tower tops in a multiset. For each cube $k$, find `upper_bound(k)`, the smallest top strictly greater than $k$. If it exists, erase that occurrence and insert $k$. Otherwise insert $k$ as a new tower. Output the multiset size.

## Correctness

We prove that the greedy processing uses the minimum possible number of towers for every prefix.

If no current top exceeds $k$, every valid arrangement of the processed prefix must start a new tower for $k$. If feasible tops exist, let $t$ be the smallest one. Consider any optimal continuation that places $k$ on a different feasible top $u\ge t$. Swapping the roles of $t$ and $u$ leaves $k$ on $t$ and keeps $u$ available. Since $u\ge t$, any later cube that could be placed on the old top $t$ can also be placed on $u$. The exchange does not increase the tower count or invalidate the future.

Thus an optimum exists after every greedy choice. By induction over the cubes, the final number of towers is minimum.

### Complexity

Each multiset search, deletion, and insertion costs $O(\log n)$. Total time is $O(n\log n)$ and space is $O(n)$.

## Implementation

The condition is strict, so `upper_bound` is required. `lower_bound` would incorrectly allow an equal cube below another equal cube. The multiset is necessary because several towers may have the same top.

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
	multiset<int> tops;                          // current top size of each tower
	for(int i = 0, k; i < n; i++){
		cin >> k;
		auto it = tops.upper_bound(k);           // smallest top strictly > k
		if(it == tops.end()) tops.insert(k);     // no fit -> new tower
		else { tops.erase(it); tops.insert(k); } // place on that tower, update top
	}
	cout << tops.size() << '\n';
	return 0;
}
```

## Worked Example

For cubes $3,8,2,1,5$, the sorted multisets of tops become $\{3\}$, $\{3,8\}$, $\{2,8\}$, $\{1,8\}$, and $\{1,5\}$. Two towers suffice.

## Takeaway

When assigning an item to a feasible container, using the tightest feasible container often preserves the most flexible resources. This is the same ordered-frontier idea used by patience sorting.

### Related problems

The multiset of tops is closely related to longest increasing subsequence decompositions and minimum chain covers in ordered sets.
