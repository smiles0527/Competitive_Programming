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

    int n, k;
    cin >> n >> k;

    long double ans = 0;

    // double ans = 0;
    // for (int v = 1; v <= k; v++) {
    //     double pLe = pow((double)v / k, n);
    //     double pLt = pow((double)(v - 1) / k, n);
    //     ans += v * (pLe - pLt);
    // }

    for (int v = 1; v <= k; v++) {
        long double x = (long double)(v - 1) / k;
        ans += 1 - powl(x, n);
    }

    // cout << fixed << setprecision(6) << (double)(ans + 1e-12L) << '\n';
    cout << fixed << setprecision(6) << ans << '\n';
    return 0;
}