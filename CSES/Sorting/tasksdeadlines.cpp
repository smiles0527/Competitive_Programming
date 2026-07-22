#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
    sort(a.begin(), a.end());
    ll time = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        time += a[i].first;
        ans += a[i].second - time;
    }
    cout << ans << '\n';
}
