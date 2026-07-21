#include <bits/stdc++.h>
using namespace std;

using ii = pair<int, int>;
int n, m;
vector<string> grid;
int md[1000][1000], pd[1000][1000];
char par[1000][1000];
// DURL
int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, 1, -1};
string stepdir = "DURL";

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    grid.resize(n);
    ii A{-1, -1};
    queue<ii> q;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < m; j++) {
            md[i][j] = pd[i][j] = INT_MAX;
            if (grid[i][j] == 'A') A = {i, j};
            if (grid[i][j] == 'M') {
                md[i][j] = 0;
                q.push({i, j});
            }
        }
    }
    while (!q.empty()) {
        ii c = q.front();
        q.pop();
        for (int k = 0; k < 4; k++) {
            int nr = c.first + dr[k], nc = c.second + dc[k];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m || grid[nr][nc] == '#' ||
                md[nr][nc] != INT_MAX)
                continue;
            md[nr][nc] = md[c.first][c.second] + 1;
            q.push({nr, nc});
        }
    }
    q.push(A);
    pd[A.first][A.second] = 0;
    ii g{-1, -1};
    if (md[A.first][A.second] > 0)
        while (!q.empty()) {
            ii c = q.front();
            q.pop();
            if (!c.first || c.first == n - 1 || !c.second || c.second == m - 1) {
                g = c;
                break;
            }
            for (int k = 0; k < 4; k++) {
                int nr = c.first + dr[k], nc = c.second + dc[k];
                if (nr < 0 || nr >= n || nc < 0 || nc >= m || grid[nr][nc] == '#' ||
                    pd[nr][nc] != INT_MAX)
                    continue;
                if (pd[c.first][c.second] + 1 >= md[nr][nc]) continue;
                pd[nr][nc] = pd[c.first][c.second] + 1;
                par[nr][nc] = stepdir[k];
                q.push({nr, nc});
            }
        }
    if (g.first == -1) {
        cout << "NO\n";
        return 0;
    }
    string path;
    int r = g.first, c = g.second;
    while (r != A.first || c != A.second) {
        char ch = par[r][c];
        path.push_back(ch);
        if (ch == 'D')
            r--;
        else if (ch == 'U')
            r++;
        else if (ch == 'R')
            c--;
        else
            c++;
    }
    reverse(path.begin(), path.end());
    cout << "YES\n" << path.size() << '\n' << path << '\n';
}
