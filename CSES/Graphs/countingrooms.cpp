#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<string> grid;

bool vis[1000][1000];

int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, 1, -1};

void dfs(int r, int c) {
    vector<pair<int, int>> st;
    st.push_back({r, c});
    vis[r][c] = true;
    while (!st.empty()) {
        auto [cr, cc] = st.back();
        st.pop_back();
        for (int k = 0; k < 4; k++) {
            int nr = cr + dr[k];
            int nc = cc + dc[k];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if (vis[nr][nc] || grid[nr][nc] == '#') continue;
            vis[nr][nc] = true;
            st.push_back({nr, nc});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    grid.resize(n);
    for (int i = 0; i < n; i++) cin >> grid[i];

    int rooms = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.' && !vis[i][j]) {
                dfs(i, j);
                rooms++;
            }
        }
    }
    cout << rooms << '\n';
}
