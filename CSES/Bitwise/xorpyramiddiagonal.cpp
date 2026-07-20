#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int m = 1;
    while (m < n) m <<= 1;

    vector<int> a(m);
    for (int i = 0; i < n; i++) cin >> a[i];

    for (int b = 1; b < m; b <<= 1) {
        for (int mask = 0; mask < m; mask++) {
            if (mask & b) a[mask] ^= a[mask ^ b];
        }
    }

    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
}
