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
ll basis[B + 1];                            // basis[b] has top set bit b, or 0

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

    int n; cin >> n;
    for (int i = 0; i < n; i++) { ll x; cin >> x; insert(x); }

    ll ans = 0;
    for (int b = B; b >= 0; b--) if ((ans ^ basis[b]) > ans) ans ^= basis[b];
    cout << ans << '\n';
    return 0;
}