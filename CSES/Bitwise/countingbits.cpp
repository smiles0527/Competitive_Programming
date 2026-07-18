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

    ll n; cin >> n;
    ll N = n + 1;                          // count over [0,n]
    ll ans = 0;
    for (int i = 0; (1LL << i) <= n; i++) {
        ll blk = 1LL << (i + 1);
        ll half = 1LL << i;
        ans += (N / blk) * half;           // full blocks
        ll rem = N % blk;
        ans += max(0LL, rem - half);       // partial upper half
    }
    cout << ans << '\n';
    return 0;
}