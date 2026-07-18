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
    for (int i = 2; i <= n; i++){ int b; cin >> b; g[b].push_back(i); }

    vector<int> sz(n + 1, 0), ord; ord.reserve(n);
    vector<int> st = {1};
    while (!st.empty()){
        int u = st.back(); st.pop_back();
        ord.push_back(u);
        for (int v : g[u]) st.push_back(v);
    }
    for (int k = (int)ord.size() - 1; k >= 0; k--){
        int u = ord[k];
        for (int v : g[u]) sz[u] += sz[v] + 1; // child finalized before parent in reverse preorder
    }

    for (int i = 1; i <= n; i++) cout << sz[i] << " \n"[i == n];
    return 0;
}