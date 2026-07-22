# Reading Books

## Problem

- **Source:** [CSES 1631: Reading Books](https://cses.fi/problemset/task/1631/)
- **Code:** [`View accepted C++ solution (readingbooks.cpp)`](./readingbooks.cpp)

Two readers must each read every book. A book cannot be read by both people simultaneously. Find the minimum time until both have finished.

## Lower Bounds and Construction

Let $S$ be the sum of all reading times and $M$ the longest reading time.

Each reader performs $S$ units of work, so the completion time is at least $S$. Also, the longest book must be occupied for $M$ time by each reader, and those two readings cannot overlap. This gives a second lower bound of $2M$. Therefore every schedule needs at least

$$
\max(S,2M)
$$

time.

It remains to show that this bound can always be attained. If $M>S-M$, the longest book dominates. One reader reads it first while the other reads all remaining books, then they exchange workloads. The other books finish within the first $M$ time units, giving total time $2M$.

If $M\le S-M$, put a longest book first in reader A's order and last in reader B's order. Put all other books in the same order between those positions. For every shorter book, B begins it exactly $M$ time units before A. Its duration is at most $M$, so B finishes it before A begins it. The longest book is read by A during $[0,M]$ and by B during $[S-M,S]$; these intervals are disjoint because $M\le S-M$. Both readers work continuously for $S$ time units, so time $S$ is attainable.

## Algorithm

Read the durations while maintaining their sum `S` and maximum `M`. Output `max(S, 2*M)`.

## Correctness

Every valid schedule lasts at least $S$, since either reader alone must spend $S$ time reading. It also lasts at least $2M$, since the two readings of the longest book are disjoint and each lasts $M$.

When $2M>S$, the dominant-book construction described above completes in $2M$. When $2M\le S$, the shifted-order construction completes in $S$. In both cases a schedule reaches the corresponding lower bound. Hence the minimum completion time is exactly $\max(S,2M)$, which the algorithm outputs.

### Complexity

The algorithm uses $O(n)$ time and $O(1)$ auxiliary space.

## Implementation

Only the sum and maximum matter, so durations need not be stored. `long long` is required because the sum can exceed 32-bit range.

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
	ll S = 0, M = 0;
	for(int i = 0; i < n; i++){
		ll t; cin >> t;
		S += t;
		M = max(M, t);
	}
	cout << max(S, 2*M) << '\n';
	return 0;
}
```

## Worked Example

For durations $2,3,7$, $S=12$ and $2M=14$. During the first seven units, one reader handles the length-7 book while the other finishes the two shorter books. They then exchange, and all reading finishes at time 14.

For $2,3,4$, the bounds are $S=9$ and $2M=8$, so a continuous interleaved schedule finishes at time 9.

## Takeaway

For parallel schedules with an exclusive shared job, compare total workload with the bottleneck created by the largest job. Often these are not merely lower bounds but a complete characterization.

### Related problems

Similar maximum-of-load-and-bottleneck formulas appear in rearranging strings without adjacent equal symbols and in two-processor open-shop scheduling.
