#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll sum(ll l, ll r) {
    return (l + r) * (r - l + 1) / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        vector<ll> a(n);
        for (ll &x : a) cin >> x;
        sort(a.begin(), a.end());

        auto ok = [&](int B) {
            if (B == n) return true;

            int c = 0;
            int H = n - B;

            for (int i = 0; i + 1 < n; ++i) {
                while (c < B && sum(B - c, B) <= a[i])
                    ++c;

                if (i + 1 - c == H)
                    return true;
            }

            return false;
        };

        int lo = 1, hi = n;

        while (lo < hi) {
            int mid = (lo + hi) >> 1;

            if (ok(mid))
                hi = mid;
            else
                lo = mid + 1;
        }

        cout << min(a.back(), sum(1, lo)) << '\n';
    }
}