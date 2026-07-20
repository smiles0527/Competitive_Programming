# Two Knights

## Problem

- **Source:** [CSES 1072: Two Knights](https://cses.fi/problemset/task/1072/)
- **Code:** [`View accepted C++ solution (twoknights.cpp)`](./twoknights.cpp)
- **Limits:** $1\le n\le10^4$.

For every $k$ from 1 through $n$, count unordered placements of two knights on a $k\times k$ board such that they do not attack each other.

## Idea

Count all placements, then subtract attacking placements.

There are $k^2$ squares, so the number of unordered pairs of distinct squares is

$$\binom{k^2}{2}=\frac{k^2(k^2-1)}2.$$

Two knights attack exactly when they occupy opposite corners of a $2\times3$ or $3\times2$ rectangle. A $2\times3$ rectangle can be placed in $(k-1)(k-2)$ positions. The rotated orientation contributes the same number. Each such rectangle has two pairs of opposite corners that form a knight move. Hence

$$2\cdot2\cdot(k-1)(k-2)=4(k-1)(k-2)$$

placements are attacking. Each attacking pair determines its bounding $2\times3$ rectangle and is counted once.

### Procedure

For each $k=1,2,\ldots,n$, compute

$$\frac{k^2(k^2-1)}2-4(k-1)(k-2)$$

and print it.

Every placement of two knights is either attacking or nonattacking. The binomial term counts every unordered placement once. The rectangle argument gives a bijection between attacking placements and a choice of rectangle orientation, rectangle position, and one of its two attacking diagonals, so the subtracted term counts every attacking placement once. The difference therefore counts all and only nonattacking placements.

## Implementation

For $k=1$ or $k=2$, the product $(k-1)(k-2)$ is zero, as required. No special case is needed.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n; cin >> n;
	for(ll i=1;i<=n;i++){
		ll total = i*i*(i*i-1)/2;
		ll attack = 4*(i-1)*(i-2);
		cout << total - attack << '\n';
	}

	return 0;
}
```

## Complexity

Each board size takes $O(1)$ work. Total time is $O(n)$ and auxiliary space is $O(1)$. The $k^4$ term requires `long long`.

## Example

For $k=3$, there are $\binom92=36$ total pairs. The board contains two $2\times3$ rectangles and two $3\times2$ rectangles, with two attacking pairs each, for 8 attacking placements. The answer is $36-8=28$.
