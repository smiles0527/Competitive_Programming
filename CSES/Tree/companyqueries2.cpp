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
int up[LOG][200005], dep[200005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 2; i <= n; i++) cin >> up[0][i];
    up[0][1] = 0;
    for (int v = 2; v <= n; v++) dep[v] = dep[up[0][v]] + 1;  // par precedes child

    for (int j = 1; j < LOG; j++)
        for (int v = 1; v <= n; v++)
            up[j][v] = up[j-1][ up[j-1][v] ];

    while (q--) {
        int a, b; cin >> a >> b;
        if (dep[a] < dep[b]) swap(a, b);          // a is deeper
        int d = dep[a] - dep[b];
        for (int j = 0; j < LOG; j++)
            if (d >> j & 1) a = up[j][a];
        if (a == b) { cout << a << '\n'; continue; }
        for (int j = LOG - 1; j >= 0; j--)
            if (up[j][a] != up[j][b]) { a = up[j][a]; b = up[j][b]; }
        cout << up[0][a] << '\n';
    }
    return 0;
}