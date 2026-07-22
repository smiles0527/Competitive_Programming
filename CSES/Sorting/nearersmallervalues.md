# Nearest Smaller Values

## Problem

- **Source:** [CSES 1645: Nearest Smaller Values](https://cses.fi/problemset/task/1645/)
- **Code:** [`View accepted C++ solution (nearersmallervalues.cpp)`](./nearersmallervalues.cpp)

For every array position, find the nearest earlier position containing a strictly smaller value, or output 0 if none exists.

## Monotonic Stack

The stack keeps exactly the undominated earlier positions, with both indices and values increasing from bottom to top.

Scanning backward independently costs $O(n^2)$. During a left-to-right scan, suppose an earlier index $j$ is followed by a later index $q$ with $a_q\le a_j$. For any future value smaller than $a_j$, index $q$ blocks $j$: it is closer and no larger. Thus $j$ can be discarded permanently.

Maintain indices whose values are strictly increasing. Before answering position $i$, pop every top with value at least $a_i$. The remaining top, if any, is smaller. It is also nearest because every later index not in the stack was removed only after being dominated by an even later candidate.

## Algorithm

Use a vector as a monotonic stack of indices. For each $i$, pop while the top value is at least $a_i$. Output the top index plus one, or 0 if empty, then push $i$.

## Correctness

After the popping loop, every stack value is strictly smaller than $a_i$, so the top is a valid answer. Any earlier index closer than the top is absent from the stack. When such an index was removed, a later index with no larger value replaced it; following these replacements leads to a surviving candidate closer to $i$. Since all candidates at least $a_i$ have just been removed, no omitted closer index can be valid while the top is not nearest.

If the stack is empty, every earlier candidate was dominated or had value at least $a_i$, so no smaller earlier value exists. Therefore every output is correct.

### Complexity

Each index is pushed once and popped at most once, giving $O(n)$ time and $O(n)$ space.

## Implementation

The pop comparison uses `>=` because the required value is strictly smaller. Indices are stored zero-based and converted only for output.

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
	vector<int> x(n);
	for(auto &v : x) cin >> v;
	vector<int> st;                              // stack of indices, increasing values
	for(int i = 0; i < n; i++){
		while(!st.empty() && x[st.back()] >= x[i]) st.pop_back();
		int ans = st.empty() ? 0 : st.back() + 1;   // 1-based, 0 if none
		cout << ans << (i+1 == n ? '\n' : ' ');
		st.pb(i);
	}
	return 0;
}
```

## Worked Example

For $2,5,1,4,3$, stacks by value after each step are $[2]$, $[2,5]$, $[1]$, $[1,4]$, and $[1,3]$. The reported positions are $0,1,0,3,3$.

## Takeaway

A monotonic stack removes candidates once a later element dominates them for every possible future query.

### Related problems

Next greater element, histogram area, and Cartesian-tree construction use the same dominance principle.
