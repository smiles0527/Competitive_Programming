# Increasing Array

## Problem

- **Source:** [CSES 1094: Increasing Array](https://cses.fi/problemset/task/1094/)
- **Code:** [`View accepted C++ solution (increasingarray.cpp)`](../increasingarray.cpp)
- **Limits:** $1\le n\le2\cdot10^5$, $1\le x_i\le10^9$.

In one move, increase one array element by one. Find the minimum moves needed to make the array nondecreasing.

## Idea

Increases are the only allowed changes. Suppose that we have already constructed a nondecreasing prefix of length $k$, whose last value is $L$. For the next input value $x$ at position $k+1$:

- If $x\ge L$, then it can remain the same at no extra cost.
- If $x<L$, then it must be increased to at least $L$. Going beyond $L$ incurs extra cost and cannot make future restrictions any easier. Thus, the minimum choice is to increase it to exactly $L$, at cost $L-x$.

Feasibility therefore forces this local decision, and increasing the current value beyond the previous value cannot be advantageous. This gives us a greedy procedure that moves from left to right. The variable `previous` stores the last value of the processed prefix, which is not necessarily the latest input value.

### Procedure

Start by reading the first value into `previous`. For each following value `current`:

- If $\texttt{current}<\texttt{previous}$, add $\texttt{previous}-\texttt{current}$ to the total cost. The final value at the current position becomes `previous` implicitly.
- Otherwise, set $\texttt{previous}=\texttt{current}$.

Output the obtained total cost.

After processing position $t$, the algorithm has used the minimum number of operations for the prefix of length $t$. Among all minimum-cost solutions for this prefix, `previous` is the smallest possible value at its last position.

For $t=1$, no operation is needed, so the claim holds. Suppose it holds for a prefix whose last value is $L$. Any valid extension must make the next value at least $L$. The algorithm chooses this lower bound, adding the minimum possible cost $L-\texttt{current}$ when necessary. This choice also leaves the smallest possible lower bound for the remaining suffix. By induction, the claim holds for every prefix. Therefore, after the entire array has been processed, the total cost is minimum.

## Implementation

The array is streamed. When `current < previous`, `previous` does not change because the current element is conceptually raised to that value.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    long long previous;
    cin >> previous;

    long long moves = 0;
    for(int i = 1; i < n; i++){
        long long current;
        cin >> current;
        if(current < previous) moves += previous - current;
        else previous = current;
    }

    cout << moves << '\n';

    return 0;
}
```

## Complexity

The algorithm takes $O(n)$ time and $O(1)$ auxiliary space. The answer may be as large as roughly $(n-1)10^9$, so it uses `long long`.

## Example

For $[3,2,5,1,7]$:

| Input | Required final value | Added moves | Total |
|---:|---:|---:|---:|
| 3 | 3 | 0 | 0 |
| 2 | 3 | 1 | 1 |
| 5 | 5 | 0 | 1 |
| 1 | 5 | 4 | 5 |
| 7 | 7 | 0 | 5 |

The minimum cost is 5.
