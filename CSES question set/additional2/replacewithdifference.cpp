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
const int MAXS = 500001;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> x(n); ll T = 0;
    for(auto& v : x){ cin >> v; T += v; }

    if(T & 1){ cout << -1 << "\n"; return 0; }            // sum parity invariant under |a-b|
    int S = T / 2;

    // prefix subset-sum bitsets to reconstruct a part A summing to S
    vector<bitset<MAXS>> dp(n + 1);
    dp[0][0] = 1;
    for(int i = 0; i < n; i++) dp[i+1] = dp[i] | (dp[i] << x[i]);
    if(!dp[n][S]){ cout << -1 << "\n"; return 0; }         // no balanced partition (e.g. [2,2,2])

    vector<char> inA(n, 0); int t = S;
    for(int i = n; i >= 1; i--) if(t >= x[i-1] && dp[i-1][t - x[i-1]]){ inA[i-1] = 1; t -= x[i-1]; }   // backtrack A

    vector<ll> PA, PB;
    for(int i = 0; i < n; i++) (inA[i] ? PA : PB).pb(x[i]);

    // cross-reduce: pair across piles, |a-b| joins the larger side; sum(PA)==sum(PB) invariant => ends at single 0
    vii ops; ops.reserve(n - 1);
    while(!PA.empty() && !PB.empty()){
        ll a = PA.back(); PA.pop_back();
        ll b = PB.back(); PB.pop_back();
        ops.pb({a, b});
        ll d = llabs(a - b);
        (a >= b ? PA : PB).pb(d);
    }
    vector<ll>& R = PA.empty() ? PB : PA;                  // leftover side is all zeros
    while(R.size() > 1){ ll a = R.back(); R.pop_back(); ll b = R.back(); R.pop_back(); ops.pb({a, b}); R.pb(llabs(a - b)); }

    string out; out.reserve(ops.size() * 14);
    for(auto& o : ops){ out += to_string(o.f); out += ' '; out += to_string(o.s); out += '\n'; }
    cout << out;
}