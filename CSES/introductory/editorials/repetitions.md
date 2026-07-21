# Repetitions

## Problem

- **Source:** [CSES 1069: Repetitions](https://cses.fi/problemset/task/1069/)
- **Code:** [`View accepted C++ solution (repetitions.cpp)`](../repetitions.cpp)
- **Limits:** $1\le n\le10^6$.

Given a DNA string, find the maximum length of a contiguous block containing one repeated character.

## Idea

Scan from left to right while storing the length of the current equal-character run and the longest run seen so far. A matching next character extends the current run; a different character resets it to one.

Define `cl` as the length of the run ending at the current position and `ml` as the longest run seen anywhere in the processed prefix. The recurrence is

$$
cl_i=
\begin{cases}
cl_{i-1}+1,&s_i=s_{i-1},\\
1,&s_i\ne s_{i-1}.
\end{cases}
$$

Then update $ml=\max(ml,cl_i)$.

## Implementation

The input is guaranteed nonempty, so initializing both counters to one is valid. The loop compares `str[i]` with `str[i+1]`; stopping at `length()-2` keeps the second index in bounds.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string str; cin >> str;
    int ml = 1; int cl = 1;
    for(int i = 0; i < str.length() - 1; i++){
        if(str[i + 1] == str[i]) cl++;
        else cl = 1;
        if(cl > ml) ml = cl;
    }
    cout << ml;

    return 0;
}
```

## Complexity

The algorithm takes $O(n)$ time. Apart from the input string, it uses $O(1)$ space.
