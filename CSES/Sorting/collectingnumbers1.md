# Collecting Numbers

## Problem

- **Source:** [CSES 2216: Collecting Numbers](https://cses.fi/problemset/task/2216/)
- **Code:** [`View accepted C++ solution (collectingnumbers1.cpp)`](./collectingnumbers1.cpp)

The numbers $1,2,\ldots,n$ appear in a permutation. During one left-to-right pass, collect numbers in increasing order. Find the number of passes required.

## Idea

Let $\operatorname{pos}(v)$ be the position of value $v$. Values $v$ and $v+1$ can be collected in the same pass precisely when

$$
\operatorname{pos}(v)<\operatorname{pos}(v+1).
$$

If the inequality is reversed, the scan has already passed $v+1$ when it collects $v$, so a new pass is unavoidable. Conversely, between two such reversals, positions increase with the values, so that entire consecutive block can be collected in one pass.

The required passes are therefore one plus the number of adjacent-value inversions $\operatorname{pos}(v+1)<\operatorname{pos}(v)$.

## Algorithm

Build the inverse permutation `pos`. Start `rounds` at 1. For every $v$ from 1 through $n-1$, increment it when `pos[v+1] < pos[v]`.

## Correctness

Every detected reversal forces a boundary between two passes: after collecting $v$, the current left-to-right scan cannot return to the earlier position of $v+1$. Thus at least one new pass is needed for each reversal.

Partition $1,2,\ldots,n$ immediately after every reversal. Within each resulting block, positions are strictly increasing, so one left-to-right scan collects the entire block in order. The blocks can be collected in successive passes. Hence the lower bound is attainable, and the algorithm's count is exact.

### Complexity

Building and scanning `pos` take $O(n)$ time and $O(n)$ space.

## Implementation

`pos[x] = i` constructs the inverse permutation while reading. The count begins at 1 because a nonempty permutation always requires at least one pass.

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
int pos[200005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; i++){
		int x; cin >> x;
		pos[x] = i;
	}
	int rounds = 1;
	for(int v = 1; v < n; v++)
		if(pos[v+1] < pos[v]) rounds++;          // v+1 is left of v -> new pass
	cout << rounds << '\n';
	return 0;
}
```

## Worked Example

For permutation $4,2,1,5,3$, positions of values $1$ through $5$ are $3,2,5,1,4$. Reversals occur from 1 to 2 and from 3 to 4. The value sequence splits into $[1]$, $[2,3]$, and $[4,5]$, requiring three passes.

## Takeaway

When operations scan a permutation but requirements are expressed by value order, invert the permutation. Global passes may then become local comparisons between consecutive values.

### Related problems

Collecting Numbers II maintains the same reversal count under swaps.
