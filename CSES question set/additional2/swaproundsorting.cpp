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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> x(n + 1);
    for(int i = 1; i <= n; i++) cin >> x[i];

    vector<char> vis(n + 1, 0);
    vector<ii> r1, r2;                         // swap pairs of rounds 1,2 ; rho = r2 o r1
    int mx = 1;                                // longest cycle length
    for(int i = 1; i <= n; i++) if(!vis[i]){
        vector<int> c; int u = i;
        while(!vis[u]){ vis[u] = 1; c.pb(u); u = x[u]; }      // follow f: c_{j+1}=x[c_j]
        int L = c.size(); mx = max(mx, L);
        for(int j = 0; j < L; j++){ int t = (L - j) % L;       if(j < t) r1.pb({c[j], c[t]}); }   // r1: j <-> -j
        for(int j = 0; j < L; j++){ int t = ((1 - j) % L + L) % L; if(j < t) r2.pb({c[j], c[t]}); }// r2: j <-> 1-j
    }

    auto dump = [&](vector<ii>& r){ cout << r.size() << "\n"; for(auto& p : r) cout << p.f << ' ' << p.s << "\n"; };
    if(mx == 1) cout << 0 << "\n";                          // already sorted
    else if(mx == 2){ cout << 1 << "\n"; dump(r2); }        // involution: all swaps fall in r2 (r1 empty)
    else { cout << 2 << "\n"; dump(r1); dump(r2); }
}