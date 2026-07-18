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
const ll INV2 = (MOD + 1) / 2;   // inverse of 2 mod p

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n; cin >> n;

    ll ans = 0;
    for (ll l = 1; l <= n; ) {
        ll q = n / l;
        ll r = n / q;                       // last d with floor(n/d) == q
        // sum of d in [l, r] mod p
        ll lm = l % MOD, rm = r % MOD;
        ll cntsum = ( (lm + rm) % MOD ) * ( (rm - lm + 1 + MOD) % MOD ) % MOD * INV2 % MOD;
        ll qm = q % MOD;
        ans = (ans + qm * cntsum) % MOD;
        l = r + 1;
    }

    cout << ans << '\n';
    return 0;
}