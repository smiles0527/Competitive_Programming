#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; ll x; cin >> n >> x;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    unordered_map<ll, pair<int, int>> sum;
    sum.reserve(n * n); sum.max_load_factor(0.7);
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < j - 1; i++) sum[a[i] + a[j - 1]] = {i, j - 1};
        for (int k = j + 1; k < n; k++) {
            ll need = x - a[j] - a[k];
            auto it = sum.find(need);
            if (it != sum.end()) {
                cout << it->second.first + 1 << ' ' << it->second.second + 1 << ' '
                     << j + 1 << ' ' << k + 1 << '\n';
                return 0;
            }
        }
    }
    cout << "IMPOSSIBLE\n";
}
