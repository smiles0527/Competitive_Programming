# Movie Festival II

## Problem

- **Source:** [CSES 1632: Movie Festival II](https://cses.fi/problemset/task/1632/)
- **Code:** [`View accepted C++ solution (moviefestival2.cpp)`](./moviefestival2.cpp)

Assign movies to at most $k$ viewers so that the total number watched completely is maximized.

## Generalizing the One-Viewer Greedy Rule

Process movies by increasing ending time, as in single-viewer interval scheduling. For a movie starting at $a$, it can follow any viewer whose current ending time is at most $a$. Among those viewers, choose the one with the largest ending time.

This tightest feasible assignment preserves earlier-ending viewers, which are at least as flexible for movies with early starts. If an optimal schedule assigns the current movie to a viewer ending earlier while another feasible viewer ends later, swapping their future roles preserves all compatibility. Therefore the greedy assignment cannot reduce the achievable count.

If no viewer is free, accepting the movie would require more than $k$ simultaneous schedules, so it must be skipped under the maintained earliest-finish processing.

## Algorithm

Sort movies as `(end, start)`. Maintain a multiset of the $k$ viewers' latest ending times, initially all zero. For each movie, find the first ending time greater than its start, step back to the greatest feasible time, replace it with the movie's end, and increment the count. Skip when no feasible ending exists.

## Correctness

Consider movies in ending-time order. Whenever the algorithm accepts a movie, assigning it to the greatest feasible viewer end is safe: compared with any assignment using an earlier end, exchanging the two viewer histories leaves the earlier end available and cannot invalidate a future movie.

If the algorithm rejects a movie, every viewer is occupied past its start. Any schedule agreeing with previous greedy choices therefore cannot accept it. The exchange argument shows some optimum can be transformed to agree with those choices without losing movies. Inductively, after every processed movie an optimum agrees with the greedy state, so the final count is maximum.

### Complexity

Sorting costs $O(n\log n)$ and each multiset operation costs $O(\log k)$. Space is $O(n+k)$.

## Implementation

`upper_bound(a)` locates the first unavailable end, then decrementing selects the largest end at most $a$. Duplicate ending times require a multiset. Initial zeros represent unused viewers because all times are positive.

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
int n, k;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> k;
	vector<ii> mv(n);                            // {end, start}
	for(int i = 0; i < n; i++){
		ll a, b; cin >> a >> b;
		mv[i] = {b, a};
	}
	sort(mv.begin(), mv.end());                  // by end time

	multiset<ll> ends;                           // k members' last-watched end times
	for(int i = 0; i < k; i++) ends.insert(0);

	int cnt = 0;
	for(auto &m : mv){
		ll b = m.f, a = m.s;
		auto it = ends.upper_bound(a);           // first end > start
		if(it == ends.begin()) continue;         // no member free by start
		--it;                                    // largest end <= start
		ends.erase(it);
		ends.insert(b);
		cnt++;
	}
	cout << cnt << '\n';
	return 0;
}
```

## Worked Example

With two viewers and movies $(1,4),(2,3),(3,5),(4,6)$, ending-time order begins with $(2,3)$. It uses one viewer, $(1,4)$ uses the other, and then $(3,5)$ reuses the viewer ending at 3. Finally $(4,6)$ reuses the viewer ending at 4, so all four movies are watched.

## Takeaway

For interval scheduling on several identical resources, sort by completion time and assign each accepted interval to the latest resource state that is still feasible.

## Related Problems

Movie Festival is the one-viewer case. Room Allocation instead must assign every interval and minimize the number of resources.
