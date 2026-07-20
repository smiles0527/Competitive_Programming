# Coin Piles

## Problem

- **Source:** [CSES 1754: Coin Piles](https://cses.fi/problemset/task/1754/)
- **Code:** [`View accepted C++ solution (coinpiles.cpp)`](./coinpiles.cpp)
- **Limits:** $1\le t\le10^5$, $0\le a,b\le10^9$.

Each move removes $(1,2)$ or $(2,1)$ coins from the two piles. Determine whether both piles can be emptied.

## Idea

Let $x$ be the number of moves removing two coins from the first pile and $y$ the number removing two from the second. Emptying both piles requires

$$2x+y=a,\qquad x+2y=b.$$

Solving gives

$$x=\frac{2a-b}{3},\qquad y=\frac{2b-a}{3}.$$

Thus a solution exists exactly when $a+b$ is divisible by 3 and both numerators are nonnegative. The latter condition is equivalent to

$$\max(a,b)\le2\min(a,b).$$

These conditions are also sufficient because they make $x$ and $y$ nonnegative integers.

### Procedure

For each test, print `YES` if $(a+b)\bmod3=0$ and the larger pile is at most twice the smaller pile. Otherwise print `NO`.

Every move removes three coins, so divisibility by three is necessary. A move removes at most twice as many coins from one pile as from the other, which gives the balance condition. Conversely, if both tests hold, the formulas for $x$ and $y$ above are nonnegative integers and describe a valid sequence of moves. The algorithm therefore accepts exactly the feasible instances.

## Implementation

The balance test uses `max` and `min`, avoiding separate cases for which pile is larger.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--){
        int a, b; cin >> a >> b;
        if((a+b)%3==0 && max(a,b) <= 2*min(a,b))
            cout << "YES\n";
        else cout <<"NO\n";
    }

    return 0;
}
```

## Complexity

Each test uses $O(1)$ time and space, for $O(t)$ total time.

## Example

For $(a,b)=(2,1)$, the sum is 3 and $2\le2\cdot1$, so one $(2,1)$ move succeeds. For $(2,2)$, the sum is not divisible by 3, so no sequence exists.
