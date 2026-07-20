# Grid Path Description

## Problem

- **Source:** [CSES 1625: Grid Path Description](https://cses.fi/problemset/task/1625/)
- **Code:** [`View accepted C++ solution (gridpathdescription.cpp)`](./gridpathdescription.cpp)

Count Hamiltonian paths on the $7\times7$ grid from the upper-left square to the lower-left square that match a 48-character direction pattern.

## Search strategy

A depth-first search chooses the next unvisited neighbor while respecting any direction imposed by the pattern. The padding scheme marks an exterior boundary as visited, so boundary checks become ordinary occupancy checks.

The primary pruning rule detects a split. If the cells above and below are blocked while the cells to the left and right are open, the unvisited cells become divided into two separate regions. Connecting both regions would require revisiting the current cell, which is forbidden. The symmetric case, where left and right are blocked while above and below are open, is impossible for the same reason. Pruning such states reduces the search space enough to make the computation tractable.

Reaching the target before step $48$ is invalid because some squares are still unvisited. At step $48$, any square other than the target is invalid as well.

### Procedure

Run a depth-first search from grid position $(1,1)$ with step number $0$. At each state, apply the target and split checks, mark the current square, explore either the required direction or all four directions leading to unvisited squares, and finally unmark the square before returning.

## Why it works

The DFS explores only adjacent unvisited squares and respects every direction constraint imposed by the pattern, so every path counted by the algorithm is valid. Every valid path corresponds to one sequence of recursive choices and is therefore explored unless one of its states is pruned.

The early-target and exhausted-step checks reject states that cannot lead to a complete path. The split check rejects only states where the unvisited area has separated into multiple regions, which cannot all be covered by a single nonrevisiting continuation. Therefore, the algorithm never prunes a valid path and counts every valid path exactly once.

## Implementation

Rows and columns $0$ and $8$ form the sentinel border. The current square is unmarked after all of its children have been explored, preserving the backtracking state for future sibling branches.

### Accepted C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
bool vis[9][9];

int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, 1, -1};
char mv[4] = {'D', 'U', 'R', 'L'};

int dfs(int r, int c, int i) {
    if (r == 7 && c == 1) return i == 48;
    if (i == 48) return 0;

    if ((vis[r-1][c] && vis[r+1][c] && !vis[r][c-1] && !vis[r][c+1]) ||
        (vis[r][c-1] && vis[r][c+1] && !vis[r-1][c] && !vis[r+1][c]))
        return 0;

    vis[r][c] = true;
    int ans = 0;

    char want = s[i];
    if (want != '?') {
        int k = 0;
        if (want == 'U') k = 1;
        else if (want == 'R') k = 2;
        else if (want == 'L') k = 3;

        int nr = r + dr[k], nc = c + dc[k];
        if (!vis[nr][nc]) ans = dfs(nr, nc, i + 1);
    } else {
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (!vis[nr][nc]) ans += dfs(nr, nc, i + 1);
        }
    }

    vis[r][c] = false;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            vis[r][c] = (r == 0 || r == 8 || c == 0 || c == 8);
        }
    }

    cout << dfs(1, 1, 0) << "\n";
    return 0;
}
```

## Complexity

A naive upper bound is $O(4^{48})$, but the visited-square and split pruning rules eliminate most states. The recursion depth is at most $49$, and the board contains only $9\times9$ entries. Thus, the auxiliary space is $O(49+9^2)=O(1)$ for this fixed-size grid.

## Example

If a state has visited cells immediately above and below but open cells on both sides, continuing left leaves the right region unreachable and continuing right leaves the left region unreachable. The function returns zero immediately.
