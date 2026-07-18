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

    vi Cn(n + 1);                              // C_m = 2^(m choose 2) = all tournaments
    for (int m = 0; m <= n; m++) Cn[m] = pw(2, (ll)m * (m - 1) / 2);

    vi sc(n + 1, 0);                           // strongly connected tournaments, labeled
    for (int m = 1; m <= n; m++) {
        ll v = Cn[m];
        for (int j = 1; j < m; j++)            // s_m = C_m - sum C(m,j) C_j s_{m-j}
            v = (v - C(m, j) * Cn[j] % MOD * sc[m - j]) % MOD;
        sc[m] = (v % MOD + MOD) % MOD;
    }

    vi a(n + 1, 0);                            // EGF coeffs a_m = s_m / m!
    for (int m = 1; m <= n; m++) a[m] = sc[m] * inv[m] % MOD;

    vi cur = a;                                // cur = S^k, start k=1
    int lo = 1;
    cout << fc[n] * cur[n] % MOD << "\n";       // T(n,1)
    for (int k = 2; k <= n; k++) {
        vi nx(n + 1, 0);
        lo++;                                  // S^k supported from degree k
        for (int i = lo - 1; i <= n; i++) {
            if (!cur[i]) continue;
            for (int j = 1; j + i <= n; j++)
                nx[i + j] = (nx[i + j] + cur[i] * a[j]) % MOD;
        }
        cur = move(nx);
        cout << fc[n] * cur[n] % MOD << "\n";
    }
}