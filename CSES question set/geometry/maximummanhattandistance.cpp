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
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    ll mnu = LLONG_MAX, mxu = LLONG_MIN, mnv = LLONG_MAX, mxv = LLONG_MIN;

    string out;
    out.reserve(1 << 21);

    while (n--) {
        ll x, y; cin >> x >> y;
        ll u = x + y, v = x - y;
        mnu = min(mnu, u); mxu = max(mxu, u);
        mnv = min(mnv, v); mxv = max(mxv, v);
        ll ans = max(mxu - mnu, mxv - mnv);
        out += to_string(ans);
        out += '\n';
    }
    cout << out;
    return 0;
}