#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<int> b(n + 1);
    int maxType = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
        if (b[i] > maxType) maxType = b[i];
    }

    if (b[1] == b[n]) {
        cout << fixed << setprecision(8) << 1.0 << '\n';
        return 0;
    }

    vector<int> next_idx(maxType + 1, 0);
    vector<double> P(n + 1, 0.0);

    next_idx[b[n]] = n;
    double suf = 0.0;

    for (int i = n - 1; i >= 2; --i) {
        int t = b[i];
        if (t == b[1]) {
            P[i] = 1.0;
        } else if (next_idx[t] != 0) {
            P[i] = P[next_idx[t]];
        } else {
            P[i] = (suf + 1.0) / double(n - i + 1);
        }
        next_idx[t] = i;
        suf += P[i];
    }

    double ans = 1.0;
    for (int i = 2; i <= n - 1; ++i) ans += P[i];
    ans /= double(n);

    cout << fixed << setprecision(8) << ans << '\n';
    return 0;
}
