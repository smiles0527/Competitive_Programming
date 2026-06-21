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

    int n, a, b; cin >> n >> a >> b;
    int maxs = 6 * n;
    vector<double> dp(maxs + 1, 0.0);
    dp[0] = 1.0;

    for (int i = 1; i <= n; i++) {
        vector<double> nd(maxs + 1, 0.0);
        for (int s = i; s <= 6 * i; s++) {       // reachable sums after i throws
            double acc = 0;
            for (int f = 1; f <= 6; f++)
                if (s - f >= 0) acc += dp[s - f];
            nd[s] = acc / 6.0;
        }
        dp = move(nd);
    }

    double ans = 0;
    for (int s = a; s <= b; s++) ans += dp[s];

    cout << fixed << setprecision(6) << ans << '\n';
    return 0;
}