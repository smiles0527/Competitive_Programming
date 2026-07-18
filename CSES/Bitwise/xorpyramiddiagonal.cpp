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
    int LOG = 0; while ((1 << LOG) < n) LOG++;
    int U = 1 << LOG;

    vector<int> a(U, 0);
    for (int i = 0; i < n; i++) cin >> a[i];

    // SOS xor-subset transform: a[r] becomes XOR over submasks i of r  ( = L_r by Lucas )
    for (int b = 0; b < LOG; b++)
        for (int mask = 0; mask < U; mask++)
            if (mask & (1 << b)) a[mask] ^= a[mask ^ (1 << b)];

    string out; out.reserve(11 * n);
    for (int r = 0; r < n; r++) { if (r) out += ' '; out += to_string(a[r]); }
    out += '\n';
    cout << out;
    return 0;
}