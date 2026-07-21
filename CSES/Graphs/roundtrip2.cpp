#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj;
int col[100005]; // 0 white, 1 gray, 2 black
int par[100005];
int cs = -1, ce = -1;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    adj.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }
    for (int st = 1; st <= n && cs == -1; st++) {
        if (col[st]) continue;
        vector<pair<int, int>> stk; // {node, edge index}
        stk.push_back({st, 0});
        col[st] = 1;
        while (!stk.empty()) {
            int v = stk.back().first;
            int& i = stk.back().second;
            if (i < (int)adj[v].size()) {
                int to = adj[v][i++];
                if (col[to] == 0) {
                    col[to] = 1;
                    par[to] = v;
                    stk.push_back({to, 0});
                } else if (col[to] == 1) {
                    cs = to;
                    ce = v;
                    break;
                }
            } else {
                col[v] = 2;
                stk.pop_back();
            }
        }
    }
    if (cs == -1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    vector<int> cyc;
    for (int v = ce; v != cs; v = par[v]) cyc.push_back(v);
    cyc.push_back(cs);
    reverse(cyc.begin(), cyc.end());
    cyc.push_back(cs);
    cout << cyc.size() << '\n';
    for (int i = 0; i < (int)cyc.size(); i++)
        cout << cyc[i] << (i + 1 == (int)cyc.size() ? '\n' : ' ');
}
