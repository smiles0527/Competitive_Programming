#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#define pb push_back
typedef long long ll;
typedef unsigned long long ull;
const ll INF = 4e18;

int n, m;
ull P1, P2;                 // random large primes

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    P1 = (1ULL<<61) - 1;                                  // Mersenne, __int128-safe
    P2 = 2000000000000000003ULL;
    cin >> n >> m;
    vector<int> A(m), B(m); vector<ll> C(m);
    vector<vector<pair<int,ll>>> adj(n + 1), radj(n + 1);
    for(int i = 0; i < m; i++){ int a, b; ll c; cin >> a >> b >> c; A[i]=a; B[i]=b; C[i]=c; adj[a].pb({b,c}); radj[b].pb({a,c}); }

    auto dijk = [&](int s, vector<vector<pair<int,ll>>>& G){
        vector<ll> d(n + 1, INF); d[s] = 0;
        priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq; pq.push({0, s});
        while(!pq.empty()){
            auto [du, u] = pq.top(); pq.pop();
            if(du > d[u]) continue;
            for(auto [v, w] : G[u]) if(du + w < d[v]){ d[v] = du + w; pq.push({d[v], v}); }
        }
        return d;
    };
    vector<ll> d1 = dijk(1, adj), d2 = dijk(n, radj);
    ll D = d1[n];

    // SP-DAG
    vector<vector<int>> g(n + 1), rg(n + 1);
    vector<char> good(n + 1, 0);
    for(int v = 1; v <= n; v++) good[v] = (d1[v] < INF && d2[v] < INF && d1[v] + d2[v] == D);
    for(int i = 0; i < m; i++) if(d1[A[i]] < INF && d2[B[i]] < INF && d1[A[i]] + C[i] + d2[B[i]] == D){ g[A[i]].pb(B[i]); rg[B[i]].pb(A[i]); }

    // topo order = vertices sorted by d1 (SP edges strictly increase d1)
    vector<int> ord;
    for(int v = 1; v <= n; v++) if(good[v]) ord.pb(v);
    sort(ord.begin(), ord.end(), [&](int a, int b){ return d1[a] < d1[b]; });

    auto mul = [](ull a, ull b, ull p){ return (ull)((__uint128_t)a * b % p); };

    // w1[v] = #SP 1->v, w2[v] = #SP v->n, both mod P1 and P2 (paired)
    vector<ull> a1(n + 1, 0), a2(n + 1, 0), b1(n + 1, 0), b2(n + 1, 0);
    a1[1] = a2[1] = 1;
    for(int u : ord) for(int v : g[u]){ a1[v] = (a1[v] + a1[u]) % P1; a2[v] = (a2[v] + a2[u]) % P2; }
    b1[n] = b2[n] = 1;
    for(int i = (int)ord.size() - 1; i >= 0; i--){ int u = ord[i]; for(int v : g[u]){ b1[u] = (b1[u] + b1[v]) % P1; b2[u] = (b2[u] + b2[v]) % P2; } }

    ull T1 = a1[n], T2 = a2[n];
    vector<int> ans;
    for(int v = 1; v <= n; v++)
        if(good[v] && mul(a1[v], b1[v], P1) == T1 && mul(a2[v], b2[v], P2) == T2) ans.pb(v);

    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for(int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " \n"[i + 1 == (int)ans.size()];
}