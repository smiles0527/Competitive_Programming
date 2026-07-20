#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, r = 0, b[30] = {};
    cin >> n >> k;

    for (int j = 0; j < n; j++) {
        int x;
        cin >> x;
        for (int i = 29; i >= 0; i--) {
            if (!(x >> i & 1)) continue;
            if (b[i]) x ^= b[i];
            else {
                b[i] = x;
                r++;
                break;
            }
        }
    }

    for (int i = 0; i < 30; i++) {
        if (!b[i]) continue;
        for (int j = i + 1; j < 30; j++) {
            if (b[j] >> i & 1) b[j] ^= b[i];
        }
    }

    vector<int> v;
    for (int i = 0; i < 30; i++) {
        if (b[i]) v.push_back(b[i]);
    }

    long long rep = 1;
    for (int i = r; i < n && rep < k; i++) rep *= 2;
    rep = min<long long>(rep, k);

    int need = (k + rep - 1) / rep;
    int done = 0;

    for (int mask = 0; mask < need; mask++) {
        int x = 0;
        for (int i = 0; i < r; i++) {
            if (mask >> i & 1) x ^= v[i];
        }
        for (int j = 0; j < rep && done < k; j++, done++) {
            if (done) cout << ' ';
            cout << x;
        }
    }

    cout << '\n';
}
