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
typedef unsigned long long ull;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n; int k;
    cin >> n >> k;
    vector<ll> a(k);
    for (auto& v : a) cin >> v;

    ll ans = 0;
    for (int mask = 1; mask < (1 << k); mask++) {
        ll prod = 1;
        bool overflow = false;
        int bits = 0;
        for (int i = 0; i < k; i++) if (mask >> i & 1) {
            bits++;
            if (prod > n / a[i]) { overflow = true; break; }   // prod*a[i] would exceed n
            prod *= a[i];
        }
        if (overflow) continue;     // floor(n/prod) == 0
        ll cnt = n / prod;
        if (bits & 1) ans += cnt;
        else ans -= cnt;
    }

    cout << ans << '\n';
    return 0;
}