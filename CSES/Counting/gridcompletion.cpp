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
ll fact(ll x) { return x < 0 ? 0 : fc[x]; }   // guarded for negative residuals

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;

    vector<string> g(n);
    for (auto &r : g) cin >> r;

    vector<char> rA(n), rB(n), cA(n), cB(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (g[i][j] == 'A') { rA[i] = 1; cA[j] = 1; }
            if (g[i][j] == 'B') { rB[i] = 1; cB[j] = 1; }
        }

    int pA = 0, pB = 0, a = 0, a2 = 0;
    for (int i = 0; i < n; i++) { pA += rA[i]; pB += rB[i]; if (!rA[i] && !rB[i]) a++; }
    for (int j = 0; j < n; j++) if (!cA[j] && !cB[j]) a2++;
    int mA = n - pA, mB = n - pB;

    int fA = 0, qf = 0;                       // forbidden-A cells; fixed A's inside B-board
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (g[i][j] == 'B' && !rA[i] && !cA[j]) fA++;
            if (g[i][j] == 'A' && !rB[i] && !cB[j]) qf++;
        }

    fc.assign(n + 1, 1); inv.assign(n + 1, 1);
    for (int i = 1; i <= n; i++) fc[i] = fc[i - 1] * i % MOD;
    inv[n] = pw(fc[n], MOD - 2);
    for (int i = n; i > 0; i--) inv[i - 1] = inv[i] * i % MOD;

    int S = min(a, a2);
    ll ans = 0;
    for (int s = 0; s <= S; s++) {
        ll D = 0;                             // perms of (mA-s) board avoiding fA indep. cells
        for (int j = 0; j <= fA; j++) {
            ll t = C(fA, j) * fact(mA - s - j) % MOD;
            D = (j & 1) ? (D - t + MOD) % MOD : (D + t) % MOD;
        }
        ll G = C(a, s) * C(a2, s) % MOD * fc[s] % MOD * D % MOD;   // sum_sigma binom(qnew,s)
        for (int d = 0; d <= qf; d++) {
            int l = s + d;
            ll t = fact(mB - l) * C(qf, d) % MOD * G % MOD;
            ans = (l & 1) ? (ans - t + MOD) % MOD : (ans + t) % MOD;
        }
    }

    cout << ans % MOD << "\n";
}