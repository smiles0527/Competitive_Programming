#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    ll x, a, b, c;
    cin >> n >> k >> x >> a >> b >> c;

    vector<pair<int, int>> s1, s2;
    int sz = 0, ans = 0;

    for (int i = 0; i < n; i++) {
        int y = x;
        int z = y;
        if (!s1.empty()) z |= s1.back().second;
        s1.push_back({y, z});
        sz++;

        if (sz > k) {
            if (s2.empty()) {
                while (!s1.empty()) {
                    y = s1.back().first;
                    s1.pop_back();

                    z = y;
                    if (!s2.empty()) z |= s2.back().second;
                    s2.push_back({y, z});
                }
            }

            s2.pop_back();
            sz--;
        }

        if (i >= k - 1) {
            int cur = 0;
            if (!s1.empty()) cur |= s1.back().second;
            if (!s2.empty()) cur |= s2.back().second;
            ans ^= cur;
        }

        x = (a * x + b) % c;
    }

    cout << ans << '\n';
}
