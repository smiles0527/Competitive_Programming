#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj, radj;
bool vis[100005];
int comp[100005];
vector<int> order_;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    adj.resize(n + 1);
    radj.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        radj[b].push_back(a);
    }
    for (int st = 1; st <= n; st++) {
        if (vis[st]) continue;
        vector<pair<int, int>> stk;
        stk.push_back({st, 0});
        vis[st] = true;
        while (!stk.empty()) {
            int v = stk.back().first;
            int& i = stk.back().second;
            if (i < (int)adj[v].size()) {
                int to = adj[v][i++];
                if (!vis[to]) {
                    vis[to] = true;
                    stk.push_back({to, 0});
                }
            } else {
                order_.push_back(v);
                stk.pop_back();
            }
        }
    }
    int k = 0;
    for (int idx = (int)order_.size() - 1; idx >= 0; idx--) {
        int st = order_[idx];
        if (comp[st]) continue;
        k++;
        vector<int> stk;
        stk.push_back(st);
        comp[st] = k;
        while (!stk.empty()) {
            int v = stk.back();
            stk.pop_back();
            for (int to : radj[v])
                if (!comp[to]) {
                    comp[to] = k;
                    stk.push_back(to);
                }
        }
    }
    cout << k << '\n';
    for (int i = 1; i <= n; i++) cout << comp[i] << (i == n ? '\n' : ' ');
}
