#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    unordered_map<int, int> cnt;
    cnt.reserve(2 * k + 10); cnt.max_load_factor(0.7);
    int l = 0, cur = 0; ll ans = 0;
    for (int r = 0; r < n; r++) {
        if (cnt[a[r]]++ == 0) cur++;
        while (cur > k) {
            if (--cnt[a[l]] == 0) { cnt.erase(a[l]); cur--; }
            l++;
        }
        ans += r - l + 1;
    }
    cout << ans << '\n';
}
