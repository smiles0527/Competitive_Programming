#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;

    vector<pair<int, int>> e;
    e.reserve(2 * n);

    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        e.push_back({a, 1});
        e.push_back({b, -1});
    }

    sort(e.begin(), e.end());

    int cur = 0, ans = 0;

    for (int i = 0; i < 2 * n; i++) {
        cur += e[i].second;
        ans = max(ans, cur);
    }

    cout << ans << '\n';
}
