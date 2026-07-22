# Missing Coin Sum

## Problem

- **Source:** [CSES 2183: Missing Coin Sum](https://cses.fi/problemset/task/2183/)
- **Code:** [`View accepted C++ solution (missingcoinsum.cpp)`](./missingcoinsum.cpp)

Given positive coin values, find the smallest positive sum that cannot be formed by selecting a subset of the coins.

## Invariant

Equivalently, maintain `reach = ans - 1`: every sum in $[0,\text{reach}]$ is constructible, and the first possible gap is $\text{reach}+1$.

The $2^n$ subsets cannot be enumerated. Sorting exposes a stronger invariant. Suppose the processed coins can form every sum in the interval $[1,R]$.

Let the next coin have value $v$. If $v\le R+1$, sums not using it still cover $[1,R]$, while sums using it cover $[v,v+R]$. These intervals touch or overlap, so together they cover every value through $R+v$.

If $v>R+1$, then $R+1$ is impossible. Processed coins sum to at most $R$ for the coverage argument, and every unprocessed coin is at least $v>R+1$. No later choice can fill the gap. This identifies both the extension rule and the stopping condition.

## Algorithm

Sort the coin values. Set `reach = 0`, meaning that all sums in the empty interval $[1,0]$ are currently covered. For each coin `v`, stop if `v > reach + 1`; otherwise add `v` to `reach`. Output `reach + 1`.

## Correctness

We maintain the invariant that after each accepted coin, every sum in $[1,\texttt{reach}]$ is constructible from processed coins.

Initially `reach = 0`, so the invariant holds. Suppose it holds before processing $v$ and $v\le\texttt{reach}+1$. Sums through `reach` remain constructible without $v$. For each $s$ from $v$ through $v+\texttt{reach}$, construct $s$ by taking $v$ together with a subset summing to $s-v$, where $s-v$ lies in $[0,\texttt{reach}]$. Since the two ranges have no gap, all sums through `reach + v` are constructible, preserving the invariant.

If the algorithm stops at $v>\texttt{reach}+1$, the invariant shows that smaller positive sums are constructible. A subset without $v$ or later coins cannot exceed the established contiguous range to reach the missing value, while any subset using an unprocessed coin has sum at least $v$. Therefore `reach + 1` is not constructible and is the smallest missing positive sum. The same conclusion holds after all coins are accepted.

### Complexity

Sorting takes $O(n\log n)$ time, the scan takes $O(n)$ time, and the array uses $O(n)$ space.

## Implementation

All coin values are positive, which is necessary for the gap argument. `reach` uses `long long` because the sum of the coins can exceed 32-bit range. The cast in the comparison ensures `reach + 1` is evaluated safely.

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
	sort(x.begin(), x.end());
	ll reach = 0;
	for(int v : x){
		if((ll)v > reach + 1) break;             // gap at reach+1
		reach += v;
	}
	cout << reach + 1 << '\n';
	return 0;
}
```

## Worked Example

For coins $1,1,3,8$, the covered endpoint changes from 0 to 1, then 2, then 5. The next coin is 8, which is greater than $5+1$. Thus 6 cannot be formed, even though sums such as 8 and 9 can be formed, and the algorithm outputs 6.

## Takeaway

When positive items are sorted, try maintaining a contiguous interval of reachable values. If the next item begins beyond the first uncovered value, later items cannot repair the gap.

### Related problems

The same coverage invariant appears in patching-array problems, where new values may be inserted to eliminate gaps.
