#include <bits/stdc++.h>
using namespace std;

int bad(int x, const vector<int>& pos) {
    if (x < 1 || x + 1 >= (int)pos.size()) return 0;
    return pos[x] > pos[x + 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; cin >> n >> m;

    vector<int> a(n + 1), pos(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }

    int ans = 1;
    for (int x = 1; x < n; x++) ans += bad(x, pos);

    while (m--) {
        int l, r; cin >> l >> r;

        int x = a[l], y = a[r];
        vector<int> v = {x - 1, x, y - 1, y};

        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());

        for (int k : v) ans -= bad(k, pos);

        swap(a[l], a[r]);
        swap(pos[x], pos[y]);

        for (int k : v) ans += bad(k, pos);

        cout << ans << '\n';
    }
}
