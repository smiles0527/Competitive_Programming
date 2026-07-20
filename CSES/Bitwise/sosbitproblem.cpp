#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int m = 1 << 20;

    int n;
    cin >> n;

    vector<int> a(n), sub(m), sup(m);
    for (int& x : a) {
        cin >> x;
        sub[x]++;
        sup[x]++;
    }

    for (int b = 1; b < m; b <<= 1) {
        for (int mask = 0; mask < m; mask++) {
            if (mask & b) sub[mask] += sub[mask ^ b];
            else sup[mask] += sup[mask | b];
        }
    }

    for (int x : a) {
        cout << sub[x] << ' ' << sup[x] << ' '
             << n - sub[(m - 1) ^ x] << '\n';
    }
}
