#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj, radj;
bool vis[200005];
int comp[200005];
vector<int> order_;
int lit(int x, int val) {
    return 2 * x + (val ? 0 : 1);
} // val=1 true node, 0 false node

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    int V = 2 * (m + 1);
    adj.assign(V, {});
    radj.assign(V, {});
    auto add = [&](int u, int v) {
        adj[u].push_back(v);
        radj[v].push_back(u);
    };
    for (int i = 0; i < n; i++) {
        char c1, c2;
        int a, b;
        cin >> c1 >> a >> c2 >> b;
        int la = lit(a, c1 == '+'), lb = lit(b, c2 == '+'); // the literals that satisfy
        add(la ^ 1, lb);                                    // !la -> lb
        add(lb ^ 1, la);                                    // !lb -> la
    }
    for (int st = 0; st < V; st++) {
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
    for (int i = 1; i <= m; i++)
        if (comp[2 * i] == comp[2 * i + 1]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    string res(m, '-');
    for (int i = 1; i <= m; i++)
        res[i - 1] = (comp[2 * i] > comp[2 * i + 1]) ? '+' : '-'; // true node topologically later
    cout << res << '\n';
}
