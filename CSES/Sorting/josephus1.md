# Josephus Problem I

## Problem

- **Source:** [CSES 2162: Josephus Problem I](https://cses.fi/problemset/task/2162/)
- **Code:** [`View accepted C++ solution (josephus1.cpp)`](./josephus1.cpp)

Children $1,2,\ldots,n$ stand in a circle. Repeatedly skip one remaining child and remove the next. Output the removal order.

## Representing the Circle

A queue represents the circle with its front as the current position. Skipping the front child is exactly a rotation: move that child to the back. The next front is then the child to remove. After removal, the new front is already the next position around the circle.

Unlike the general Josephus problem, the fixed skip count of one makes direct queue simulation linear because each removal performs only a constant number of queue operations.

## Algorithm

Initialize a queue with 1 through $n$. While it is nonempty, move the front to the back, then remove and record the new front. Print the recorded order.

## Correctness

Before every iteration, the queue lists all surviving children in circular order beginning at the next child to consider. Moving the front to the back skips exactly that child while preserving circular order. Removing the next front therefore removes exactly the required child. The following front is the successor of the removed child, restoring the invariant.

Each iteration removes one distinct child, so after $n$ iterations the recorded sequence is exactly the complete Josephus removal order.

### Complexity

There are $O(1)$ queue operations per child, giving $O(n)$ time and $O(n)$ space.

## Implementation

The code stores output before printing, although it could stream results. The queue is never empty between the rotation and removal because an iteration begins with at least one child, and rotating a one-element queue leaves that element present.

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
	queue<int> q;
	for(int i = 1; i <= n; i++) q.push(i);
	vector<int> out;
	out.reserve(n);
	while(!q.empty()){
		q.push(q.front()); q.pop();              // skip one
		out.pb(q.front()); q.pop();              // remove next
	}
	for(int i = 0; i < n; i++) cout << out[i] << (i+1 == n ? '\n' : ' ');
	return 0;
}
```

## Worked Example

For $n=5$, the queue evolves as follows: skip 1 and remove 2; skip 3 and remove 4; skip 5 and remove 1; skip 3 and remove 5; remove 3. The order is $2,4,1,5,3$.

## Takeaway

A circular process can often be linearized by choosing the queue front as the current cursor and representing movement as rotation.

### Related problems

Josephus Problem II needs order-statistic selection because the skip count may be large.
