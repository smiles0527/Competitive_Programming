#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<long long> p(N+1);
    for (int i = 1; i <= N; ++i) cin >> p[i];

    vector<vector<long long>> w(N+1, vector<long long>(N+1));
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            cin >> w[i][j];

    vector<bool> used(N+1, false);
    vector<long long> dist(N+1, LLONG_MAX);
    for (int i = 1; i <= N; ++i)
        dist[i] = p[i];

    long long answer = 0;
    for (int iter = 0; iter < N; ++iter) {
        int u = 0;
        long long best = LLONG_MAX;
        for (int i = 1; i <= N; ++i)
            if (!used[i] && dist[i] < best) {
                best = dist[i];
                u = i;
            }
        used[u] = true;
        answer += best;
        for (int v = 1; v <= N; ++v)
            if (!used[v] && w[u][v] < dist[v])
                dist[v] = w[u][v];
    }

    cout << answer;
    return 0;
}
