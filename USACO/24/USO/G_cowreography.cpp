#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    string s, t;
    cin >> n >> k >> s >> t;

    map<int, int> q;
    ll ans = 0;

    for (int i = 0; i < n; ++i) {
        while (!q.empty() && q.begin()->first < i) {
            auto [x, c] = *q.begin();
            q.erase(q.begin());
            q[x + k] += c;
            ans += abs((ll)c);

            if (q[x + k] == 0)
                q.erase(x + k);
        }

        int d = s[i] - t[i];
        if (!d) continue;

        if (!q.empty() && 1LL * q.begin()->second * d < 0) {
            auto it = q.begin();
            it->second += d;
            if (it->second == 0)
                q.erase(it);
        } else {
            q[i] += d;
        }
    }

    cout << ans << '\n';
    return 0;
}