#include <bits/stdc++.h>
using namespace std;

pair<int, int> getrng(const vector<int>& a) {
    int n = (int)a.size();
    int lo = 0;

    for (int i = 0; i < n; i += 2) {
        if (a[i + 1] - a[i] > 1) return {-1, -1};
        lo += a[i] != a[i + 1];
    }

    vector<pair<int, int>> r;
    for (int x : a) {
        if (!r.empty() && r.back().first == x) {
            ++r.back().second;
        } else {
            r.push_back({x, 1});
        }
    }

    int hi = 0;

    for (int i = 0; i + 1 < (int)r.size(); ++i) {
        if (r[i + 1].first != r[i].first + 1) continue;

        int d = min(r[i].second, r[i + 1].second);
        if ((r[i].second - d) & 1) --d;

        r[i].second -= d;
        r[i + 1].second -= d;
        hi += d;
    }

    return {lo, hi};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        vector<int> x(n), y(n);
        for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];

        sort(x.begin(), x.end());
        sort(y.begin(), y.end());

        auto rx = getrng(x);
        auto ry = getrng(y);

        if (rx.first == -1 || ry.first == -1) {
            cout << "NO\n";
            continue;
        }

        int m = n / 2;
        int lo = rx.first + ry.first;
        int hi = rx.second + ry.second;

        bool ok = lo <= m && m <= hi && ((m - lo) % 2 == 0);
        cout << (ok ? "YES\n" : "NO\n");
    }
}