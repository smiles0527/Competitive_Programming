
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N, K; cin >> N >> K;

    int M = 1 << N;
    vector<long long> a(M, 0);

    for (int i = 0; i < K; i++) {
        int x, y, z; cin >> x >> y >> z;
        x--; y--; z--;

        int mx = 1 << x;
        int mxy = mx | (1 << y);
        int mxz = mx | (1 << z);
        int mxyz = mxy | (1 << z);

        a[mx] += 1;
        a[mxy] -= 1;
        a[mxz] -= 1;
        a[mxyz] += 1;
    }

    for (int b = 0; b < N; b++) {
        for (int mask = 0; mask < M; mask++) {
            if (mask & (1 << b)) a[mask] += a[mask ^ (1 << b)];
        }
    }

    long long best = a[0], cnt = 0;
    for (int mask = 0; mask < M; mask++) best = max(best, a[mask]);
    for (int mask = 0; mask < M; mask++) if (a[mask] == best) cnt++;

    cout << best << " " << cnt << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}
