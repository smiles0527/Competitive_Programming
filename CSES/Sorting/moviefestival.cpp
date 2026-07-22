#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;

    vector<pair<int, int>> a(n);

    for (int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        a[i] = {r, l};
    }

    sort(a.begin(), a.end());

    int last = 0, ans = 0;

    for (int i = 0; i < n; i++) {
        int r = a[i].first;
        int l = a[i].second;

        if (l >= last) {
            ans++;
            last = r;
        }
    }

    cout << ans << '\n';
}
