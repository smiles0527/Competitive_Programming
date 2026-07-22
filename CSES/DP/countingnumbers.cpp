#include <bits/stdc++.h>
using namespace std;

using ll = long long;

string s;
ll dp[20][11];

ll get(int p, int prev, bool tight) {
    if (p == (int)s.size()) return 1;
    if (!tight && dp[p][prev] != -1) return dp[p][prev];

    int limit = tight ? s[p] - '0' : 9;
    ll ans = 0;

    for (int d = 0; d <= limit; d++) {
        if (prev != 10 && d == prev) continue;

        int next = d;
        if (prev == 10 && d == 0) next = 10;

        ans += get(p + 1, next, tight && d == limit);
    }

    if (!tight) dp[p][prev] = ans;
    return ans;
}

ll calc(ll x) {
    if (x < 0) return 0;

    s = to_string(x);
    memset(dp, -1, sizeof(dp));
    return get(0, 10, true);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll a, b; cin >> a >> b;
    cout << calc(b) - calc(a - 1) << '\n';
}
