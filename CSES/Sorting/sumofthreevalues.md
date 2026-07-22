# Sum of Three Values

## Problem

- **Source:** [CSES 1641: Sum of Three Values](https://cses.fi/problemset/task/1641/)
- **Code:** [`View accepted C++ solution (sumofthreevalues.cpp)`](./sumofthreevalues.cpp)

Find three distinct indices whose values sum to $x$, or report that no such triple exists.

## Fix One Value

Fix one selected element $a_i$. The remaining two values must sum to $x-a_i$. After sorting values together with original indices, this two-sum problem can be solved with pointers $l=i+1$ and $r=n-1$.

If $a_l+a_r$ is too small, increasing $l$ is the only move that may reach the target because every pair using the current $l$ and a smaller right value is no larger. If it is too large, decreasing $r$ is symmetric. Restricting both pointers to indices after $i$ guarantees three distinct sorted positions.

## Algorithm

Sort `(value, original index)` pairs. For each fixed position $i$, run a two-pointer search on positions $i+1$ through $n-1$ for sum $x-a_i$. Output original indices on success.

## Correctness

For fixed $i$, the pointer search never discards a possible pair. When the sum is below the target, no pair using the current left value can succeed, so advancing it is safe. When above, no pair using the current right value can succeed, so decreasing it is safe. Thus it finds a pair exactly when one exists after $i$.

Any triple of distinct sorted positions has a smallest position $i$. The outer loop eventually fixes it, and the inner search considers the other two. Hence every valid triple can be found. Any reported triple uses distinct positions and its tested sum equals $x$, so it is valid.

### Complexity

Sorting takes $O(n\log n)$ and all two-pointer searches take $O(n^2)$ time. Space is $O(n)$.

## Implementation

Original one-based indices travel with values through sorting. Sums use `long long`, while the loop condition `l < r` enforces distinct positions.

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
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> x;
	vector<ii> a(n);                             // {value, original index}
	for(int i = 0; i < n; i++){
		ll v; cin >> v;
		a[i] = {v, i + 1};
	}
	sort(a.begin(), a.end());
	for(int i = 0; i < n; i++){
		ll need = x - a[i].f;
		int l = i + 1, r = n - 1;
		while(l < r){
			ll sum = a[l].f + a[r].f;
			if(sum == need){
				cout << a[i].s << ' ' << a[l].s << ' ' << a[r].s << '\n';
				return 0;
			}
			if(sum < need) l++;
			else r--;
		}
	}
	cout << "IMPOSSIBLE\n";
	return 0;
}
```

## Worked Example

For values $2,7,5,1$ and target 10, sorted values are $1,2,5,7$. Fixing 1 leaves target 9. The pointers find $2+7=9$, yielding the original indices of 1, 2, and 7.

## Takeaway

Fixing one dimension can reduce a $k$-sum problem to a structured lower-dimensional search. Sorting supplies monotonic pointer moves.

### Related problems

Sum of Two Values is the base case. Sum of Four Values uses stored pair sums to remain quadratic.
