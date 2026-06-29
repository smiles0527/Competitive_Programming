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

const int B = 30;
ll basis[B + 1];

void insert(ll x) {
    for (int b = B; b >= 0; b--) {
        if (!((x >> b) & 1)) continue;
        if (!basis[b]) { basis[b] = x; return; }
        x ^= basis[b];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; ll k; cin >> n >> k;
    for (int i = 0; i < n; i++) { ll x; cin >> x; insert(x); }

    // RREF: clear each pivot bit from every other vector
    for (int b = B; b >= 0; b--) if (basis[b])
        for (int c = B; c >= 0; c--)
            if (c != b && basis[c] && ((basis[c] >> b) & 1)) basis[c] ^= basis[b];

    ll sb[B + 1]; int r = 0;                 // pivots descending
    for (int b = B; b >= 0; b--) if (basis[b]) sb[r++] = basis[b];

    int nr = n - r;
    ll c = (nr >= 62) ? (ll)4e18 : (1LL << nr);   // multiplicity per distinct value (capped vs k)

    string out; out.reserve(11 * (size_t)k);
    ll produced = 0;
    for (int j = 0; produced < k; j++) {
        ll val = 0;
        for (int t = 0; t < r; t++) if ((j >> (r - 1 - t)) & 1) val ^= sb[t];   // MSB -> largest pivot
        ll rep = min(c, k - produced);
        for (ll q = 0; q < rep; q++) { out += to_string(val); out += ' '; }
        produced += rep;
    }
    if (!out.empty()) out.back() = '\n';
    cout << out;
    return 0;
}