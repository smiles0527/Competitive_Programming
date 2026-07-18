#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> P(n + 1, 0);
    for (int i = 1; i <= n; i++) { ll v; cin >> v; P[i] = P[i - 1] + v; }
    auto sum = [&](int l, int r) { return P[r] - P[l - 1]; };

    // dp[l][r], opt[l][r] over 1-indexed intervals; flatten to 1D rows
    static ll dp[5001][5001];                    // 200 MB; ll required for 5e12 sums
    static short opt[5001][5001];                // argmin split, fits in short (<=5000)

    for (int i = 1; i <= n; i++) { dp[i][i] = 0; opt[i][i] = i; }

    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            ll best = LLONG_MAX; int bj = opt[l][r - 1];
            int hi = opt[l + 1][r];
            for (int j = max(l, (int)opt[l][r - 1]); j <= min(r - 1, hi); j++) {
                ll v = dp[l][j] + dp[j + 1][r];   // Knuth window [opt[l][r-1], opt[l+1][r]]
                if (v < best) { best = v; bj = j; }
            }
            dp[l][r] = best + sum(l, r);
            opt[l][r] = bj;
        }
    }

    cout << dp[1][n] << "\n";
}