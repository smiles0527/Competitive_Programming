#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n), b;
    for (int i = 0; i < n; i++) cin >> a[i];

    b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());

    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    }

    vector<int> cnt(b.size());
    set<pair<int, int>> s;

    for (int i = 0; i < k; i++) {
        int x = a[i];
        s.erase({-cnt[x], x});
        s.insert({-++cnt[x], x});
    }

    cout << b[s.begin()->second];

    for (int i = k; i < n; i++) {
        int x = a[i - k], y = a[i];

        if (x != y) {
            s.erase({-cnt[x], x});
            if (--cnt[x]) s.insert({-cnt[x], x});

            s.erase({-cnt[y], y});
            s.insert({-++cnt[y], y});
        }

        cout << ' ' << b[s.begin()->second];
    }

    cout << '\n';
}
