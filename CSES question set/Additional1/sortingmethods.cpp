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

int N;
vi bit;
void upd(int i){ for(; i <= N; i += i & -i) bit[i]++; }
ll qry(int i){ ll r = 0; for(; i; i -= i & -i) r += bit[i]; return r; }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    N = n;
    vector<int> p(n+1), pos(n+1, 0);
    for(int i = 1; i <= n; i++){ cin >> p[i]; pos[p[i]] = i; }

    // M1: inversions via BIT (count already-seen values greater than current)
    bit.assign(n+1, 0);
    ll inv = 0;
    for(int i = 1; i <= n; i++){
        inv += qry(n) - qry(p[i]);          // seen values > p[i]
        upd(p[i]);
    }

    // M2: n - cycles
    vector<char> vis(n+1, 0);
    int cyc = 0;
    for(int i = 1; i <= n; i++){
        if(!vis[i]){
            cyc++;
            for(int j = i; !vis[j]; j = p[j]) vis[j] = 1;
        }
    }
    ll m2 = n - cyc;

    // M3: n - LIS  (kept elements form an increasing subsequence; rest moved once each)
    // int L = 1, cur = 1;                      // value chain v,v+1,... with pos increasing
    // for(int v = 2; v <= n; v++){
    //     if(pos[v] > pos[v-1]) cur++; else cur = 1;
    //     L = max(L, cur);
    // }
    // ll m3 = n - L;
    vector<int> tails;                          // patience sorting, strictly increasing
    for(int i = 1; i <= n; i++){
        auto it = lower_bound(tails.begin(), tails.end(), p[i]);
        if(it == tails.end()) tails.pb(p[i]); else *it = p[i];
    }
    ll m3 = n - (ll)tails.size();

    // M4: n - longest TOP suffix of values (n,n-1,...) with increasing positions
    int S = 1;                              // n-S+1..n in increasing pos order
    for(int v = n-1; v >= 1; v--){
        if(pos[v] < pos[v+1]) S++; else break;
    }
    ll m4 = n - S;

    cout << inv << " " << m2 << " " << m3 << " " << m4 << '\n';
    // if(n == 0) cout;                        // guard (n>=1 by constraints)
}