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

    string str; cin >> str;
    n = str.size();
    int cnt[26] = {};
    for (char ch : str) cnt[ch - 'a']++;

    fc.assign(n + 1, 1); inv.assign(n + 1, 1);
    for (int i = 1; i <= n; i++) fc[i] = fc[i - 1] * i % MOD;
    inv[n] = pw(fc[n], MOD - 2);
    for (int i = n; i > 0; i--) inv[i - 1] = inv[i] * i % MOD;

    vi cur = {1};                              // P(x) = prod g_i(x), index = total blocks K
    for (int c = 0; c < 26; c++) {
        int ci = cnt[c];
        if (!ci) continue;
        vi g(ci + 1, 0);
        for (int k = 1; k <= ci; k++) {        // (-1)^(ci-k) * C(ci-1,k-1) / k!
            ll v = C(ci - 1, k - 1) * inv[k] % MOD;
            g[k] = ((ci - k) & 1) ? (MOD - v) % MOD : v;
        }
        vi nx(cur.size() + ci, 0);
        for (size_t i = 0; i < cur.size(); i++) {
            if (!cur[i]) continue;
            for (int k = 1; k <= ci; k++)
                nx[i + k] = (nx[i + k] + cur[i] * g[k]) % MOD;
        }
        cur = move(nx);
    }

    ll ans = 0;
    for (size_t K = 0; K < cur.size(); K++)
        ans = (ans + cur[K] * fc[K]) % MOD;

    cout << ans % MOD << "\n";
}