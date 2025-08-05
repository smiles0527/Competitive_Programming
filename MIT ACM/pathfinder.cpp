#include <bits/stdc++.h>
using namespace std;

vector<unordered_set<int>> bad(500001);
vector<char> isRow(500001);
int n, m;

bool bfs(int sy, int sx) {
    queue<pair<int, int>> q;
    q.emplace(sy, sx);
    vector<unordered_set<int>> vis(m + 1);
    while (!q.empty()) {
        auto [y, x] = q.front();
        q.pop();
        if (y <= 0 || y > m || x <= 0 || x > n) continue;
        if (!isRow[y] || !bad[y].count(x) || vis[y].count(x)) continue;
        if (x == 1 || y == m) return true;
        vis[y].insert(x);
        q.emplace(y + 1, x);
        q.emplace(y + 1, x + 1);
        q.emplace(y + 1, x - 1);
        q.emplace(y, x - 1);
        q.emplace(y - 1, x);
        q.emplace(y - 1, x - 1);
        q.emplace(y - 1, x + 1);
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int b;
    if (!(cin >> n >> m >> b)) return 0;
    queue<pair<int, int>> seeds;
    while (b--) {
        int y, x;
        cin >> y >> x;
        bad[y].insert(x);
        isRow[y] = 1;
        if (x == n || y == 1) seeds.emplace(y, x);
    }
    while (!seeds.empty()) {
        auto [y, x] = seeds.front();
        seeds.pop();
        if (bfs(y, x)) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    return 0;
}
