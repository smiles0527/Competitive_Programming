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
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; i++){
        int a, b; cin >> a >> b;
        g[a].push_back(b); g[b].push_back(a);
    }

    vector<int> par(n + 1, 0), ord; ord.reserve(n);
    vector<int> st = {1}; par[1] = -1;
    while (!st.empty()){
        int u = st.back(); st.pop_back();
        ord.push_back(u);
        for (int v : g[u]) if (v != par[u]){ par[v] = u; st.push_back(v); }
    }

    vector<long long> d0(n + 1, 0), d1(n + 1, 0);
    for (int k = (int)ord.size() - 1; k >= 0; k--){
        int u = ord[k];
        long long S = 0, best = LLONG_MIN;
        for (int v : g[u]) if (v != par[u]) S += max(d0[v], d1[v]);
        for (int v : g[u]) if (v != par[u]){
            long long gain = 1 + d0[v] - max(d0[v], d1[v]); // pairing u with v
            best = max(best, gain);
        }
        d0[u] = S;
        d1[u] = (best == LLONG_MIN) ? 0 : S + best; // best<0 case naturally handled vs d0
    }

    cout << max(d0[1], d1[1]) << "\n";
    return 0;
}