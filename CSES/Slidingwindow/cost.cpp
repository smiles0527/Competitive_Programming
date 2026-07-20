#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void bal(multiset<int>& l, multiset<int>& r, ll& sl, ll& sr, int t) {
    while ((int)l.size() > t) {
        auto it = prev(l.end());
        int x = *it;
        l.erase(it);
        sl -= x;
        r.insert(x);
        sr += x;
    }

    while ((int)l.size() < t) {
        auto it = r.begin();
        int x = *it;
        r.erase(it);
        sr -= x;
        l.insert(x);
        sl += x;
    }
}

ll get(const multiset<int>& l, const multiset<int>& r, ll sl, ll sr) {
    ll m = *prev(l.end());
    return m * l.size() - sl + sr - m * r.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    multiset<int> l, r;
    ll sl = 0, sr = 0;
    int t = (k + 1) / 2;

    for (int i = 0; i < k; i++) {
        l.insert(a[i]);
        sl += a[i];
    }

    bal(l, r, sl, sr, t);
    cout << get(l, r, sl, sr);

    for (int i = k; i < n; i++) {
        int x = a[i - k], y = a[i];

        auto it = l.find(x);
        if (it != l.end()) {
            l.erase(it);
            sl -= x;
        } else {
            r.erase(r.find(x));
            sr -= x;
        }

        if (l.empty()) {
            if (r.empty() || y <= *r.begin()) {
                l.insert(y);
                sl += y;
            } else {
                r.insert(y);
                sr += y;
            }
        } else if (y <= *prev(l.end())) {
            l.insert(y);
            sl += y;
        } else {
            r.insert(y);
            sr += y;
        }

        bal(l, r, sl, sr, t);
        cout << ' ' << get(l, r, sl, sr);
    }

    cout << '\n';
}
