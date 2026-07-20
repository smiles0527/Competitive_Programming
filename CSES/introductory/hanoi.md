# Tower of Hanoi

## Problem

- **Source:** [CSES 2165: Tower of Hanoi](https://cses.fi/problemset/task/2165/)
- **Code:** [`View accepted C++ solution (hanoi.cpp)`](./hanoi.cpp)
- **Limits:** $1\le n\le16$.

Move $n$ ordered disks from stack 1 to stack 3 without placing a larger disk on a smaller one, using the minimum number of moves.

## Construction

The largest disk cannot move until all $n-1$ smaller disks have moved to the spare stack. It then moves once to the destination, after which the smaller tower must move onto it. Therefore

$$T(n)=2T(n-1)+1,\qquad T(0)=0,$$

which solves to $T(n)=2^n-1$. The recurrence also gives the construction.

### Procedure

To move $n$ disks from `a` to `c` using `b`:

1. Move $n-1$ disks from `a` to `b` using `c`.
2. Move the largest disk from `a` to `c`.
3. Move $n-1$ disks from `b` to `c` using `a`.

## Why it works

Induct on $n$. The empty case needs no moves. For $n>0$, the induction hypothesis makes both recursive transfers valid. Between them, all smaller disks are off the largest disk, so moving it to the empty destination is legal. The final state places the complete ordered tower at the destination. Any solution must perform the same two transfers around the largest disk's move, requiring at least $2T(n-1)+1$ moves. The construction attains this bound and is optimal.

## Implementation

The parameters are source, spare, and destination stacks. The call `solve(n, 1, 2, 3)` matches that order.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve(int n, int a, int b, int c){
	if(!n) return;
	solve(n-1, a, c, b);
	cout << a << ' ' << c << '\n';
	solve(n-1, b, a, c);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n; cin >> n;

	cout << (1LL << n) - 1 << '\n';
	solve(n, 1, 2, 3);
}
```

## Complexity

The algorithm prints $2^n-1$ moves, taking $O(2^n)$ time and $O(n)$ recursion depth.

## Example

For two disks, move the small disk from 1 to 2, the large disk from 1 to 3, then the small disk from 2 to 3. Three moves equal $2^2-1$.
