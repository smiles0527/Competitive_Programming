# Grid Coloring I

## Problem

- **Source:** [CSES 3311: Grid Coloring I](https://cses.fi/problemset/task/3311/)
- **Code:** [`View accepted C++ solution (gridcoloring1.cpp)`](../gridcoloring1.cpp)
- **Limits:** $1\le n,m\le500$.

Change every cell to a different letter from `A`, `B`, `C`, `D` so adjacent cells have different final letters.

## Construction

Consider the grid as a bipartite graph, where the bipartition is determined by the parity of $i+j$. Assign distinct color palettes to the two parity classes:

- cells with even parity use symbols from $\{\texttt{A},\texttt{B}\}$;
- cells with odd parity use symbols from $\{\texttt{C},\texttt{D}\}$.

Adjacent cells have different parity, so their palettes do not intersect. This guarantees that adjacent cells cannot receive the same output symbol.

For every cell, at least one symbol in its two-symbol palette differs from its original value. Choose such a symbol. This independently guarantees that every cell is changed.

### Procedure

- For even parity, choose `B` if the original symbol is `A`; otherwise, choose `A`.
- For odd parity, choose `D` if the original symbol is `C`; otherwise, choose `C`.

## Why it works

By construction, every output symbol differs from the corresponding input symbol. Any two adjacent cells have different parity, so one output belongs to $\{\texttt{A},\texttt{B}\}$ and the other belongs to $\{\texttt{C},\texttt{D}\}$. Since these palettes are disjoint, the two output symbols are different. Therefore, the entire grid configuration is valid.

## Implementation

The parity expression `(i + j) & 1` assumes zero-indexed cells. However, the checkerboard property is invariant under the particular choice of indexing system.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m; cin >> n >> m;

	vector<string> s(n);
	for(int i = 0; i < n; i++) cin >> s[i];

	vector<string> out(n, string(m, 'A'));

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			char old = s[i][j];
			if(((i+j)&1) == 0){
				out[i][j] = (old == 'A' ? 'B' : 'A');
			} else{
				out[i][j] = (old == 'C' ? 'D' : 'C');
			}
		}
	}
	for(auto &x : out) cout << x << '\n';
	return 0;
}
```

## Complexity

Every cell is processed once, giving $O(nm)$ time and $O(nm)$ output storage.

## Example

Two horizontally adjacent cells have opposite parity. Even an input pair `A C` becomes `B D`, while `B D` becomes `A C`; both cells change and remain different.
