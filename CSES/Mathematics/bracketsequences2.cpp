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
const int V = 1000000;
ll fact[V + 1], invfact[V + 1];

ll power(ll a, ll b) {
    a %= MOD; ll r = 1;
    while (b) { if (b & 1) r = r * a % MOD; a = a * a % MOD; b >>= 1; }
    return r;
}
ll C(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invfact[r] % MOD * invfact[n-r] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fact[0] = 1;
    for (int i = 1; i <= V; i++) fact[i] = fact[i-1] * i % MOD;
    invfact[V] = power(fact[V], MOD - 2);
    for (int i = V; i >= 1; i--) invfact[i-1] = invfact[i] * i % MOD;

    int n; cin >> n;
    string p; cin >> p;
    int k = p.size();

    // validate prefix, compute depth d
    int d = 0;
    bool valid = true;
    for (char c : p) {
        if (c == '(') d++;
        else d--;
        if (d < 0) { valid = false; break; }
    }
    if (!valid) { cout << 0 << '\n'; return 0; }

    int s = n - k;
    if ((s - d) < 0 || (s - d) % 2 != 0) { cout << 0 << '\n'; return 0; }

    int u = (s - d) / 2;        // remaining opens
    ll ans = (C(s, u) - C(s, u - 1) + MOD) % MOD;

    cout << ans << '\n';
    return 0;
}