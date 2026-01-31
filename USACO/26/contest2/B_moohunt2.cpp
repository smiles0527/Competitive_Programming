#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N, K; cin >> N >> K;

    int M = 1 << N;

    vector<int> x(K), y(K), z(K);
    
    for (int i = 0; i < K; i++) {
        cin >> x[i] >> y[i] >> z[i];
        x[i]--; y[i]--; z[i]--;
    }

    long long best = -1, cnt = 0;

    for (int mask = 0; mask < M; mask++) {
        long long a = 0;
        for (int i = 0; i < K; i++) {
            int mx = (mask >> x[i]) & 1;
            int my = (mask >> y[i]) & 1;
            int mz = (mask >> z[i]) & 1;
            a += (mx == 1 && my == 0 && mz == 0);
        }
        if (a > best) {
            best = a;
            cnt = 1;
        } else if (a == best) {
            cnt++;
        }
    }

    cout << best << " " << cnt << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}

