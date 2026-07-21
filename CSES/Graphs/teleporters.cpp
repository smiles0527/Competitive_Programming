#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj;
int it_[100005];
int indeg[100005], outdeg[100005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    adj.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        outdeg[a]++;
        indeg[b]++;
    }
    for (int i = 1; i <= n; i++) {
        int d = outdeg[i] - indeg[i];
        if (i == 1) {
            if (d != 1) {
                cout << "IMPOSSIBLE\n";
                return 0;
            }
        } else if (i == n) {
            if (d != -1) {
                cout << "IMPOSSIBLE\n";
                return 0;
            }
        } else if (d != 0) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }
    vector<int> path;
    vector<int> stk;
    stk.push_back(1);
    while (!stk.empty()) {
        int v = stk.back();
        if (it_[v] < (int)adj[v].size()) {
            int u = adj[v][it_[v]++];
            stk.push_back(u);
        } else {
            path.push_back(v);
            stk.pop_back();
        }
    }
    if ((int)path.size() != m + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    } // disconnected
    reverse(path.begin(), path.end());
    if (path.front() != 1 || path.back() != n) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    for (int i = 0; i < (int)path.size(); i++)
        cout << path[i] << (i + 1 == (int)path.size() ? '\n' : ' ');
}
