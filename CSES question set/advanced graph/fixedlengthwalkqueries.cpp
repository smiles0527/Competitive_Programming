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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q; cin >> n >> m >> q;
    vector<vector<int>> adj(n + 1);
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        adj[a].pb(b); adj[b].pb(a);
    }
    const int INF = 1e9;
    ll W = (ll)(n + 1);
    // de[a*W+b] = shortest even-length walk a->b, dod[...] = shortest odd
    vector<int> de(W * W, INF), dod(W * W, INF);

    // layered BFS over (node, parity): each step toggles parity, +1 length
    vector<int> d0(n + 1), d1(n + 1);
    vector<pair<int,int>> bfs; bfs.reserve(2 * (n + 1));
    for(int a = 1; a <= n; a++){
        fill(d0.begin(), d0.end(), INF);
        fill(d1.begin(), d1.end(), INF);
        d0[a] = 0;
        bfs.clear(); bfs.pb({a, 0});
        for(int h = 0; h < (int)bfs.size(); h++){
            auto [u, p] = bfs[h];
            int cur = p ? d1[u] : d0[u];
            for(int w : adj[u]){
                if(!p){                       // u even -> w odd
                    if(d1[w] > cur + 1){ d1[w] = cur + 1; bfs.pb({w, 1}); }
                } else {                       // u odd -> w even
                    if(d0[w] > cur + 1){ d0[w] = cur + 1; bfs.pb({w, 0}); }
                }
            }
        }
        ll base = (ll)a * W;
        for(int b = 1; b <= n; b++){ de[base + b] = d0[b]; dod[base + b] = d1[b]; }
    }

    string out; out.reserve(q * 4);
    while(q--){
        int a, b; ll x; cin >> a >> b >> x;
        ll need = (x & 1) ? dod[(ll)a * W + b] : de[(ll)a * W + b];
        out += (need <= x) ? "YES\n" : "NO\n";
    }
    cout << out;
}