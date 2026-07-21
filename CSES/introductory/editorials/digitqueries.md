# Digit Queries

## Problem

- **Source:** [CSES 2431: Digit Queries](https://cses.fi/problemset/task/2431/)
- **Code:** [`View accepted C++ solution (digitqueries.cpp)`](../digitqueries.cpp)

Find the character at one-based position $k$ in `123456789101112...` for each query.

## Idea

Group integers by digit length. There are $9\cdot10^{d-1}$ positive $d$-digit integers, contributing

$$d\cdot9\cdot10^{d-1}$$

characters. Subtract whole blocks until $k$ lies in the $d$-digit block. Convert to zero-based `idx=k-1`. The containing integer is

$$10^{d-1}+\left\lfloor\frac{idx}{d}\right\rfloor,$$

and the desired digit is at offset $idx\bmod d$ within its decimal representation.

### Procedure

Increase `d` while subtracting complete digit blocks and maintain `s=10^{d-1}`. Compute the containing integer and character offset, convert the integer to a string, and output that character.

Block subtraction removes exactly all digits belonging to shorter integers, leaving the position relative to the correct fixed-width block. Division by $d$ selects the zero-based integer within that block, and remainder modulo $d$ selects its digit. Therefore the algorithm returns the character at the original position.

## Implementation

Block sizes use `__int128` so multiplication cannot overflow before comparison. The conversion to zero-based indexing occurs only after the correct block is found.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll q; cin >> q;
	while(q--){
		ll k; cin >> k;

		ll d = 1; ll s = 1;
		while(true){
			__int128 cnt = 9;
			for(int i = 1; i < d; i++) cnt *= 10;
			__int128 block = cnt * d;
			if((__int128)k > block){
				k -= (long long) block;
				d++;
				s *= 10;
			} else break;
		}
		ll idx = k-1;
		ll add = idx / d;
		ll pos = idx % d;
		ll x = s + add;

		string ss = to_string(x);
		cout << ss[(int)pos] << '\n';
	}
	return 0;
}
```

## Complexity

There are at most 18 decimal-length blocks for 64-bit positions. Each query takes $O(\log k)$ time and $O(\log k)$ temporary string space.

## Example

Position 11 lies after the nine one-digit characters, so its block-relative position is 2. Zero-based index 1 selects integer $10+\lfloor1/2\rfloor=10$ and offset $1$, yielding digit `0`.
