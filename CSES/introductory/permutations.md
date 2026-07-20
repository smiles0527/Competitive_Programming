# Permutations

## Problem

- **Source:** [CSES 1070: Permutations](https://cses.fi/problemset/task/1070/)
- **Code:** [`View accepted C++ solution (permutations.cpp)`](./permutations.cpp)
- **Limits:** $1\le n\le10^6$.

Construct a permutation of $1,2,\ldots,n$ in which adjacent values never differ by one, or report that none exists.

## Construction

Consecutive integers have different parities. Numbers with the same parity differ by at least two. Therefore, a sequence that groups all even numbers together and all odd numbers together is valid within both subsequences. The only part left to verify is the boundary between them.

The algorithm produces the sequence

$$2,4,6,\ldots,\quad1,3,5,\ldots.$$

For $n\ge4$, the last even number is at least $4$, while the first odd number is $1$. Their difference is therefore at least $3$, so the boundary between the two subsequences is valid as well.

The small cases must be considered separately. For $n=1$, there is exactly one permutation. For $n=2$, both possible permutations place $1$ and $2$ next to each other. For $n=3$, the number $2$ must be adjacent to either $1$ or $3$ in every permutation. Thus, no solution exists for $n=2$ or $n=3$.

### Procedure

If $n=2$ or $n=3$, print `NO SOLUTION`. If $n=1$, print $1$. Otherwise, print all even numbers in ascending order, followed by all odd numbers in ascending order.

## Explanation

For $n=1$, the generated sequence is beautiful. The argument above shows that solutions are impossible for $n=2$ and $n=3$.

Now consider the general case $n\ge4$. Every integer from $1$ to $n$ occurs exactly once in one of the two parity subsequences, so the result is a permutation. Adjacent numbers within either subsequence differ by $2$. At the only boundary between the even and odd subsequences, the last even number is at least $4$ and the first odd number is $1$, so their difference is at least $3$. Since no adjacent numbers differ by $1$, the generated permutation is beautiful.

## Implementation

The first loop starts at 2 and advances by 2. The second starts at 1. The conditional separator on the odd loop avoids relying on a trailing space for the final value.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n; cin >> n;
	if(n==1){ cout << 1; return 0;}
	if(n==3 || n ==2){cout << "NO SOLUTION"; return 0;}

	for(int i=2;i<=n;i+=2) cout << i << ' ';
	for(int i=1;i<=n;i+=2) cout << i << (i + 2 <= n ? ' ': '\n');

	return 0;
}
```

## Complexity

The output itself contains $n$ values. The algorithm takes $O(n)$ time and $O(1)$ auxiliary space.

## Example

For $n=5$, the construction prints $2,4,1,3,5$. Its adjacent differences are $2,3,2,2$, all greater than one.
