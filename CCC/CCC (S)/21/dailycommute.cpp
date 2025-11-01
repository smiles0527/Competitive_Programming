#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, W, D;
    cin >> N >> W >> D;
    vector<vector<int>> g(N+1);
    for (int i = 0; i < W; i++) {
        int a, b;
        cin >> a >> b;
        g[b].push_back(a); // reversed edges
    }
    vector<int> dist(N+1, 1e9);
    queue<int> q;
    dist[N] = 0;
    q.push(N);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    vector<int> S(N+1), pos(N+1);
    for (int i = 1; i <= N; i++) {
        cin >> S[i];
        pos[S[i]] = i;
    }

    multiset<long long> ms;
    auto contrib = [&](int v) {
        return 1LL * (pos[v] - 1) + dist[v];
    };
    for (int v = 1; v <= N; v++) {
        ms.insert(contrib(v));
    }

    while (D--) {
        int X, Y;
        cin >> X >> Y;
        int u = S[X], v = S[Y];
        ms.erase(ms.find(contrib(u)));
        ms.erase(ms.find(contrib(v)));
        swap(S[X], S[Y]);
        pos[u] = Y;
        pos[v] = X;
        ms.insert(contrib(u));
        ms.insert(contrib(v));
        cout << *ms.begin() << '\n';
    }
    return 0;
}
