#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

vector<int> bit;

void add(int i, int x) {
    for (; i < (int)bit.size(); i += i & -i) {
        bit[i] += x;
        if (bit[i] >= MOD) bit[i] -= MOD;
    }
}

int get(int i) {
    int ans = 0;

    for (; i > 0; i -= i & -i) {
        ans += bit[i];
        if (ans >= MOD) ans -= MOD;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;

    vector<int> a(n), v;
    for (int i = 0; i < n; i++) cin >> a[i];

    v = a;
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    bit.resize(v.size() + 1);

    for (int x : a) {
        int p = lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
        int cur = get(p - 1) + 1;
        if (cur >= MOD) cur -= MOD;
        add(p, cur);
    }

    cout << get(v.size()) << '\n';
}
