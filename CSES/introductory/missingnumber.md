# Missing Number

## Problem

- **Source:** [CSES 1083: Missing Number](https://cses.fi/problemset/task/1083/)
- **Code:** [`View accepted C++ solution (missingnumber.cpp)`](./missingnumber.cpp)
- **Limits:** $2\le n\le2\cdot10^5$.

The input contains $n-1$ distinct values from $1$ through $n$. Find the one value that is absent.

## Idea

The complete set has a known sum:

$$1+2+\cdots+n=\frac{n(n+1)}2.$$

If the missing value is $m$, the sum of the input is the complete sum minus $m$. Rearranging gives

$$m=\frac{n(n+1)}2-\sum x_i.$$

Compute this total, subtract every supplied number, and output what remains.

## Implementation

The multiplication in `n*(n+1)/2` is performed in 64-bit arithmetic because `n` is declared as `ll`. The input values are accumulated as they are read; no array is allocated.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n; cin >> n;

    long  long sum = 0;
    for(int i = 0; i < n - 1; i++){
        long long x = 0; cin >> x;
        sum += x;
    }
    cout << n*(n+1)/2 - sum;


    return 0;
}
```

## Complexity

The scan takes $O(n)$ time and uses $O(1)$ auxiliary space. For $n=2\cdot10^5$, the complete sum is about $2\cdot10^{10}$, so 32-bit `int` is insufficient. The implementation stores the sum and $n$ in `long long`.
