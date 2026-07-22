#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<ll> cnt(n); cnt[0] = 1;
    ll sum = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        sum = (sum + x) % n;
        if (sum < 0) sum += n;
        ans += cnt[sum];
        cnt[sum]++;
    }
    cout << ans << '\n';
}
