# Traffic Lights

## Problem

- **Source:** [CSES 1163: Traffic Lights](https://cses.fi/problemset/task/1163/)
- **Code:** [`View accepted C++ solution (trafficlights.cpp)`](./trafficlights.cpp)

Traffic lights are added one by one along a street. After each insertion, report the longest segment between consecutive lights.

## Maintained Structures

A forward solution can maintain ordered light positions and a multiset of gap lengths. This implementation uses the equally useful reverse viewpoint. First insert every light. Then remove lights in reverse order.

Removing a light $v$ between neighboring lights $L$ and $R$ deletes gaps $v-L$ and $R-v$, and creates the merged gap $R-L$. This is a local update. Immediately before removing the light inserted at step $i$, the structure represents the street after the first $i+1$ insertions, so its largest gap is exactly answer $i$.

## Algorithm

Build an ordered set containing endpoints 0 and $x$ plus all inserted lights. Build a multiset containing every adjacent gap. Traverse insertions backward. Record the largest gap, locate the removed light's neighbors, replace its two adjacent gaps by their sum, and erase the light. Print recorded answers in forward order.

## Correctness

At the start of reverse iteration $i$, the position set contains the endpoints and exactly the first $i+1$ inserted lights. The gap multiset contains one length for every pair of consecutive positions. Therefore its maximum is the required answer after insertion $i$.

When removing $p_i$, all consecutive pairs remain unchanged except $(L,p_i)$ and $(p_i,R)$. The algorithm removes exactly their two lengths and adds $R-L$, the length of the newly consecutive pair $(L,R)$. Hence the invariant holds for the next reverse iteration. Every stored answer is consequently correct.

### Complexity

Building and updating the ordered containers takes $O(n\log n)$ time. The sets, multiset, and answer array use $O(n)$ space.

## Implementation

`gaps.erase(gaps.find(value))` removes one occurrence, while `gaps.erase(value)` would remove every equal gap. Endpoints remain permanently, so every removed light has both a predecessor and successor. Answers are stored before removal.

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
int x, n;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> x >> n;
	vector<int> p(n);
	for(auto &v : p) cin >> v;

	set<int> pts;
	pts.insert(0); pts.insert(x);
	for(int v : p) pts.insert(v);

	multiset<int> gaps;
	{
		int prev = -1;
		for(int v : pts){
			if(prev != -1) gaps.insert(v - prev);
			prev = v;
		}
	}

	vector<int> ans(n);
	for(int i = n - 1; i >= 0; i--){
		ans[i] = *gaps.rbegin();                  // max gap with first i+1 lights present
		int v = p[i];
		auto it = pts.find(v);
		auto nx = next(it), pv = prev(it);
		int R = *nx, L = *pv;
		gaps.erase(gaps.find(R - v));             // remove the two adjacent gaps
		gaps.erase(gaps.find(v - L));
		gaps.insert(R - L);                       // merge
		pts.erase(it);
	}
	for(int i = 0; i < n; i++) cout << ans[i] << (i+1 == n ? '\n' : ' ');
	return 0;
}
```

## Worked Example

On a street of length 10, insert lights at $3,6,2$. With all lights present, gaps are $2,1,3,4$, so the last answer is 4. Remove 2, merging gaps 2 and 1 into 3, giving maximum 4 for the first two lights. Remove 6, merging gaps 3 and 4 into 7, giving the first answer 7. Printed forward, the answers are $7,4,4$.

## Takeaway

When additions split components or intervals, reversing time may turn them into simpler merges. Record each answer before undoing the corresponding operation.

### Related problems

Reverse processing also powers offline dynamic connectivity with disjoint-set union, where deletions become additions.
