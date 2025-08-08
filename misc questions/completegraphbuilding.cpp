#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int findRoot(int x, vector<int>& p) {
    return p[x] == x ? x : p[x] = findRoot(p[x], p);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<tuple<int64,int,int>> edges(N-1);
    for (int i = 0; i < N-1; ++i) {
        int u, v;
        int64 w;
        cin >> u >> v >> w;
        edges[i] = {w, u, v};
    }
    sort(edges.begin(), edges.end(),
         [](auto& a, auto& b){ return get<0>(a) < get<0>(b); });

    vector<int> parent(N+1), sz(N+1,1);
    for (int i = 1; i <= N; ++i) parent[i] = i;

    __int128 S = 0;
    for (auto& e : edges) {
        int64 w;
        int u, v;
        tie(w, u, v) = e;
        int ru = findRoot(u, parent);
        int rv = findRoot(v, parent);
        __int128 pairs = (__int128)sz[ru] * sz[rv];
        S += pairs * w;
        parent[rv] = ru;
        sz[ru] += sz[rv];
    }

    __int128 add = (__int128)(N-1)*(N-2)/2;
    __int128 ans = S + add;

    if (ans == 0) {
        cout << '0';
    } else {
        string out;
        while (ans > 0) {
            out.push_back(char('0' + ans % 10));
            ans /= 10;
        }
        reverse(out.begin(), out.end());
        cout << out;
    }
    return 0;
}
