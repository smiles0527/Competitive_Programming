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
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    int LOG = 1;
    while ((1 << LOG) < n) LOG++;
    LOG++;

    vector<vi> sp(LOG, vi(n));
    for (int i = 0; i < n; i++) cin >> sp[0][i];

    for (int k = 1; k < LOG; k++)
        for (int i = 0; i + (1 << k) <= n; i++)
            sp[k][i] = min(sp[k-1][i], sp[k-1][i + (1 << (k-1))]);

    while (q--){
        int a, b; cin >> a >> b;
        a--; b--;                       // 0-indexed
        int k = 31 - __builtin_clz(b - a + 1);
        cout << min(sp[k][a], sp[k][b - (1 << k) + 1]) << '\n';
    }
    return 0;
}