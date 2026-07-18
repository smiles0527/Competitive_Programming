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
    vector<ll> top(n), bot(n);
    for(auto& v : top) cin >> v;
    for(auto& v : bot) cin >> v;

    // horizontal across boundary j is forced to pre_j = prefix(t-2); split between rows is free within [min(0,pre),max(0,pre)]
    // vertical = min over splits of sum |(top_j-1) - (x_j - x_{j-1})|, x_0=x_n=0 ; clamp the ideal top-prefix into the corridor
    ll h = 0, x = 0, v = 0, pre = 0;
    for(int j = 1; j <= n; j++){
        pre += top[j-1] + bot[j-1] - 2;                       // running prefix of (t-2); boundary right of col j
        ll lo, hi;
        if(j <= n-1){ lo = min(0LL, pre); hi = max(0LL, pre); h += llabs(pre); }   // free range; horizontal cost
        else { lo = hi = 0; }                                 // outer boundary carries no flow
        ll ideal = x + (top[j-1] - 1);                        // x making v_j = 0
        ll nx = max(lo, min(hi, ideal));                      // clamp into corridor
        v += llabs(ideal - nx);                               // unavoidable vertical at column j
        x = nx;
    }
    cout << h + v << "\n";
}