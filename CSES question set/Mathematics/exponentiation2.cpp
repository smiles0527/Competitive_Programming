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

ll power(ll a, ll b, ll mod) {
    a %= mod;
    if (a < 0) a += mod;
    ll r = 1 % mod;
    while (b > 0) {
        if (b & 1) r = r * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    string out;
    out.reserve(1 << 21);

    while (n--) {
        ll a, b, c; cin >> a >> b >> c;

        // determine exponent E = b^c, both reduced mod (p-1) and its zero/one status
        ll am = a % MOD;

        // zero base handling
        if (am == 0) {
            // result is 0^(b^c); 0^0 = 1, else 0
            // b^c == 0  iff b==0 and c>0
            bool expIsZero = (b == 0 && c > 0);
            out += (expIsZero ? "1" : "0");
            out += '\n';
            continue;
        }

        // a not divisible by p: reduce exponent mod (p-1)
        ll e = power(b % (MOD - 1), c, MOD - 1);   // b^c mod (p-1)
        // if true exponent is 0 (b^c==0 => b==0,c>0), a^0 = 1
        if (b == 0 && c > 0) { out += "1"; out += '\n'; continue; }
        out += to_string(power(am, e, MOD));
        out += '\n';
    }
    cout << out;
    return 0;
}