#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
typedef long long ll;

int n, m;
int p[100005];
int fnd(int x){ while(p[x]!=x){ p[x]=p[p[x]]; x=p[x]; } return x; }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    vector<int> A(m), B(m);
    vector<vector<int>> g(n + 1);
    for(int i=1;i<=n;i++) p[i]=i;
    for(int i = 0; i < m; i++){ int a, b; cin >> a >> b; A[i] = a; B[i] = b; if(a != b) g[a].pb(b); p[fnd(a)]=fnd(b); }

    // iterative Tarjan: SCC sizes + count
    vector<int> low(n + 1, 0), num(n + 1, 0), comp(n + 1, -1), it(n + 1, 0);
    vector<char> onst(n + 1, 0);
    vector<int> stk, dfs; stk.reserve(n); dfs.reserve(n);
    int timer = 0, nc = 0;
    for(int s = 1; s <= n; s++){
        if(num[s]) continue;
        dfs.pb(s);
        while(!dfs.empty()){
            int u = dfs.back();
            if(!num[u]){ num[u] = low[u] = ++timer; stk.pb(u); onst[u] = 1; }
            bool pushed = false;
            while(it[u] < (int)g[u].size()){
                int v = g[u][it[u]++];
                if(!num[v]){ dfs.pb(v); pushed = true; break; }
                else if(onst[v]) low[u] = min(low[u], num[v]);
            }
            if(pushed) continue;
            if(low[u] == num[u]){
                while(true){ int w = stk.back(); stk.pop_back(); onst[w] = 0; comp[w] = nc; if(w == u) break; }
                nc++;
            }
            dfs.pop_back();
            if(!dfs.empty()) low[dfs.back()] = min(low[dfs.back()], low[u]);
        }
    }

    vector<int> csz(nc, 0);
    for(int i = 1; i <= n; i++) csz[comp[i]]++;
    ll ans = 0;
    // for(int c = 0; c < nc; c++) if(csz[c] >= 2) ans += csz[c];     // WRONG: separate cycle per SCC; cyclic SCCs in one WCC merge

    // --- old DAG handling: transitive reduction (WRONG: forbade new arcs) ---
    // vector<vector<int>> cg(nc);
    // for(int i = 0; i < m; i++){ int cu = comp[A[i]], cv = comp[B[i]]; if(cu != cv) cg[cu].pb(cv); }
    // for(int c = 0; c < nc; c++){
    //     auto &v = cg[c];
    //     sort(v.begin(), v.end(), greater<int>());                 // source-most sibling first
    //     v.erase(unique(v.begin(), v.end()), v.end());
    // }
    // vector<int> seen(nc, -1), st;
    // for(int c = 0; c < nc; c++){
    //     for(int v : cg[c]){
    //         if(seen[v] == c) continue;
    //         ans++;                                                 // keep arc c->v
    //         st.pb(v); seen[v] = c;
    //         while(!st.empty()){
    //             int x = st.back(); st.pop_back();
    //             for(int y : cg[x]) if(seen[y] != c){ seen[y] = c; st.pb(y); }
    //         }
    //     }
    // }

    int wcc = 0;
    for(int i = 1; i <= n; i++) if(fnd(i) == i) wcc++;
    // ans += (ll)nc - wcc;                                           // WRONG companion to the per-SCC cycle sum

    // each WCC: |V|-1 chain edges + 1 extra iff it contains a directed cycle (some SCC>=2)
    ans = (ll)n - wcc;
    vector<char> hascyc(n + 1, 0);
    for(int i = 1; i <= n; i++) if(csz[comp[i]] >= 2) hascyc[fnd(i)] = 1;   // mark WCC root
    for(int i = 1; i <= n; i++) if(fnd(i) == i && hascyc[i]) ans++;

    cout << ans << "\n";
}