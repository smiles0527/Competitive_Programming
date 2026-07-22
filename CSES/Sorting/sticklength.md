# Stick Lengths

## Problem

- **Source:** [CSES 1074: Stick Lengths](https://cses.fi/problemset/task/1074/)
- **Code:** [`View accepted C++ solution (sticklength.cpp)`](./sticklength.cpp)

Change all stick lengths to one common integer length while minimizing the total number of unit changes.

## Idea

If the chosen target is $t$, the total cost is

$$
f(t)=\sum_{i=1}^{n}|a_i-t|.
$$

After sorting $a_1\le\cdots\le a_n$, consider increasing $t$ by one. Every value at or below $t$ contributes one more unit of cost, while every value above $t$ contributes one less. Thus the cost decreases while more than half the values lie to the right, and increases once more than half lie to the left. A minimum is reached at a median.

For odd $n$, the middle value is a median. For even $n$, every target between the two middle values has the same minimum cost, so choosing `a[n/2]` is valid.

## Algorithm

Sort the lengths, choose the element at index $\lfloor n/2\rfloor$, and sum its absolute distance from every length.

## Correctness

Let $m=a_{\lfloor n/2\rfloor}$ in sorted order. If a target $t<m$ is increased toward $m$, at least as many array values lie above the current target as lie at or below it. The total absolute deviation therefore cannot increase. Hence some minimum is attained at $m$ rather than below it.

If $t>m$ is decreased toward $m$, at least as many values lie at or below the current target as lie above it, so the total deviation again cannot increase. Hence no target above $m$ has smaller cost. Therefore $m$ minimizes the total number of changes, and the sum computed by the algorithm is optimal.

### Complexity

Sorting costs $O(n\log n)$ time, the summation costs $O(n)$ time, and the array uses $O(n)$ space.

## Implementation

The median itself fits in `int`, but the total cost can be about $2\cdot10^{14}$, so `med`, `cost`, and the subtraction passed to `llabs` use `long long`.

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
	vector<int> p(n);
	for(auto &v : p) cin >> v;
	sort(p.begin(), p.end());
	ll med = p[n/2];
	ll cost = 0;
	for(int v : p) cost += llabs((ll)v - med);
	cout << cost << '\n';
	return 0;
}
```

## Worked Example

For lengths $1,2,2,7,9$, the median is 2. The distances are $1,0,0,5,7$, giving cost 13. Moving the target to 3 changes the distances to $2,1,1,4,6$, whose sum is 14.

## Takeaway

The median minimizes a sum of absolute deviations. This contrasts with squared deviations, which are minimized by the mean.

### Related problems

Weighted variants use a weighted median. Convex cost functions can often be recognized by examining how the discrete slope changes as the target moves.
