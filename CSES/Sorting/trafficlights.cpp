#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, n; cin >> x >> n;

    set<int> pos = {0, x};
    multiset<int> len = {x};

    for (int i = 0; i < n; i++) {
        int p; cin >> p;

        auto it = pos.upper_bound(p);
        int r = *it;
        int l = *prev(it);

        len.erase(len.find(r - l));
        len.insert(p - l);
        len.insert(r - p);
        pos.insert(p);

        if (i) cout << ' ';
        cout << *len.rbegin();
    }

    cout << '\n';
}
