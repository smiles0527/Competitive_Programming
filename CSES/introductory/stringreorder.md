# String Reorder

## Problem

- **Source:** [CSES 1743: String Reorder](https://cses.fi/problemset/task/1743/)
- **Code:** [`View accepted C++ solution (stringreorder.cpp)`](./stringreorder.cpp)
- **Limits:** string length at most $10^6$.

Find the lexicographically smallest permutation with no equal adjacent characters.

## Construction

A multiset of length $L$ has an arrangement without equal adjacent letters if and only if its maximum letter frequency is at most $\lceil L/2\rceil$. The lexicographically smallest such arrangement can be found by considering candidate letters in ascending order from `A` and choosing the first letter for which the remaining suffix is still feasible.

In addition to the usual feasibility constraint, the first letter of the suffix must differ from the chosen candidate $x$. If only copies of $x$ remain, no valid continuation exists. When $L$ is odd and

$$
\operatorname{cnt}[x]=\left\lceil\frac L2\right\rceil,
$$

every valid arrangement of the suffix must place $x$ first, which is also forbidden. Together with the maximum-frequency constraint, these checks are necessary and sufficient.

### Algorithm

First check whether the maximum frequency in the original multiset exceeds $\lceil n/2\rceil$. At each output position, consider letters in ascending order, skipping the previously emitted letter. Temporarily decrement the count of the candidate and perform the suffix-feasibility check. Keep the first candidate that passes; if a candidate fails, restore its count and continue to the next letter.

## Explanation

At every position, the algorithm chooses a letter different from the previously emitted letter. The feasibility checks guarantee that the remaining multiset can be completed with a suffix whose first character differs from the selected letter. Therefore, the algorithm never commits to a choice that causes a dead end.

The algorithm also selects the smallest letter that permits some valid completion. If another valid result were lexicographically smaller, then at the first position where the two results differ, it would use a smaller feasible candidate. The ascending scan would have selected that candidate instead, which is a contradiction. Thus, the generated string is valid and lexicographically smallest.

## Implementation

The variable `prev` stores the last emitted letter. A tentative decrement is undone whenever its feasibility test fails. The assignment

$$
\texttt{CH}=\frac{L+1}{2}
$$

uses integer division to compute $\lceil L/2\rceil$.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string s; cin >> s;
	int n = (int)s.size();

	array<int, 26> cnt{};
	for(char ch : s) cnt[ch - 'A']++;

	int mx0 = 0;
	for(int v : cnt) mx0 = max(mx0, v);
	if(mx0 > (n+1)/2){
		cout << -1 << '\n';
		return 0;
	}
	string out; out.reserve(n);
	int prev = -1;

	for(int i = 0; i < n; i++){
		bool ok = false;
		for(int x = 0; x < 26; x++){
			if(x == prev || cnt[x] == 0) continue;
			cnt[x]--;
			int L = n - i - 1;
			bool good = true;
			if(L > 0){
				int cx = cnt[x];
				if(L - cx == 0) good = false;
				int mx = 0;
				for(int v : cnt) mx = max(mx, v);
				int CH = (L + 1) / 2;
				if(mx > CH) good = false;
				if((L&1) && cx == CH) good = false;
			}
			if(good){
				out.push_back(char('A' + x));
				prev = x;
				ok = true;
				break;
			}
			cnt[x]++;
		}
		if(!ok){
			cout << -1 << '\n'; return 0;
		}
	}
	cout << out << '\n';
	return 0;
}
```

## Time Complexity

At each of the $n$ positions, there are at most $26$ candidates, and each feasibility test scans all $26$ counts. The running time is therefore $O(26^2n)$, which is $O(n)$ because the alphabet size is constant. The frequency array uses $O(26)=O(1)$ auxiliary space, while the output string uses $O(n)$ space.

## Example

For counts `A:2, B:1`, choosing `A` first leaves `A:1, B:1`; a suffix can start with `B`, so the choice is feasible and leads to `ABA`. For `A:3, B:1`, the initial maximum exceeds $\lceil4/2\rceil$, so no arrangement exists.
