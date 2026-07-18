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

typedef __int128 lll;

const ll MOD = 1e9 + 7;

ll power(ll a, ll b) {
    a %= MOD; if (a < 0) a += MOD;
    ll r = 1;
    while (b) { if (b & 1) r = r * a % MOD; a = a * a % MOD; b >>= 1; }
    return r;
}

// 2^E mod p with E given as exact __int128, reduced mod (p-1)
ll pow2(lll E) {
    ll e = (ll)(E % (MOD - 1));
    return power(2, e);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n; cin >> n;
    lll nn = (lll)n * n;

    lll E1 = nn;
    lll E2, E4;
    if (n % 2 == 0) { E2 = nn / 2; E4 = nn / 4; }
    else { E2 = (nn + 1) / 2; E4 = (nn + 3) / 4; }

    ll s = (pow2(E1) + pow2(E2)) % MOD;
    s = (s + 2 * pow2(E4)) % MOD;

    ll ans = s * power(4, MOD - 2) % MOD;
    cout << ans << '\n';
    return 0;
}