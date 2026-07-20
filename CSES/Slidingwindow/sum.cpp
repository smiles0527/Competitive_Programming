#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    ll x, a, b, c;
    cin >> n >> k;
    cin >> x >> a >> b >> c;

    vector<int> v(k);
    ll sum = 0;

    for (int i = 0; i < k; i++) {
        v[i] = x;
        sum += x;
        x = (a * x + b) % c;
    }

    ll ans = sum;

    for (int i = k; i < n; i++) {
        int p = i % k;

        sum -= v[p];
        v[p] = x;
        sum += x;

        ans ^= sum;
        x = (a * x + b) % c;
    }

    cout << ans << '\n';
}