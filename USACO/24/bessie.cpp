#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    vector<long long> p(11, 1);
    for (int i = 1; i <= 10; i++) p[i] = p[i - 1] * 10;

    vector<long long> g(11, 0), pre(11, 0);
    for (int L = 2; L <= 10; L++) {
        int k = L - 1;
        long long t = (k == 1) ? 5 : 4 * ((p[k] - 10) / 9) + 5;
        g[L] = p[L - 1] - t;
        if (g[L] < 0) g[L] = 0;
        pre[L] = pre[L - 1] + g[L]; 
    }

    while (T--) {
        long long n;
        cin >> n;
        if (n < 10) {
            cout << 0 << "\n";
            continue;
        }   

        int L = 1;
        while (L <= 10 && p[L] <= n) L++;
        long long ans = pre[L - 1];

        int k = L - 1;
        long long t = (k == 1) ? 5 : 4 * ((p[k] - 10) / 9) + 5;
        long long a = 4 * p[L - 1] + t;
        long long b = 5 * p[L - 1] - 1;

        if (n >= a) ans += min(n, b) - a + 1;
        cout << ans << "\n";
    }
    return 0;
}
