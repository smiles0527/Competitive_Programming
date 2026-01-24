#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> graph, cycle, vis, on_stack;

bool dfs(int cur) {
    vis[cur] = on_stack[cur] = true;
    int adj = graph[cur];
    if (on_stack[adj]) {
        on_stack[adj] = false;
        on_stack[cur] = false;
        cycle.push_back(cur);
        return true;
    } else if (!vis[adj]) {
        if (dfs(adj)) {
            if (on_stack[cur]) {
                on_stack[cur] = false;
                cycle.push_back(cur);
                return true;
            } else {
                cycle.push_back(cur);
                return false;
            }
        }
    }
    on_stack[cur] = false;
    return false;
}

signed main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> cnt(n + 1, 0);
    graph.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> graph[i];
        cnt[graph[i]]++;
    }
    vis.resize(n + 1, 0);
    on_stack.resize(n + 1, 0);
    dfs(1);
    vector<int> on_cycle(n + 1, 0);
    for (auto& room : cycle) on_cycle[room] = true;
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        if (!cnt[i]) {
            int pos = i, dist = 0;
            while (!on_cycle[pos]) {
                dist++;
                pos = graph[pos];
            }
            mx = max(mx, dist);
        }
    }
    cout << 2 * mx + 2 * (cycle.size() - 1);
    return 0;
}