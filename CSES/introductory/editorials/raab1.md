# Raab Game I

## Problem

- **Source:** [CSES 3399: Raab Game I](https://cses.fi/problemset/task/3399/)
- **Code:** [`View accepted C++ solution (raab1.cpp)`](../raab1.cpp)
- **Limits:** $1\le t\le1000$, $1\le n\le100$.

Construct two permutations of $1,\ldots,n$ whose pairwise comparisons give scores $a$ and $b$.

## Construction

There must be $a+b$ nontied rounds, so $a+b\le n$. If at least one player scores, both players must score: comparing two permutations, the sums of all card differences is zero, so positive differences cannot exist without negative differences.

Let $m=a+b$. Keep the first permutation as $1,2,\ldots,n$. On the first $m$ positions, rotate the second permutation left by $a$. The first $b=m-a$ comparisons make the second card larger, while the last $a$ wraparound comparisons make the first card larger. Values above $m$ remain aligned and tie.

### Procedure

Reject if $m>n$ or exactly one of $a,b$ is zero while $m>0$. Otherwise print the identity permutation and the described rotation on $1,\ldots,m$, followed by aligned values $m+1,\ldots,n$.

## Why it works

The construction uses every card once in each row. In the nonwrapped part of the rotation, player two wins $b$ rounds. In the wrapped part, player one wins $a$ rounds. Every remaining aligned position ties. Thus the scores are correct. The rejection conditions are necessary by the count of rounds and the zero-sum difference argument.

## Implementation

The expression `((i-1+a)%m)+1` performs the cyclic shift using one-based card labels.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T; cin >> T;
    while(T--){
        int n,a,b; cin >> n >> a >> b;
        int m=a+b, t=n-m;
        if(t<0 || (m>0 && (a==0||b==0))){ cout<<"NO\n"; continue; }
        cout<<"YES\n";
        for(int i=1;i<=n;i++) cout<<i<<" \n"[i==n];   // A: 1..n
        for(int i=1;i<=m;i++) cout<<((i-1+a)%m)+1<<' ';// B contested: shift by a
        for(int v=m+1;v<=n;v++) cout<<v<<" \n"[v==n];  // B ties: m+1..n
        if(m==n) cout<<"\n";                            // no tie block printed newline
    }

	return 0;
}
```

## Complexity

Each test prints $2n$ values and takes $O(n)$ time with $O(1)$ auxiliary space.

## Example

For $n=4,a=1,b=2$, $m=3$. The rows `1 2 3 4` and `2 3 1 4` give player two two wins, player one one win, and one tie.
