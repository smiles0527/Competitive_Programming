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
