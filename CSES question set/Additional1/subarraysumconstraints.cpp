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

int par[5005];
ll d[5005];                         // P_v - P_par[v]

int find(int v){
    if(par[v] == v) return v;
    int r = find(par[v]);
    d[v] += d[par[v]];              // accumulate offset to root
    par[v] = r;
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; cin >> n >> m;
    for(int i = 0; i <= n; i++){ par[i] = i; d[i] = 0; }

    bool ok = true;
    for(int q = 0; q < m; q++){
        ll l, r, s; cin >> l >> r >> s;
        int a = l-1, b = r;                    // P_b - P_a = s
        int ra = find(a), rb = find(b);
        if(ra == rb){
            if(d[b] - d[a] != s) ok = false;   // inconsistent
        } else {
            d[rb] = s - d[b] + d[a];           // P_rb - P_ra
            par[rb] = ra;
        }
    }

    if(!ok){ cout << "NO\n"; return 0; }

    cout << "YES\n";
    for(int i = 1; i <= n; i++){
        find(i); find(i-1);                    // ensure d[] are root-relative
        cout << d[i] - d[i-1] << " \n"[i==n];   // x_i = P_i - P_{i-1}
    }
}