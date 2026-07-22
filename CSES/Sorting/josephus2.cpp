#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> bit;
void add(int i, int x) { for (; i <= n; i += i & -i) bit[i] += x; }
int kth(int k) {
    int p = 0;
    for (int step = 1 << 18; step; step >>= 1) {
        int np = p + step;
        if (np <= n && bit[np] < k) { p = np; k -= bit[np]; }
    }
    return p + 1;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    long long k; cin >> n >> k;
    bit.resize(n + 1);
    for (int i = 1; i <= n; i++) add(i, 1);
    long long pos = 0;
    int sz = n;
    for (int removed = 0; removed < n; removed++) {
        pos = (pos + k) % sz;
        int x = kth(pos + 1);
        if (removed) cout << ' ';
        cout << x;
        add(x, -1);
        sz--;
        if (sz) pos %= sz;
    }
    cout << '\n';
}
