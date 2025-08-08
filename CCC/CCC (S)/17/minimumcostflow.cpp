#include <bits/stdc++.h>
using namespace std;

vector<int> parent, sz;

int root(int v) {
    return parent[v] == v ? v : parent[v] = root(parent[v]);
}

bool isConnected(int a, int b) {
    return root(a) == root(b);
}

void unite(int a, int b) {
    int ra = root(a), rb = root(b);
    if (sz[ra] < sz[rb]) {
        parent[ra] = rb;
        sz[rb] += sz[ra];
    } else {
        parent[rb] = ra;
        sz[ra] += sz[rb];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long N, M, D;
    cin >> N >> M >> D;

    set<tuple<long long,int,int,int>> pipes;
    for (int i = 0; i < M; ++i) {
        long long w;
        int u, v;
        cin >> u >> v >> w;
        pipes.insert(make_tuple(w, i, u, v));
    }

    parent.resize(N+1);
    sz.assign(N+1, 1);
    for (int i = 1; i <= N; ++i) parent[i] = i;

    int used = 0, replaceCount = 0;
    tuple<long long,int,int,int> maxPipe{-1, -1, -1, -1};

    for (const auto& pipe : pipes) {
        if (used == N - 1) break;
        auto [w, idx, u, v] = pipe;
        if (!isConnected(u, v)) {
            unite(u, v);
            ++used;
            if (idx >= N - 1) ++replaceCount;
            maxPipe = pipe;
        }
    }

    parent.clear();
    sz.clear();
    parent.resize(N+1);
    sz.assign(N+1, 1);
    for (int i = 1; i <= N; ++i) parent[i] = i;

    for (const auto& pipe : pipes) {
        auto [w, idx, u, v] = pipe;
        if (!isConnected(u, v)) {
            if (w < get<0>(maxPipe) || (w == get<0>(maxPipe) && idx < N - 1)) {
                unite(u, v);
            } else if (w <= D && idx < N - 1) {
                --replaceCount;
                break;
            }
        }
    }

    cout << replaceCount;
    return 0;
}
