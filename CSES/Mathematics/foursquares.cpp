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
const int MOD = 1e9+7;

const int MAXN = 10000000;
static vector<bool> sos2;                 // sos2[v] = v expressible as sum of two squares

// try to write R = p^2 + q^2, p<=q; return {p,q} or {-1,-1}
pair<int,int> twoSquares(ll R) {
    if (R < 0) return {-1, -1};
    ll p = 0, q = (ll)sqrtl((long double)R);
    while (q * q > R) q--;
    while (p <= q) {
        ll s = p*p + q*q;
        if (s == R) return {(int)p, (int)q};
        if (s < R) p++;
        else q--;
    }
    return {-1, -1};
}

inline bool isSum3(ll m) {                 // Legendre: sum of 3 squares iff not 4^k(8j+7)
    while (m && m % 4 == 0) m /= 4;
    return m % 8 != 7;                      // m==0 -> true (0 = 0+0+0)
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sos2.assign(MAXN + 1, false);
    for (ll p = 0; p*p <= MAXN; p++)
        for (ll q = p; p*p + q*q <= MAXN; q++)
            sos2[p*p + q*q] = true;

    int t; cin >> t;
    string out;

    while (t--) {
        ll n; cin >> n;
//      bool done = false;
//      for (ll a = 0; a*a <= n && !done; a++) {
//          ll r1 = n - a*a;
//          for (ll b = a; b*b <= r1 && !done; b++) {
//              ll r2 = r1 - b*b;
//              auto pr = twoSquares(r2);
//              if (pr.first != -1) {
//                  out += to_string(a); out += ' ';
//                  out += to_string(b); out += ' ';
//                  out += to_string(pr.first); out += ' ';
//                  out += to_string(pr.second);
//                  out += '\n';
//                  done = true;
//              }
//          }
//      }
        ll a = 0;
        while (!isSum3(n - a*a)) a++;          // smallest a: n-a^2 is a sum of 3 squares
        ll m = n - a*a;
        ll b = 0;
        while (!sos2[m - b*b]) b++;            // smallest b: remainder is a sum of 2 squares
        auto pr = twoSquares(m - b*b);
        out += to_string(a); out += ' ';
        out += to_string(b); out += ' ';
        out += to_string(pr.first); out += ' ';
        out += to_string(pr.second);
        out += '\n';
    }
    cout << out;
    return 0;
}