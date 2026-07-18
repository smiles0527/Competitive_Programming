#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int MOD = 1e9+7;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<ll> a(n), b(n);
    for (auto& v : a) cin >> v;
    for (auto& v : b) cin >> v;

    vector<ll> P(n);
    ll pref = 0;
    for (int i = 0; i < n; i++) {
        pref += a[i] - b[i];
        P[i] = pref;
    }

    sort(P.begin(), P.end());
    ll k = P[n / 2];   // median

    ll ans = 0;
    for (int i = 0; i < n; i++) ans += llabs(P[i] - k);

    cout << ans << '\n';
    return 0;
}