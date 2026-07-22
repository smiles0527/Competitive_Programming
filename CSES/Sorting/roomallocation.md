# Room Allocation

## Problem

- **Source:** [CSES 1164: Room Allocation](https://cses.fi/problemset/task/1164/)
- **Code:** [`View accepted C++ solution (roomallocation.cpp)`](./roomallocation.cpp)

Assign every customer's inclusive stay interval to a room, minimizing the number of rooms, and output an assignment in input order.

## Processing Customers Chronologically

Process customers by arrival time. A previously used room is reusable only if its customer departs strictly before the new arrival, because equal departure and arrival days still overlap.

Among occupied rooms, only the earliest departure matters. If it is before the arrival, that room can be reused. If it is not, every other active room departs no earlier, so a new room is forced. A min-priority queue exposes this earliest departure.

## Algorithm

Sort customers as `(arrival, departure, original index)`. Maintain a min-heap of `(departure, room id)`. Reuse the top room when its departure is less than the current arrival; otherwise create a new id. Store each assignment by original index.

## Correctness

Every reuse is valid because the former departure is strictly before the new arrival. New rooms are also valid, so the output assignment has no overlapping customers in one room.

When the algorithm creates a room for arrival $a$, the smallest active departure is at least $a$. Therefore all currently allocated rooms are occupied on day $a$, and the new customer overlaps one customer in each of them. Any valid assignment needs one additional room at that moment. Every room creation is thus forced, so the final room count is minimum.

### Complexity

Sorting and heap operations take $O(n\log n)$ time. The heap, customer array, and assignment array use $O(n)$ space.

## Implementation

The comparison is `departure < arrival`, not `<=`, because stays include both endpoints. Original indices restore output order. The heap stores room ids together with departure times so a freed room can be named immediately.

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
	vector<array<int,3>> c(n);                   // {arrival, departure, idx}
	for(int i = 0; i < n; i++){
		int a, b; cin >> a >> b;
		c[i] = {a, b, i};
	}
	sort(c.begin(), c.end());                    // by arrival

	priority_queue<ii, vii, greater<ii>> pq;     // {departure, room id}
	vector<int> room(n);
	int k = 0;
	for(auto &cust : c){
		int a = cust[0], b = cust[1], idx = cust[2];
		if(!pq.empty() && pq.top().f < a){       // earliest room frees before arrival
			int rid = pq.top().s; pq.pop();
			room[idx] = rid;
			pq.push({b, rid});
		} else {
			k++;
			room[idx] = k;
			pq.push({b, k});
		}
	}
	cout << k << '\n';
	for(int i = 0; i < n; i++) cout << room[i] << (i+1 == n ? '\n' : ' ');
	return 0;
}
```

## Worked Example

For stays $(1,2),(2,4),(4,4),(5,7)$, the second customer cannot reuse the first room because day 2 overlaps. The third cannot reuse the room ending on day 4, but can reuse the one ending on day 2. The fourth can reuse a room ending on day 4. Two rooms suffice.

## Takeaway

For assigning all intervals to the fewest resources, sort by starts and track the earliest resource release. Creating a resource is optimal precisely when all existing ones are provably occupied.

### Related problems

Movie Festival selects a maximum compatible subset, while Room Allocation must keep every interval.
