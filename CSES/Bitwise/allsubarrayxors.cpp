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

const int LOG = 20, U = 1 << LOG;          // values < 2^20 since x_i <= 1e6
static ll g[U];

void wht(ll* a) {
    for (int len = 1; len < U; len <<= 1)
        for (int i = 0; i < U; i += len << 1)
            for (int j = i; j < i + len; j++) {
                ll u = a[j], v = a[j + len];
                a[j] = u + v; a[j + len] = u - v;
            }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    int pref = 0, distinct = 0;
    g[0] = 1; distinct = 1;                 // P_0 = 0
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        pref ^= x;
        if (!g[pref]) { g[pref] = 1; distinct++; }   // set indicator over prefixes
    }
    bool zero = (n + 1 > distinct);         // repeated prefix => subarray xor 0 achievable

    wht(g);
    for (int v = 0; v < U; v++) g[v] *= g[v];
    wht(g);                                 // g[v] /= U gives pair-count; sign of >0 unaffected

    string out;
    vector<int> res;
    if (zero) res.pb(0);
    for (int v = 1; v < U; v++) if (g[v] > 0) res.pb(v);   // g[v]>0 <=> v is some subarray xor

    out += to_string(res.size()); out += '\n';
    for (size_t i = 0; i < res.size(); i++) { if (i) out += ' '; out += to_string(res[i]); }
    out += '\n';
    cout << out;
    return 0;
}