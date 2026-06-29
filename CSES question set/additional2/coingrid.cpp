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
vector<vector<int>> adj;                 // rows -> cols (1..n each side)
vector<int> mr, mc;                      // mr[r]=matched col, mc[c]=matched row (0 = none)
vector<char> used;                       // Kuhn visited (right side per phase)

bool kuhn(int u){
    for(int v : adj[u]) if(!used[v]){
        used[v] = 1;
        if(mc[v] == 0 || kuhn(mc[v])){ mc[v] = u; mr[u] = v; return true; }
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    adj.assign(n + 1, {});
    for(int r = 1; r <= n; r++){
        string row; cin >> row;
        for(int c = 1; c <= n; c++) if(row[c-1] == 'o') adj[r].pb(c);   // coin = edge r-c
    }

    mr.assign(n + 1, 0); mc.assign(n + 1, 0);
    int M = 0;
    for(int r = 1; r <= n; r++){ used.assign(n + 1, 0); if(kuhn(r)) M++; }

    // alternating-reachable from unmatched left. MVC = (L\Z) ∪ (R∩Z).
    vector<char> visL(n + 1, 0), visR(n + 1, 0);
    vector<int> st;
    for(int r = 1; r <= n; r++) if(mr[r] == 0){ visL[r] = 1; st.pb(r); }
    while(!st.empty()){
        int u = st.back(); st.pop_back();
        for(int v : adj[u]) if(!visR[v]){                 // unmatched edge L->R
            visR[v] = 1;
            int w = mc[v];                                // matched edge R->L
            if(w && !visL[w]){ visL[w] = 1; st.pb(w); }
        }
    }

    vector<ii> cover;                                     // (type, idx): 1=row, 2=col
    for(int r = 1; r <= n; r++) if(!visL[r] && mr[r]) cover.pb({1, r});   // L\Z (matched rows not reached)
    for(int c = 1; c <= n; c++) if(visR[c]) cover.pb({2, c});             // R∩Z

    cout << cover.size() << "\n";
    for(auto& p : cover) cout << p.f << ' ' << p.s << "\n";
}