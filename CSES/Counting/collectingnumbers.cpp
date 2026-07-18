#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

ll pw(ll a, ll b) {
    ll r = 1; a %= MOD;
    while (b) {
        if (b & 1) r = r * a % MOD;
        a = a * a % MOD; b >>= 1;
    }
    return r;
}

int n;
vi fc, inv;

ll C(ll a, ll b) {
    if (b < 0 || b > a || a < 0) return 0;
    return fc[a] * inv[b] % MOD * inv[a - b] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;

    fc.assign(n + 1, 1); inv.assign(n + 1, 1);
    for (int i = 1; i <= n; i++) fc[i] = fc[i - 1] * i % MOD;
    inv[n] = pw(fc[n], MOD - 2);
    for (int i = n; i > 0; i--) inv[i - 1] = inv[i] * i % MOD;

    vi dp(n, 0);                               // dp[d] = A(row,d), Eulerian; rounds = d+1
    dp[0] = 1;                                 // row 1
    for (int r = 2; r <= n; r++)               // A(r,d)=(d+1)A(r-1,d)+(r-d)A(r-1,d-1)
        for (int d = r - 1; d >= 0; d--)
            dp[d] = ((ll)(d + 1) * dp[d] + (ll)(r - d) * (d ? dp[d - 1] : 0)) % MOD;

    for (int d = 0; d < n; d++) cout << dp[d] << "\n";
}