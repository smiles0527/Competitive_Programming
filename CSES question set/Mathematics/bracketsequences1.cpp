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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fact[0] = 1;
    for (int i = 1; i <= V; i++) fact[i] = fact[i-1] * i % MOD;
    invfact[V] = power(fact[V], MOD - 2);
    for (int i = V; i >= 1; i--) invfact[i-1] = invfact[i] * i % MOD;

    int n; cin >> n;
    if (n & 1) { cout << 0 << '\n'; return 0; }

    int m = n / 2;
    // C_m = C(2m, m) * inv(m+1)
    ll binom = fact[2*m] * invfact[m] % MOD * invfact[m] % MOD;
    ll cat = binom * power(m + 1, MOD - 2) % MOD;

    cout << cat << '\n';
    return 0;
}