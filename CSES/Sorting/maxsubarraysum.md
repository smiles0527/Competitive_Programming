# Maximum Subarray Sum

## Problem

- **Source:** [CSES 1643: Maximum Subarray Sum](https://cses.fi/problemset/task/1643/)
- **Code:** [`View accepted C++ solution (maxsubarraysum.cpp)`](./maxsubarraysum.cpp)

Find the maximum sum of a nonempty contiguous subarray.

## Idea

There are $\Theta(n^2)$ subarrays, too many to enumerate when $n$ reaches $2\cdot10^5$. Instead, process right endpoints. Define $E_i$ as the maximum sum of a nonempty subarray ending exactly at position $i$.

A subarray counted by $E_i$ has only two possible forms. It either starts at $i$, with sum $a_i$, or extends the best subarray ending at $i-1$, with sum $E_{i-1}+a_i$. Extending any worse subarray cannot improve the result because the same $a_i$ is added to every candidate. Therefore

$$
E_i=\max(a_i,E_{i-1}+a_i).
$$

Every nonempty subarray has exactly one right endpoint, so the answer is $\max_i E_i$. This is Kadane's algorithm viewed as a one-state dynamic program.

## Algorithm

Maintain `cur`, the best sum ending at the current position, and `best`, the largest `cur` seen. For each value `x`, set `cur = max(x, cur + x)`, then update `best`.

## Correctness

We prove by induction that after processing position $i$, `cur` equals $E_i$.

At the first position, the only nonempty subarray ending there contains that one value, and the update chooses it. For the induction step, every subarray ending at $i$ either begins at $i$ or consists of a subarray ending at $i-1$ followed by $a_i$. By the induction hypothesis, `cur` before the update is the best possible prefix of the second form. The recurrence therefore chooses the best among all subarrays ending at $i$.

After each update, `best` is the maximum of $E_1,\ldots,E_i$. At termination this covers every possible right endpoint, so `best` is the maximum sum of every nonempty contiguous subarray.

### Complexity

The algorithm uses $O(n)$ time and $O(1)$ auxiliary space.

## Implementation

`best` starts at `LLONG_MIN`, not zero, because the answer must be nonempty and every value may be negative. Sums can reach magnitude $2\cdot10^{14}$, so both states use `long long`.

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
	ll cur = 0, best = LLONG_MIN;
	for(int i = 0; i < n; i++){
		ll x; cin >> x;
		cur = max(x, cur + x);
		best = max(best, cur);
	}
	cout << best << '\n';
	return 0;
}
```

## Worked Example

For $-1,3,-2,5,-7,4$, the successive values of `cur` are $-1,3,1,6,-1,4$. The successive `best` values are $-1,3,3,6,6,6$. The optimum is the subarray $3,-2,5$ with sum 6.

## Takeaway

When optimizing over all contiguous subarrays, classify candidates by their right endpoint. If extending a candidate depends only on its value, one best ending state may summarize the entire past.

### Related problems

Maximum Subarray Sum II adds length bounds and replaces the single state with prefix sums and a maintained range minimum.
