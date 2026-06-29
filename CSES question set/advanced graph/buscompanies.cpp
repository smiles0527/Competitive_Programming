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
const ll INF = 4e18;

int n, m;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    int N = n + m;                                   // cities 1..n, company nodes n+1..n+m
    vector<vii> adj(N + 1);
    vector<ll> cost(m);
    for(int i = 0; i < m; i++) cin >> cost[i];
    for(int i = 0; i < m; i++){
        int comp = n + 1 + i, k; cin >> k;
        while(k--){ int a; cin >> a; adj[a].pb({comp, cost[i]}); adj[comp].pb({a, 0}); }   // pay in, ride out free
    }

    vector<ll> d(N + 1, INF); d[1] = 0;
    priority_queue<ii, vii, greater<>> pq; pq.push({0, 1});
    while(!pq.empty()){
        auto [du, u] = pq.top(); pq.pop();
        if(du > d[u]) continue;
        for(auto [v, w] : adj[u]) if(du + w < d[v]){ d[v] = du + w; pq.push({d[v], v}); }
    }

    for(int i = 1; i <= n; i++) cout << d[i] << " \n"[i == n];
}