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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n; cin >> n;
    if (n == 1) { cout << 0 << '\n'; return 0; }

    ll d0 = 1, d1 = 0;   // D_0 = 1, D_1 = 0
    ll cur = d1;
    for (ll i = 2; i <= n; i++) {
        cur = (ll)(i - 1) % MOD * ((d1 + d0) % MOD) % MOD;
        d0 = d1;
        d1 = cur;
    }
    cout << cur << '\n';
    return 0;
}