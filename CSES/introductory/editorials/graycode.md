# Gray Code

## Problem

- **Source:** [CSES 2205: Gray Code](https://cses.fi/problemset/task/2205/)
- **Code:** [`View accepted C++ solution (graycode.cpp)`](../graycode.cpp)
- **Limits:** $1\le n\le16$.

Print all $2^n$ binary strings of length $n$ so consecutive strings differ in one bit.

## Construction

The binary-reflected Gray code maps an integer $i$ to

$$g(i)=i\oplus(i\!\gg\!1).$$

Incrementing the integer flips a suffix of its binary representation: the least significant zero bit becomes one, and all trailing one bits become zero. In the XOR with the shifted copy, these changes cancel everywhere except at one position. Thus, $g(i)$ and $g(i+1)$ differ in exactly one bit. The mapping is reversible, so all results are unique.

### Algorithm

For every integer $i$ in the range $0\le i<2^n$, calculate

$$
g=i\oplus(i\gg1),
$$

then output the $n$ bits of $g$ from the most significant bit to the least significant bit.

## Explanation

The Gray transformation is a bijection on the set of $n$-bit integers. Therefore, the algorithm produces every binary string of length $n$ exactly once. The cancellation argument above shows that adjacent outputs have Hamming distance one, so the sequence satisfies the definition of a Gray code.

## Output

The output loop runs from bit $n-1$ down to bit $0$. Printing from the most significant bit to the least significant bit preserves leading zeros, ensuring that every output has length $n$.

## Implementation

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n; cin >> n;

	int limit = 1 << n;
	for(int i = 0; i < limit; i++){
		int g = i ^ (i >> 1);
		for(int b = n-1; b>=0; b--){
			cout << ((g>>b) & 1);
		}
		cout << '\n';
	}
	return 0;
}
```

## Complexity

There are $2^n$ strings and $n$ printed bits per string, giving $O(n2^n)$ time, which matches the output size. Auxiliary space is $O(1)$.

## Example

For $n=2$, integers $0,1,2,3$ map to Gray values $0,1,3,2$, printed as `00`, `01`, `11`, `10`.
