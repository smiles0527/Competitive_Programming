# Chessboard and Queens

## Problem

- **Source:** [CSES 1624: Chessboard and Queens](https://cses.fi/problemset/task/1624/)
- **Code:** [`View accepted C++ solution (chessboardqueens.cpp)`](../chessboardqueens.cpp)

Count placements of eight nonattacking queens on free squares of an $8\times8$ board.

## Search strategy

Every valid placement contains exactly one queen in each row and exactly one queen in each column. We choose the queen's column one row at a time. A square $(r,c)$ is attacked by a previously placed queen if any of its three indices is already occupied:

- its column $c$,
- its diagonal $r+c$,
- its other diagonal $r-c+7$.

These three indices fully describe every possible threat from queens in earlier rows. After evaluating a particular placement, all three marks must be cleared before the next column is considered.

### Procedure

Run a backtracking search on the next row. For every free and unattacked column, place a queen by marking its column and diagonal indices, make a recursive call, and then clear all three marks. Reaching row $8$ produces one complete solution.

## Justification

The recursion places one queen in every processed row and rejects all blocked squares, column conflicts, and diagonal conflicts. Therefore, every placement it counts is valid.

Now consider any valid solution. The queen in the current row passes every test because it occupies a free square and conflicts with none of the previously placed queens. The recursion can therefore follow all eight choices belonging to this solution and will eventually count it. Different sequences of column choices produce different placements, so every valid placement is counted exactly once.

## Implementation

The second diagonal index adds 7 so values from $r-c\in[-7,7]$ map into $[0,14]$.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
char g[8][9];
bool col[8], d1[15], d2[15];        // d1: r+c, d2: r-c+7
int ans = 0;

void solve(int r){
    if(r==8){ ans++; return; }
    for(int c=0;c<8;c++){
        if(g[r][c]=='*' || col[c] || d1[r+c] || d2[r-c+7]) continue;
        col[c]=d1[r+c]=d2[r-c+7]=1;
        solve(r+1);
        col[c]=d1[r+c]=d2[r-c+7]=0;
    }
}

int main(){
    for(int i=0;i<8;i++) cin >> g[i];
    solve(0);
    cout << ans << "\n";
}
```

## Complexity

Ignoring pruning, at most $8!$ column permutations are explored, with constant work per node. The state arrays use $O(1)$ space and recursion depth 8.

## Example

After placing a queen at $(0,2)$, column 2, diagonal index 2, and diagonal index 5 are blocked. The next row skips any square sharing one of those indices.
