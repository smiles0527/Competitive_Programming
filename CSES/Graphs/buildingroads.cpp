#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj;
bool vis[100005];
vector<int> rep;

void dfs(int v) {
    vector<int> st = {v};
    vis[v] = true;
    while (!st.empty()) {
        int cur = st.back();
        st.pop_back();
        for (int to : adj[cur]) {
            if (!vis[to]) {
                vis[to] = true;
                st.push_back(to);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    adj.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            rep.push_back(i);
            dfs(i);
        }
    }
    cout << rep.size() - 1 << '\n';

    for (int i = 1; i < (int)rep.size(); i++) {
        cout << rep[i - 1] << ' ' << rep[i] << '\n';
    }
}
