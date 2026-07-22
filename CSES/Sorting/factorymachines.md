# Factory Machines

## Problem

- **Source:** [CSES 1620: Factory Machines](https://cses.fi/problemset/task/1620/)
- **Code:** [`View accepted C++ solution (factorymachines.cpp)`](./factorymachines.cpp)

Machine $i$ produces one product every $k_i$ time units. Find the earliest time by which all machines have produced at least $t$ products in total.

## Production by a Fixed Time

At time $T$, machine $i$ has completed $\lfloor T/k_i\rfloor$ products, so feasibility is the predicate

$$
P(T):\quad \sum_{i=1}^{n}\left\lfloor\frac{T}{k_i}\right\rfloor\ge t.
$$

If $P(T)$ holds, it also holds for every later time because no machine's production count decreases. This false-then-true structure permits binary search for the first feasible time.

Time 1 is a valid lower search boundary. If $m=\min_i k_i$, the fastest machine alone produces $t$ products by time $mt$, so $mt$ is a feasible upper boundary.

## Algorithm

Binary search the inclusive interval `[1, m*t]`. At midpoint `mid`, sum `mid / k[i]`, stopping as soon as the sum reaches $t$. If feasible, retain `mid` as the upper boundary; otherwise discard it and everything below it.

## Correctness

Throughout the search, the earliest feasible time lies in `[lo, hi]`, and `hi` is feasible. Initially this follows from the fastest-machine bound. If `mid` is feasible, the first feasible time is at most `mid`, so setting `hi = mid` preserves it. Otherwise monotonicity shows every time through `mid` is infeasible, so setting `lo = mid + 1` preserves it.

When `lo == hi`, the interval contains only one value. The invariant makes it feasible, while every smaller value has been discarded only after being proved infeasible. It is therefore the earliest feasible time.

### Complexity

Each feasibility test costs $O(n)$ and there are $O(\log(mt))$ tests. Total time is $O(n\log(mt))$ and space is $O(n)$.

## Implementation

The production sum may overflow if accumulated unnecessarily. The predicate returns immediately once it reaches `t`. `mid = lo + (hi - lo) / 2` avoids overflowing the boundary addition, and all time arithmetic uses `long long`.

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
ll t;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> t;
	vector<ll> k(n);
	ll mn = LLONG_MAX;
	for(auto &v : k){ cin >> v; mn = min(mn, v); }

	auto ok = [&](ll T)->bool{
		ll cnt = 0;
		for(ll v : k){
			cnt += T / v;
			if(cnt >= t) return true;            // early exit avoids overflow
		}
		return cnt >= t;
	};

	ll lo = 1, hi = mn * t;                       // fastest machine alone
	while(lo < hi){
		ll mid = lo + (hi - lo) / 2;
		if(ok(mid)) hi = mid;
		else lo = mid + 1;
	}
	cout << lo << '\n';
	return 0;
}
```

## Worked Example

For machine times $2,3,7$ and target 8, time 8 produces $4+2+1=7$ products and is infeasible. Time 9 produces $4+3+1=8$ and is feasible. Binary search isolates 9 as the first feasible time.

## Takeaway

When a numerical answer asks for the earliest point at which cumulative capacity reaches a target, write the capacity predicate first and check whether it is monotone.

### Related problems

Array Division also binary searches an answer and validates each candidate greedily.
