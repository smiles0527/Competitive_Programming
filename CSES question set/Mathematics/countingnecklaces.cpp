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
const ll MOD = 1e9 + 7;

ll power(ll a, ll b) {
    a %= MOD; if (a < 0) a += MOD;
    ll r = 1;
    while (b) { if (b & 1) r = r * a % MOD; a = a * a % MOD; b >>= 1; }
    return r;
}

ll phi(ll x) {                      // Euler totient by trial division
    ll res = x;
    for (ll p = 2; p * p <= x; p++) {
        if (x % p == 0) {
            while (x % p == 0) x /= p;
            res -= res / p;
        }
    }
    if (x > 1) res -= res / x;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m; cin >> n >> m;

    ll sum = 0;
    for (ll d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            ll d1 = d, d2 = n / d;
            // contribution for divisor d1: phi(n/d1) * m^{d1}
            sum = (sum + phi(n / d1) % MOD * power(m, d1)) % MOD;
            if (d1 != d2)
                sum = (sum + phi(n / d2) % MOD * power(m, d2)) % MOD;
        }
    }

    ll ans = sum % MOD * power(n % MOD, MOD - 2) % MOD;
    cout << ans << '\n';
    return 0;
}