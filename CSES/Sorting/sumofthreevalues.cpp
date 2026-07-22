#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; ll x; cin >> n >> x;
    vector<pair<ll, int>> a(n);
    for (int i = 0; i < n; i++) { cin >> a[i].first; a[i].second = i + 1; }
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        int l = i + 1, r = n - 1;
        while (l < r) {
            ll sum = a[i].first + a[l].first + a[r].first;
            if (sum == x) {
                cout << a[i].second << ' ' << a[l].second << ' ' << a[r].second << '\n';
                return 0;
            }
            if (sum < x) l++;
            else r--;
        }
    }
    cout << "IMPOSSIBLE\n";
}
