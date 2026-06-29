#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;
const int INF = 1e9;

int n;
vector<vector<int>> adj;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    adj.assign(n + 1, {});
    for(int i = 0; i < n - 1; i++){ int a, b; cin >> a >> b; adj[a].pb(b); adj[b].pb(a); }

    int root = 1;
    for(int u = 1; u <= n; u++) if((int)adj[u].size() >= 2){ root = u; break; }   // root must be a non-leaf

    // iterative DFS preorder; leaves of any subtree stay contiguous in `leaves` (key invariant)
    vector<int> leaves, st;
    vector<char> vis(n + 1, 0);
    st.pb(root); vis[root] = 1;
    while(!st.empty()){
        int u = st.back(); st.pop_back();
        if((int)adj[u].size() == 1) leaves.pb(u);                 // root has deg>=2, so never caught here
        for(int v : adj[u]) if(!vis[v]){ vis[v] = 1; st.pb(v); }
    }

    int L = leaves.size();
    int k = (L + 1) / 2;                                          // = ceil(L/2), the answer
    cout << k << "\n";
    for(int i = 0; i < L / 2; i++) cout << leaves[i] << ' ' << leaves[i + k] << "\n";
    if(L & 1) cout << leaves[L / 2] << ' ' << leaves[0] << "\n";  // odd middle leaf: cover its pendant edge
}