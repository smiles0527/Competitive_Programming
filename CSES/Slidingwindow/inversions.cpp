#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int bit[200005], m;

void add(int i, int v) {
    for (i++; i <= m; i += i & -i) bit[i] += v;
}

int sum(int i) {
    int s = 0;
    for (i++; i; i -= i & -i) s += bit[i];
    return s;
}

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

    m = b.size();
    ll cur = 0;

    for (int i = 0; i < k; i++) {
        cur += i - sum(a[i]);
        add(a[i], 1);
    }

    cout << cur;

    for (int i = k; i < n; i++) {
        int x = a[i - k], y = a[i];

        cur -= sum(x - 1);
        add(x, -1);

        cur += k - 1 - sum(y);
        add(y, 1);

        cout << ' ' << cur;
    }

    cout << '\n';
}
