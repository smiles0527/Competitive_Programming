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
const int LOG = 18;
int n, q;
int up[LOG][200005];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 2; i <= n; i++) cin >> up[0][i];
    up[0][1] = 0;   // director has no boss

    for (int j = 1; j < LOG; j++)
        for (int v = 1; v <= n; v++)
            up[j][v] = up[j-1][ up[j-1][v] ];   // up[*][0]=0 sentinel

    while (q--) {
        int x, k; cin >> x >> k;
        for (int j = 0; j < LOG && x; j++)
            if (k >> j & 1) x = up[j][x];
        cout << (x ? x : -1) << '\n';
    }
    return 0;
}