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
const int V = 1000000;
int mu[V + 1], freq[V + 1];
bool comp[V + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // linear sieve for mobius
    vector<int> primes;
    mu[1] = 1;
    for (int i = 2; i <= V; i++) {
        if (!comp[i]) { primes.push_back(i); mu[i] = -1; }
        for (int p : primes) {
            if ((ll)i * p > V) break;
            comp[i * p] = true;
            if (i % p == 0) { mu[i * p] = 0; break; }
            else mu[i * p] = -mu[i];
        }
    }

    int n; cin >> n;
    int mx = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        freq[x]++;
        mx = max(mx, x);
    }

    ll ans = 0;
    for (int d = 1; d <= mx; d++) {
        if (mu[d] == 0) continue;
        ll cd = 0;
        for (int m = d; m <= mx; m += d) cd += freq[m];
        ans += (ll)mu[d] * (cd * (cd - 1) / 2);
    }

    cout << ans << '\n';
    return 0;
}