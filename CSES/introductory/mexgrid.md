# Mex Grid Construction

## Problem

- **Source:** [CSES 3419: Mex Grid Construction](https://cses.fi/problemset/task/3419/)
- **Code:** [`View accepted C++ solution (mexgrid.cpp)`](./mexgrid.cpp)

Construct the prescribed mex grid of size $n\times n$.

## Construction

The construction is the xor table

$$g[i][j]=i\oplus j.$$

In each fixed row, xor with $i$ is a bijection, so all values are distinct; the same holds in each column. The binary structure of xor also satisfies the recursive mex rule: for $z=i\oplus j$, every smaller value can be obtained from a predecessor by changing the highest differing bit, while $z$ itself cannot occur among those predecessors. Thus their mex is $z$.

### Procedure

For every zero-based row $i$ and column $j$, print `i ^ j`.

## Why it works

The xor identity above establishes that each printed cell equals the mex required from its preceding row and column entries. Since the loops cover every grid coordinate once, the whole construction is valid.

## Implementation

The indices are zero-based, matching the values required in the first row and first column.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n; cin >> n;

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(j) cout << ' ';
			cout << (i^j);
		}
		cout << '\n';
	}
	return 0;
}
```

## Complexity

The algorithm performs $n^2$ constant-time xor operations, taking $O(n^2)$ time and $O(1)$ auxiliary space beyond output.

## Example

For $n=4$, the rows are `0 1 2 3`, `1 0 3 2`, `2 3 0 1`, and `3 2 1 0`.
