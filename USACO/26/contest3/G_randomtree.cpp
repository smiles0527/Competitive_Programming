#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll MOD = 1000000007;
const int MAXN = 200005;

ll iv[MAXN];
int par[MAXN], sz[MAXN], ord[MAXN];
ll iQ[MAXN];
vector<int> adj[MAXN];

ll pw(ll a, ll e){ ll r = 1; a %= MOD; for(; e; e >>=1){ if(e&1) r = r*a%MOD; a = a*a%MOD; } return r; }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    iv[1] = 1;
    for(int i=2;i<MAXN;i++) iv[i] = (MOD-(MOD/i)*iv[MOD%i]%MOD)%MOD; 

    int T; cin >> T;
    while(T--){
        int N; cin >> N;
        for(int i = 1; i <= N; i++) adj[i].clear();
        for(int i = 0; i < N-1; i++){ 
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int t = 0; ord[t++]=1; par[1]=0;
        for(int i = 0; i < t; i++){
            int v = ord[i];
            for(int u : adj[v])
                if(u != par[v]){
                    par[u] = v; ord[t++] = u;
                }
        }

        for(int i = 1; i <= N; i++) sz[i] = 1;
        for(int i = N - 1; i >= 1; i--){
            int v = ord[i]; sz[par[v]]+=sz[v];
        }

        ll iq1 = 1;
        for(int i = 1; i <= N; i++) iq1 = iq1 * iv[sz[i]]%MOD;

        ll ans = 0;
        for(int i = 0; i < N; i++){
            int v = ord[i];
            if(v == 1) iQ[v] = iq1;
            else iQ[v] = iQ[par[v]] * (ll)sz[v] % MOD * iv[N-sz[v]]%MOD;
            ans = (ans + iQ[v])%MOD;
        }

        ll f = 1; for(int i = 1; i <= N - 1; i++) f = f * i % MOD;
        ans = ans * pw(f, MOD - 2)%MOD;
        cout << ans << '\n';

    }
    return 0;
}