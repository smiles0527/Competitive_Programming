#include <bits/stdc++.h>
using namespace std;

using ii = pair<int, int>;
int n, m;
vector<vector<ii>> adj; // {neighbor, edge id}
vector<bool> used;
int it_[100005];
int deg[100005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    adj.resize(n + 1);
    used.assign(m, false);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
        deg[a]++;
        deg[b]++;
    }
    for (int i = 1; i <= n; i++)
        if (deg[i] & 1) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }

    vector<int> circuit;
    vector<int> stk;
    stk.push_back(1);
    while (!stk.empty()) {
        int v = stk.back();
        while (it_[v] < (int)adj[v].size() && used[adj[v][it_[v]].second]) it_[v]++;
        if (it_[v] == (int)adj[v].size()) {
            circuit.push_back(v);
            stk.pop_back();
        } else {
            ii e = adj[v][it_[v]++];
            if (used[e.second]) continue;
            used[e.second] = true;
            stk.push_back(e.first);
        }
    }
    if ((int)circuit.size() != m + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    } // disconnected
    reverse(circuit.begin(), circuit.end());
    for (int i = 0; i < (int)circuit.size(); i++)
        cout << circuit[i] << (i + 1 == (int)circuit.size() ? '\n' : ' ');
}
