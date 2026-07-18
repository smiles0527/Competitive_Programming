#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#define pb push_back
typedef long long ll;

int n, m;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    vector<vector<int>> g(n + 1), rg(n + 1);
    for(int i = 0; i < m; i++){ int a, b; cin >> a >> b; g[a].pb(b); rg[b].pb(a); }

    // good = reachable from 1 AND can reach n
    vector<char> R1(n + 1, 0), R2(n + 1, 0), good(n + 1, 0);
    vector<int> st;
    st.pb(1); R1[1] = 1;
    while(!st.empty()){ int u = st.back(); st.pop_back(); for(int v : g[u]) if(!R1[v]){ R1[v] = 1; st.pb(v); } }
    st.pb(n); R2[n] = 1;
    while(!st.empty()){ int u = st.back(); st.pop_back(); for(int v : rg[u]) if(!R2[v]){ R2[v] = 1; st.pb(v); } }
    for(int i = 1; i <= n; i++) good[i] = R1[i] && R2[i];

    // reference SHORTEST path 1 -> n via BFS in good subgraph (no long jump edges p_a->p_b)
    vector<int> par(n + 1, -1), pos(n + 1, -1);
    queue<int> q; q.push(1); par[1] = 1;
    while(!q.empty()){
        int u = q.front(); q.pop();
        if(u == n) break;
        for(int v : g[u]) if(good[v] && par[v] == -1){ par[v] = u; q.push(v); }
    }
    vector<int> path;
    for(int u = n; ; u = par[u]){ path.pb(u); if(u == 1) break; }
    reverse(path.begin(), path.end());
    int L = (int)path.size() - 1;                 // positions 0..L
    for(int i = 0; i <= L; i++) pos[path[i]] = i;

    vector<int> pl(n + 1, -1), pr(n + 1, -1);
    // vector<char> vis(n + 1, 0);

    // --- OLD (WRONG): crossed path nodes, took max-reach / min-reachable => intervals collapse on back-edges ---
    // for(int i = L; i >= 0; i--){
    //     if(vis[path[i]]) continue;
    //     st.clear(); st.pb(path[i]);
    //     while(!st.empty()){
    //         int u = st.back(); st.pop_back();
    //         if(vis[u]) continue;
    //         vis[u] = 1; pl[u] = i;
    //         for(int v : g[u]) if(good[v] && !vis[v]) st.pb(v);
    //     }
    // }
    // fill(vis.begin(), vis.end(), 0);
    // for(int i = 0; i <= L; i++){
    //     if(vis[path[i]]) continue;
    //     st.clear(); st.pb(path[i]);
    //     while(!st.empty()){
    //         int u = st.back(); st.pop_back();
    //         if(vis[u]) continue;
    //         vis[u] = 1; pr[u] = i;
    //         for(int v : rg[u]) if(good[v] && !vis[v]) st.pb(v);
    //     }
    // }

    // pl[v] = min path idx reaching v WITHOUT crossing interior path nodes (ascending => first claim = min)
    for(int i = 0; i <= L; i++){
        int src = path[i];
        st.clear();
        for(int w : g[src]) if(good[w] && pl[w] == -1){ pl[w] = i; if(pos[w] == -1) st.pb(w); }
        while(!st.empty()){
            int u = st.back(); st.pop_back();
            for(int w : g[u]) if(good[w] && pl[w] == -1){ pl[w] = i; if(pos[w] == -1) st.pb(w); }
        }
    }
    // pr[v] = max path idx reachable from v WITHOUT crossing interior path nodes (descending => first claim = max)
    for(int i = L; i >= 0; i--){
        int src = path[i];
        st.clear();
        for(int w : rg[src]) if(good[w] && pr[w] == -1){ pr[w] = i; if(pos[w] == -1) st.pb(w); }
        while(!st.empty()){
            int u = st.back(); st.pop_back();
            for(int w : rg[u]) if(good[w] && pr[w] == -1){ pr[w] = i; if(pos[w] == -1) st.pb(w); }
        }
    }

    // off-path node v covers open interval (pl[v], pr[v]); uncovered path positions are critical
    vector<int> diff(L + 2, 0);
    // for(int v = 1; v <= n; v++) if(good[v] && pl[v] < pr[v]){ diff[pl[v] + 1]++; diff[pr[v]]--; }
    for(int v = 1; v <= n; v++)
        if(pos[v] == -1 && good[v] && pl[v] != -1 && pr[v] != -1 && pl[v] < pr[v]){ diff[pl[v] + 1]++; diff[pr[v]]--; }
    vector<int> ans;
    int cur = 0;
    for(int i = 0; i <= L; i++){ cur += diff[i]; if(cur == 0) ans.pb(path[i]); }

    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for(int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " \n"[i + 1 == (int)ans.size()];
}