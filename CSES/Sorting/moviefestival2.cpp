#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int l, r; cin >> l >> r; a[i] = {r, l};
    }
    sort(a.begin(), a.end());
    multiset<int> end;
    for (int i = 0; i < k; i++) end.insert(0);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int r = a[i].first, l = a[i].second;
        auto it = end.upper_bound(l);
        if (it == end.begin()) continue;
        --it; end.erase(it); end.insert(r); ans++;
    }
    cout << ans << '\n';
}
