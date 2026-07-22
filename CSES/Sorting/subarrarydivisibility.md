# Subarray Divisibility

## Problem

- **Source:** [CSES 1662: Subarray Divisibility](https://cses.fi/problemset/task/1662/)
- **Code:** [`View accepted C++ solution (subarrarydivisibility.cpp)`](./subarrarydivisibility.cpp)

Count contiguous subarrays whose sum is divisible by $n$.

## Prefix-Sum Congruence Condition

For prefix sums $P_i$ and $P_j$, subarray sum $P_i-P_j$ is divisible by $n$ exactly when

$$
P_i\equiv P_j\pmod n.
$$

Therefore each new prefix forms a valid subarray with every earlier prefix having the same residue. It is enough to maintain a frequency for each of the $n$ residue classes.

In C++, the remainder of a negative number can be negative. Normalizing with `((pre % n) + n) % n` maps every equivalent prefix to the same index in $[0,n-1]$.

## Algorithm

Initialize residue 0 with frequency one for the empty prefix. Scan the array, update the prefix sum and its normalized residue, add the residue's previous frequency to the answer, and increment that frequency.

## Correctness

Before processing $P_i$, `cntRes[r]` equals the number of earlier prefixes with normalized residue $r$. For each such prefix $P_j$ sharing the residue of $P_i$, $P_i-P_j$ is divisible by $n$, giving a valid subarray ending at $i$. Prefixes with other residues cannot give a divisible difference.

The algorithm adds exactly this number and then records $P_i$ for later endpoints. Thus every divisible-sum subarray is counted once by its right endpoint, and no other subarray is counted.

### Complexity

The scan takes $O(n)$ time and the residue array uses $O(n)$ space.

## Implementation

The empty prefix is required to count prefixes whose own sum is divisible by $n$. The answer may be $n(n+1)/2$, so it uses `long long`.

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
	vector<ll> cntRes(n, 0);
	cntRes[0] = 1;                               // empty prefix, residue 0
	ll pre = 0, ans = 0;
	for(int i = 0; i < n; i++){
		ll v; cin >> v;
		pre += v;
		int r = (int)(((pre % n) + n) % n);      // normalized residue
		ans += cntRes[r];                        // pairs with same residue seen before
		cntRes[r]++;
	}
	cout << ans << '\n';
	return 0;
}
```

## Worked Example

For $3,1,2,7,4$ with $n=5$, normalized prefix residues are $0,3,4,1,3,2$. Residue 3 occurs twice, producing the subarray between those prefixes, $1,2,7$, whose sum 10 is divisible by 5.

## Takeaway

Divisibility of a range sum becomes equality of prefix residues. Count equal states rather than enumerating ranges.

## Problems Related to This Topic

Subarray Sums II uses the same prefix-pair framework with an exact difference instead of congruence.
