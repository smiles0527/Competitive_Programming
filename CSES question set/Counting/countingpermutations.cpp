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

    ll ans = 0;
    for (int k = 0; k < n; k++) {
        ll g = 1;
        if (k) {                           // g(k) = sum_c 2^c * C(k-1,c-1) * C(n-k,c)
            g = 0;
            ll p2 = 2;
            for (int c = 1; c <= k; c++) {
                g = (g + p2 * C(k - 1, c - 1) % MOD * C(n - k, c)) % MOD;
                p2 = p2 * 2 % MOD;
            }
        }
        ll t = fc[n - k] * g % MOD;
        ans = (k & 1) ? (ans - t + MOD) % MOD : (ans + t) % MOD;
    }

    cout << ans % MOD << "\n";
}