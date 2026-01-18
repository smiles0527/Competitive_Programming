#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    const ull BASE = 1315423911ULL;

    while (T--) {
        string s;
        cin >> s;
        int n = (int)s.size();

        vector<ull> H(n + 1), P(n + 1);
        H[0] = 0;
        P[0] = 1;
        for (int i = 0; i < n; ++i) {
            H[i + 1] = H[i] * BASE + (ull)(s[i] - 'a' + 1);
            P[i + 1] = P[i] * BASE;
        }

        auto getHash = [&](int l, int r) -> ull {
            return H[r] - H[l] * P[r - l];
        };

        int L = 0, R = n;
        int ans = 0;

        while (L < R) {
            int len = R - L;
            int half = len / 2;
            int b = 0;
            for (int k = 1; k <= half; ++k) {
                if (getHash(L, L + k) == getHash(R - k, R)) {
                    b = k;
                    break;
                }
            }
            if (b == 0) {
                ++ans;
                break;
            }
            ans += 2;
            L += b;
            R -= b;
        }

        cout << ans << '\n';
    }

    return 0;
}
