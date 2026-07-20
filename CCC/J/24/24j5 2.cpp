#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int MOD = 1e9+7;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int R, C;
    cin >> R >> C;
    vector<string> g(R);
    for (auto& row : g) cin >> row;
    int sr, sc;
    cin >> sr >> sc;       

    auto val = [](char c) -> int {
        if (c == 'S') return 1;
        if (c == 'M') return 5;
        if (c == 'L') return 10;
        return 0;
    };

    vector<vector<char>> vis(R, vector<char>(C, 0));
    long long total = 0;
    int dr[] = {1,-1,0,0}, dc[] = {0,0,1,-1};

    queue<pair<int,int>> q;
    if (g[sr][sc] != '*') {
        vis[sr][sc] = 1;
        q.push({sr, sc});
    }
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        total += val(g[r][c]);
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if (vis[nr][nc] || g[nr][nc] == '*') continue;
            vis[nr][nc] = 1;
            q.push({nr, nc});
        }
    }

    cout << total << '\n';
    return 0;
}