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

int n;

int build(vector<vector<int>>& adj, int par[], int dep[], int id[], map<vector<int>,int>& mp){
    // iterative BFS root=1: parent/depth
    vector<int> bfs; bfs.reserve(n);
    vector<char> vis(n + 1, 0);
    dep[1] = 0; par[1] = 0; vis[1] = 1; bfs.pb(1);
    for(int h = 0; h < (int)bfs.size(); h++){
        int u = bfs[h];
        for(int w : adj[u]) if(!vis[w]){ vis[w] = 1; dep[w] = dep[u] + 1; par[w] = u; bfs.pb(w); }
    }
    vector<vector<int>> ch(n + 1);            // children ids gathered bottom-up
    for(int i = (int)bfs.size() - 1; i >= 0; i--){
        int u = bfs[i];
        sort(ch[u].begin(), ch[u].end());     // sibling-order invariance
        auto it = mp.find(ch[u]);
        if(it == mp.end()) id[u] = mp[ch[u]] = (int)mp.size();
        else id[u] = it->s;
        if(u != 1) ch[par[u]].pb(id[u]);
    }
    return id[1];
}

int par1[100005], dep1[100005], idv1[100005];
int par2[100005], dep2[100005], idv2[100005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    string out;
    while(t--){
        cin >> n;
        vector<vector<int>> a1(n + 1), a2(n + 1);
        for(int i = 0; i < n - 1; i++){ int u, v; cin >> u >> v; a1[u].pb(v); a1[v].pb(u); }
        for(int i = 0; i < n - 1; i++){ int u, v; cin >> u >> v; a2[u].pb(v); a2[v].pb(u); }
        map<vector<int>,int> mp;              // shared intern table across both trees
        int r1 = build(a1, par1, dep1, idv1, mp);
        int r2 = build(a2, par2, dep2, idv2, mp);
        out += (r1 == r2) ? "YES\n" : "NO\n";
    }
    cout << out;
}