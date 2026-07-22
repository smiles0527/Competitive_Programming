#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; ll x; cin >> n >> x;
    unordered_map<ll, int> cnt;
    cnt.reserve(2 * n); cnt.max_load_factor(0.7);
    cnt[0] = 1;
    ll sum = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        ll y; cin >> y;
        sum += y;
        auto it = cnt.find(sum - x);
        if (it != cnt.end()) ans += it->second;
        cnt[sum]++;
    }
    cout << ans << '\n';
}
