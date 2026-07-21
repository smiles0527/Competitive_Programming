# Weird Algorithm

## Problem

- **Source:** [CSES 1068: Weird Algorithm](https://cses.fi/problemset/task/1068/)
- **Code:** [`View accepted C++ solution (weirdalgorithm.cpp)`](../weirdalgorithm.cpp)
- **Limits:** $1\le n\le10^6$.

Starting from $n$, repeatedly apply

$$
n\leftarrow
\begin{cases}
n/2,&n\text{ is even},\\
3n+1,&n\text{ is odd}.
\end{cases}
$$

Print the starting value and every later value through $1$.

## Idea

Output the starting number and then keep applying the parity rule and outputting the resulting number each time. The loop `while (n != 1)` will be immediately stopped as soon as 1 appears.

The input is guaranteed to be inside `int` bounds, but the generated numbers might exceed this limit. Therefore, we use `long long` to represent the current state.

The program assumes that the sequence will eventually reach 1, in compliance with the task statement. It is not a proof of the Collatz conjecture for arbitrary starting numbers.

## Implementation

Checking `n & 1` allows us to check if $n$ is odd. All values are outputted as they are being calculated, so no sequence needs to be stored.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n; cin >> n;
    cout << n << ' ';

    while (n != 1) {
        if (n & 1) n = 3 * n + 1;
        else n /= 2;
        cout << n << ' ';
    }
    return 0;
}
```

## Complexity

Given that the number of generated elements equals $k$, this algorithm works in $O(k)$ time and uses $O(1)$ additional memory. The complexity is provided in terms of $k$ as the process continues until reaching 1 and not based on the number of iterations.
