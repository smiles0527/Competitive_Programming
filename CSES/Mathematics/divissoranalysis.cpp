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
const ll MOD = 1e9+7;
typedef __int128 lll;

ll power(ll a, ll b, ll mod) {
    a %= mod; if (a < 0) a += mod;
    ll r = 1 % mod;
    while (b > 0) {
        if (b & 1) r = (lll)r * a % mod;
        a = (lll)a * a % mod;
        b >>= 1;
    }
    return r;
}
ll inv(ll a) { return power(a, MOD - 2, MOD); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<ll> x(n), k(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> k[i];

    // count = prod (k_i + 1) mod p
    ll count = 1;
    for (int i = 0; i < n; i++) count = (lll)count * ((k[i] + 1) % MOD) % MOD;

    // sum = prod (p_i^{k_i+1} - 1)/(p_i - 1) mod p
    ll sum = 1;
    for (int i = 0; i < n; i++) {
        ll num = (power(x[i], k[i] + 1, MOD) - 1 + MOD) % MOD;
        ll den = inv((x[i] - 1) % MOD);
        sum = (lll)sum * (num * den % MOD) % MOD;
    }

    // product = prod p_i^{ k_i * tau / 2 }, exponent mod (p-1)
    // compute T2 = prod (k_j + 1) mod 2*(p-1); for each i, E = (k_i * T2)/2 mod (p-1)
    ll M2 = 2 * (MOD - 1);
    ll T2 = 1;
    for (int i = 0; i < n; i++) T2 = (lll)T2 * ((k[i] + 1) % M2) % M2;

    ll product = 1;
    for (int i = 0; i < n; i++) {
        ll ee = (lll)(k[i] % M2) * T2 % M2;   // k_i * tau  (mod 2(p-1)), guaranteed even
        ll e = (ee / 2) % (MOD - 1);           // divide by 2 then reduce mod (p-1)
        product = (lll)product * power(x[i], e, MOD) % MOD;
    }

    cout << count << ' ' << sum << ' ' << product << '\n';
    return 0;
}