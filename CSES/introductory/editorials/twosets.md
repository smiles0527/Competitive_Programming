# Two Sets

## Problem

- **Source:** [CSES 1092: Two Sets](https://cses.fi/problemset/task/1092/)
- **Code:** [`View accepted C++ solution (twosets.cpp)`](../twosets.cpp)
- **Limits:** $1\le n\le10^6$.

Partition $\{1,2,\ldots,n\}$ into two sets with equal sums, or report that no partition exists.

## Construction

The total sum is

$$
S=\frac{n(n+1)}2.
$$

An odd total sum cannot be split equally. The value of $S$ is even if and only if $n\equiv0\pmod4$ or $n\equiv3\pmod4$.

These two residue classes also admit direct constructions.

For $n\equiv0\pmod4$, split each block

$$\{a,a+1,a+2,a+3\}$$

as $\{a,a+3\}$ and $\{a+1,a+2\}$. Both pairs sum to $2a+3$.

For $n\equiv3\pmod4$, begin with $A=\{1,2\}$ and $B=\{3\}$, which both have sum $3$. The remaining values start from $4$ and form complete four-element blocks. Split every block using the same equal-pair principle.

### Algorithm

Print `NO` if $S$ is odd. If $n\equiv0\pmod4$, split blocks starting from $1$. Otherwise, place the three special values first and split blocks starting from $4$. Finally, print the two constructed sets.

## Reasoning

If the total sum is odd, two integer set sums cannot both equal half of it, so rejection is correct.

For an accepted case, each number belongs to exactly one block and is placed in exactly one set. In every four-element block, the selected pairs have equal sums. In the $n\equiv3\pmod4$ case, the initial selections also have equal sums. Adding equal contributions to the two sets preserves their equality. Therefore, the sets partition the entire range and have equal sums.

## Implementation

The odd-total check uses `long long`. In the second construction branch, feasibility guarantees $n\equiv3\pmod4$. After processing $1$, $2$, and $3$, the loop beginning at $4$ therefore splits only complete blocks.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n; cin >> n;
	if(n*(n+1)/2 %2){
		cout << "NO";
		return 0;
	}

	vector<int> A, B;

	if(n%4==0){
		for(int a=1;a<=n;a+=4){
			A.push_back(a);
			A.push_back(a+3);
			B.push_back(a+1);
			B.push_back(a+2);
		}
	} else{
		A = {1, 2}; B = {3};
		for(int i=4;i<=n;i+=4){
			A.push_back(i);
			A.push_back(i+3);
			B.push_back(i+1);
			B.push_back(i+2);
		}
	}

	cout << "YES\n";
	cout << A.size() << '\n';
	for(int x : A) cout << x << ' ';
	cout << '\n';
	cout << B.size() << '\n';
	for(int x : B) cout << x << ' ';


	return 0;
}
```

## Complexity

The construction takes $O(n)$ time and $O(n)$ space for the two output vectors. Since output itself contains $n$ integers, linear time is necessary.

## Example

For $n=7$, initialize $A=\{1,2\}$ and $B=\{3\}$. Split $\{4,5,6,7\}$ into $\{4,7\}$ and $\{5,6\}$. The final sums are $1+2+4+7=14$ and $3+5+6=14$.
