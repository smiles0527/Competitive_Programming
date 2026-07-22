# Tasks and Deadlines

## Problem

- **Source:** [CSES 1630: Tasks and Deadlines](https://cses.fi/problemset/task/1630/)
- **Code:** [`View accepted C++ solution (tasksdeadlines.cpp)`](./tasksdeadlines.cpp)

Each task has duration $a_i$ and deadline $d_i$. All tasks must be processed sequentially. If task $i$ finishes at time $f_i$, maximize total reward $\sum_i(d_i-f_i)$.

## Remove the Constant Part

The deadlines contribute the fixed quantity $\sum_i d_i$, independent of task order. Maximizing reward is therefore equivalent to minimizing the sum of completion times $\sum_i f_i$.

Consider two adjacent tasks with durations $a$ and $b$, beginning after an accumulated time $T$. In order $a,b$, their completion-time contribution is

$$
(T+a)+(T+a+b)=2T+2a+b.
$$

In order $b,a$, it is $2T+2b+a$. The first order is no worse exactly when $a\le b$. Thus every adjacent inversion of durations can be exchanged without worsening the objective. Repeated exchanges lead to nondecreasing duration order.

## Algorithm

Sort tasks by duration. Scan them in that order, maintaining elapsed time. Add `deadline - elapsed` after completing each task.

## Correctness

If a schedule contains adjacent tasks with durations $a>b$, exchanging them changes only their two completion times and decreases their sum by $a-b>0$. Deadlines do not affect this comparison because their total contribution is fixed.

Repeatedly removing such inversions transforms any optimal schedule into nondecreasing duration order without reducing reward. The algorithm uses exactly that order and computes each task's reward from its true finishing time, so its total reward is maximum.

### Complexity

Sorting takes $O(n\log n)$ time, the scan takes $O(n)$ time, and the task array uses $O(n)$ space.

## Implementation

Pairs are stored as `(duration, deadline)`, so default sorting uses the correct primary key. Equal durations may appear in either order. Finishing times and total reward require `long long`, and the answer may be negative.

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
	vector<ii> task(n);                          // {duration, deadline}
	for(int i = 0; i < n; i++){
		ll a, d; cin >> a >> d;
		task[i] = {a, d};
	}
	sort(task.begin(), task.end());              // ascending duration
	ll t = 0, reward = 0;
	for(auto &tk : task){
		t += tk.f;                               // finishing time after this task
		reward += tk.s - t;                      // d - f
	}
	cout << reward << '\n';
	return 0;
}
```

## Worked Example

For tasks $(3,10),(1,5),(2,8)$, duration order is $(1,5),(2,8),(3,10)$. Completion times are 1, 3, and 6, giving reward $4+5+4=13$. Placing duration 3 before duration 1 increases early completion-time cost and produces a smaller total reward.

## Takeaway

When an ordering objective is a sum over completion times, compare two adjacent jobs. The exchange calculation often reveals the correct sorting key.

### Related problems

Weighted completion-time variants lead to Smith's ratio rule rather than sorting by duration alone.
