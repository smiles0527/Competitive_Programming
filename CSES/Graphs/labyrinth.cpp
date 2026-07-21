#include <bits/stdc++.h>
using namespace std;

using ii = pair<int, int>;

int n, m;
vector<string> grid;
int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, 1, -1};
string stepdir = "DURL";

char par[1000][1000];
bool vis[1000][1000];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    grid.resize(n);

    ii A{-1, -1}, B{-1, -1};
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A') A = {i, j};
            if (grid[i][j] == 'B') B = {i, j};
        }
    }

    queue<ii> q;
    q.push(A);
    vis[A.first][A.second] = true;

    while (!q.empty()) {
        ii cur = q.front();
        q.pop();
        for (int k = 0; k < 4; k++) {
            int nr = cur.first + dr[k];
            int nc = cur.second + dc[k];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if (vis[nr][nc]) continue;
            if (grid[nr][nc] == '#') continue;
            vis[nr][nc] = true;
            par[nr][nc] = stepdir[k];
            q.push({nr, nc});
        }
    }
    if (!vis[B.first][B.second]) {
        cout << "NO\n";
        return 0;
    }

    string path;
    int r = B.first, c = B.second;
    while (!(r == A.first && c == A.second)) {
        char ch = par[r][c];
        path.push_back(ch);
        if (ch == 'D')
            r -= 1;
        else if (ch == 'U')
            r += 1;
        else if (ch == 'R')
            c -= 1;
        else if (ch == 'L')
            c += 1;
    }
    reverse(path.begin(), path.end());

    cout << "YES\n";
    cout << path.size() << '\n';
    cout << path;
}
