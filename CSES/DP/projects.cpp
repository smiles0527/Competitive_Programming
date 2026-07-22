#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Project {
    ll a, b, p;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;

    vector<Project> v(n);
    for (int i = 0; i < n; i++) cin >> v[i].a >> v[i].b >> v[i].p;

    sort(v.begin(), v.end(), [](const Project& x, const Project& y) {
        return x.b < y.b;
    });

    vector<ll> ends(n), dp(n + 1);
    for (int i = 0; i < n; i++) ends[i] = v[i].b;

    for (int i = 0; i < n; i++) {
        int j = lower_bound(ends.begin(), ends.begin() + i, v[i].a) - ends.begin();
        dp[i + 1] = max(dp[i], dp[j] + v[i].p);
    }

    cout << dp[n] << '\n';
}
