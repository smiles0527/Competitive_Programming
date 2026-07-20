#include <bits/stdc++.h>
using namespace std;

void bal(multiset<int>& l, multiset<int>& r, int t) {
    while ((int)l.size() > t) {
        auto it = prev(l.end());
        r.insert(*it);
        l.erase(it);
    }

    while ((int)l.size() < t) {
        auto it = r.begin();
        l.insert(*it);
        r.erase(it);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    multiset<int> l, r;
    int t = (k + 1) / 2;

    for (int i = 0; i < k; i++) l.insert(a[i]);
    bal(l, r, t);

    cout << *prev(l.end());

    for (int i = k; i < n; i++) {
        int x = a[i - k];

        auto it = l.find(x);
        if (it != l.end()) l.erase(it);
        else r.erase(r.find(x));

        if (l.empty()) {
            if (r.empty() || a[i] <= *r.begin()) l.insert(a[i]);
            else r.insert(a[i]);
        } else if (a[i] <= *prev(l.end())) {
            l.insert(a[i]);
        } else {
            r.insert(a[i]);
        }

        bal(l, r, t);
        cout << ' ' << *prev(l.end());
    }

    cout << '\n';
}
