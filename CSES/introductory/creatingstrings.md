# Creating Strings

## Problem

- **Source:** [CSES 1622: Creating Strings](https://cses.fi/problemset/task/1622/)
- **Code:** [`View accepted C++ solution (creatingstrings.cpp)`](./creatingstrings.cpp)
- **Limits:** string length at most 8.

Print every distinct permutation of the input string in lexicographic order.

## Construction

Starting from the sorted string and repeatedly calling `next_permutation` enumerates permutations in strictly increasing lexicographic order. With repeated characters, swapping equal occurrences does not create a new string, and `next_permutation` advances to the next distinct value sequence. Thus duplicates do not appear.

The maximum length is 8, so at most $8!=40320$ strings are generated. Storing them lets the program print the count before the list, as required.

### Procedure

Sort the string. Append the current string to the answer, then advance with `next_permutation` until no larger permutation exists. Print the number of stored strings and the strings in order.

## Why it works

The sorted string is the lexicographically smallest permutation. Each call produces the smallest permutation larger than the current one. Therefore no permutation is skipped and none is repeated. Termination occurs at the largest permutation, so the stored list contains every distinct permutation exactly once and in the required order.

## Implementation

The `do` loop is necessary because the sorted starting permutation must be included even when it is the only one.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string n; cin >> n;

	sort(n.begin(), n.end());

	vector<string> ans;
	do ans.push_back(n);
	while(next_permutation(n.begin(), n.end()));

	cout << ans.size() << '\n';
	for(auto &x : ans) cout << x << '\n';
	return 0;
}
```

## Complexity

If there are $P$ distinct permutations of length $n$, generation and storage take $O(Pn)$ time and space.

## Example

For `AAB`, sorting gives `AAB`. Successive permutations are `ABA` and `BAA`; the next call then fails. The output count is 3.
