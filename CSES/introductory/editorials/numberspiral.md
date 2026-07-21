# Number Spiral

## Problem

- **Source:** [CSES 1071: Number Spiral](https://cses.fi/problemset/task/1071/)
- **Code:** [`View accepted C++ solution (numberspiral.cpp)`](../numberspiral.cpp)
- **Limits:** $1\le t\le10^5$, $1\le x,y\le10^9$.

For each coordinate $(y,x)$ in the infinite number spiral, output the value stored there.

## Idea

The coordinate belongs to layer

$$k=\max(x,y).$$

All previous layers fit in a $(k-1)\times(k-1)$ square, whose largest value is $(k-1)^2$. The current layer occupies the new bottom row and right column and ends at $k^2$. Its direction alternates with the parity of $k$.

For odd $k$, $k^2$ lies at $(1,k)$. Moving downward on column $k$ decreases values, while the bottom row starts after $(k-1)^2$ and increases with $x$:

$$
v=
\begin{cases}
k^2-y+1,&x=k,\\
(k-1)^2+x,&x<k.
\end{cases}
$$

For even $k$, the orientation is transposed:

$$
v=
\begin{cases}
k^2-x+1,&y=k,\\
(k-1)^2+y,&y<k.
\end{cases}
$$

### Procedure

For each query, compute $k=\max(x,y)$. Select the odd-layer or even-layer formula, then select the row or column branch according to which coordinate equals $k$.

Every coordinate lies on exactly one layer $k=\max(x,y)$, because at least one coordinate is $k$ and neither exceeds it. The four formulas enumerate the new row or column of that layer from its known endpoint $(k-1)^2+1$ or $k^2$, respecting the layer's parity-dependent direction. Therefore the selected formula returns the unique spiral value at $(y,x)$.

## Implementation

The conditions match the geometry exactly. On an odd layer, the code first tests the right column with `x == k`. On an even layer, it first tests the bottom row with `y == k`.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t; cin >> t;
    while(t--){
        ll y, x; cin >> y >> x;
        ll k = max(y, x), v;
        if(k & 1){                       // odd layer
            if(x == k) v = k*k - y + 1;
            else       v = (k-1)*(k-1) + x;
        } else {                         // even layer
            if(y == k) v = k*k - x + 1;
            else       v = (k-1)*(k-1) + y;
        }
        cout << v << "\n";
    }

	return 0;
}
```

## Complexity

Each query uses constant time and space. Total time is $O(t)$ and auxiliary space is $O(1)$. Since $k^2$ can reach $10^{18}$, every coordinate product uses `long long`.

## Example

For $(y,x)=(4,2)$, $k=4$ is even and $y=k$. The answer is $4^2-2+1=15$. For $(2,3)$, $k=3$ is odd and $x=k$, giving $3^2-2+1=8$.
