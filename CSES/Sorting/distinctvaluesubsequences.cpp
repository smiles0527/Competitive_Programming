#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    ll ans = 1;
    for (int i = 0; i < n; ) {
        int j = i + 1;
        while (j < n && a[j] == a[i]) j++;
        ans = ans * (j - i + 1) % MOD;
        i = j;
    }
    ans = (ans - 1 + MOD) % MOD;
    cout << ans << '\n';
}
