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

    // --- old O(n^3) power-by-power convolution (TLE at n=5000) ---
    // vi cm(n + 1, 0);                           // connected funcgraphs: c_m=(m-1)! sum_{i<m} m^i/i!
    // for (int m = 1; m <= n; m++) {
    //     ll s = 0, p = 1;                       // p = m^i
    //     for (int i = 0; i < m; i++) {
    //         s = (s + p * inv[i]) % MOD;
    //         p = p * m % MOD;
    //     }
    //     cm[m] = s * fc[m - 1] % MOD;
    // }
    //
    // vi a(n + 1, 0);                            // EGF coeffs a_m = c_m / m!
    // for (int m = 1; m <= n; m++) a[m] = cm[m] * inv[m] % MOD;
    //
    // vi cur = a;                                // cur = C^k, start k=1
    // int lo = 1;
    // cout << fc[n] * inv[1] % MOD * cur[n] % MOD << "\n";
    // for (int k = 2; k <= n; k++) {
    //     vi nx(n + 1, 0);
    //     lo++;
    //     for (int i = lo - 1; i <= n; i++) {
    //         if (!cur[i]) continue;
    //         for (int j = 1; j + i <= n; j++)
    //             nx[i + j] = (nx[i + j] + cur[i] * a[j]) % MOD;
    //     }
    //     cur = move(nx);
    //     cout << fc[n] * inv[k] % MOD * cur[n] % MOD << "\n";
    // }

    // Lagrange inversion on T=x e^T (tree fn) with S1 = unsigned Stirling 1st kind:
    //   F(n,k) = (n-1)! * sum_{r>=k} n^{n-r} / ((n-r)!(r-1)!) * S1[r][k]
    vi np(n + 1, 1);                           // np[b] = n^b
    for (int b = 1; b <= n; b++) np[b] = np[b - 1] * (ll)n % MOD;

    vi ans(n + 1, 0), row(n + 2, 0);
    row[1] = 1;                                // S1[1][1] = 1
    for (int r = 1; r <= n; r++) {
        ll w = fc[n - 1] * np[n - r] % MOD * inv[n - r] % MOD * inv[r - 1] % MOD;
        for (int k = 1; k <= r; k++)
            ans[k] = (ans[k] + w * row[k]) % MOD;
        if (r < n)                             // S1[r+1][k] = r*S1[r][k] + S1[r][k-1]
            for (int k = r + 1; k >= 1; k--)
                row[k] = ((ll)r * row[k] + row[k - 1]) % MOD;
    }

    for (int k = 1; k <= n; k++) cout << ans[k] << "\n";
}