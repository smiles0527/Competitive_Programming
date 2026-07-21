#include <bits/stdc++.h>
using namespace std;

int n;
int t[200005];
int ans[200005];
int state[200005]; // 0 unvisited, 1 on current path, 2 done
int ord[200005];   // position on current path

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> t[i];
    for (int i = 1; i <= n; i++) {
        if (state[i]) continue;
        vector<int> path;
        int v = i;
        while (state[v] == 0) {
            state[v] = 1;
            ord[v] = (int)path.size();
            path.push_back(v);
            v = t[v];
        }
        if (state[v] == 1) { // found a fresh cycle
            int start = ord[v];
            int L = (int)path.size() - start;
            for (int j = start; j < (int)path.size(); j++) ans[path[j]] = L;
            for (int j = start; j < (int)path.size(); j++) state[path[j]] = 2;
            for (int j = start - 1; j >= 0; j--) { // tail before cycle
                ans[path[j]] = ans[path[j + 1]] + 1;
                state[path[j]] = 2;
            }
        } else { // ran into a done node
            for (int j = (int)path.size() - 1; j >= 0; j--) {
                ans[path[j]] = ans[t[path[j]]] + 1;
                state[path[j]] = 2;
            }
        }
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << (i == n ? '\n' : ' ');
}
