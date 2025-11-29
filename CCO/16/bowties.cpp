#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;
    vector<long long> x(N), y(N);
    for (int i = 0; i < N; i++) cin >> x[i] >> y[i];

    vector<long long> L(N), R(N), U(N), D(N);
    vector<int> idx(N);
    iota(idx.begin(), idx.end(), 0);

    sort(idx.begin(), idx.end(), [&](int a, int b) {
        if (x[a] != x[b]) return x[a] < x[b];
        return y[a] < y[b];
    });

    int pos = 0;
    while (pos < N) {
        int start = pos;
        long long curx = x[idx[pos]];
        while (pos < N && x[idx[pos]] == curx) pos++;
        int end = pos;
        for (int j = start; j < end; j++) {
            int i0 = idx[j];
            long long below = j - start;
            long long above = end - 1 - j;
            D[i0] = below;
            U[i0] = above;
        }
    }

    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        if (y[a] != y[b]) return y[a] < y[b];
        return x[a] < x[b];
    });

    pos = 0;
    while (pos < N) {
        int start = pos;
        long long cury = y[idx[pos]];
        while (pos < N && y[idx[pos]] == cury) pos++;
        int end = pos;
        for (int j = start; j < end; j++) {
            int i0 = idx[j];
            long long left = j - start;
            long long right = end - 1 - j;
            L[i0] = left;
            R[i0] = right;
        }
    }

    long long ans = 0;
    for (int i = 0; i < N; i++) {
        if (L[i] && R[i] && U[i] && D[i]) {
            __int128 v = 2;
            v *= L[i];
            v *= R[i];
            v *= U[i];
            v *= D[i];
            ans += (long long)v;
        }
    }

    cout << ans << '\n';
    return 0;
}
