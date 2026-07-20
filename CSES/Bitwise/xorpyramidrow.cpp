#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int d = n - k, m = n;
    for (int q = 1; q <= d; q <<= 1) {
        if (!(d & q)) continue;
        for (int i = 0; i + q < m; i++) a[i] ^= a[i + q];
        m -= q;
    }

    for (int i = 0; i < k; i++) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
}
