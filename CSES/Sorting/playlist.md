# Playlist

## Problem

- **Source:** [CSES 1141: Playlist](https://cses.fi/problemset/task/1141/)
- **Code:** [`View accepted C++ solution (playlist.cpp)`](./playlist.cpp)

Find the maximum length of a contiguous segment in which every song identifier is distinct.

## Sliding-Window Invariant

Fix the right endpoint and maintain the earliest valid left endpoint. Because this boundary never moves backward, every position is processed once.

There are $\Theta(n^2)$ contiguous segments, so checking each one is infeasible for $n\le 2\cdot10^5$. Instead, fix the right endpoint $r$ and determine the earliest valid left endpoint.

Maintain a window $[l,r]$ containing no duplicate. When song $k_r$ last appeared before $l$, it creates no conflict. If its last occurrence is at position $p\ge l$, every segment ending at $r$ and beginning at or before $p$ contains the duplicate pair $(p,r)$. The smallest repair is therefore

$$
l\leftarrow p+1.
$$

The left endpoint never moves backward. This monotonicity makes it possible to process each right endpoint once.

## Algorithm

Maintain a hash map `last` from each identifier to its latest index, and a left endpoint `l`. At each right endpoint `r`, move `l` just after the previous occurrence when that occurrence lies inside the current window. Store the new latest index and maximize `r - l + 1`.

## Correctness

We maintain the invariant that $[l,r]$ contains distinct values and that $l$ is the smallest valid left endpoint for this $r$.

Before adding $k_r$, the previous window is distinct. If the latest occurrence $p$ of $k_r$ lies outside it, adding $k_r$ preserves distinctness and no movement is needed. If $p\ge l$, setting $l=p+1$ removes the only possible duplicate involving the new element. Starting any earlier would retain both occurrences, so the new $l$ is minimal.

Thus `r - l + 1` is the longest valid segment ending at each $r$. Every valid segment has some right endpoint, so the maximum recorded length is the global optimum.

### Complexity

The expected running time is $O(n)$ and the hash map uses $O(n)$ space.

## Implementation

The check `it->second >= l` prevents an old occurrence from moving `l` backward. Updating `last[k[r]]` after repairing the window ensures later iterations see the most recent occurrence.

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
	vector<int> k(n);
	for(auto &v : k) cin >> v;
	unordered_map<int,int> last;
	last.reserve(2*n);
	int l = 0, best = 0;
	for(int r = 0; r < n; r++){
		auto it = last.find(k[r]);
		if(it != last.end() && it->s >= l) l = it->s + 1;   // shrink past duplicate
		last[k[r]] = r;
		best = max(best, r - l + 1);
	}
	cout << best << '\n';
	return 0;
}
```

## Worked Example

For $1,2,1,3,2,7$, the left endpoints for right endpoints 0 through 5 are $0,0,1,1,2,2$. The corresponding window lengths are $1,2,2,3,3,4$. The longest distinct segment is $1,3,2,7$.

## Takeaway

For a longest segment with a uniqueness constraint, store last occurrences and move the left endpoint directly past the conflicting position.

### Related problems

Distinct Values Subarrays counts all distinct windows using the same monotone boundary. Other frequency constraints use a sliding window with explicit counts.
