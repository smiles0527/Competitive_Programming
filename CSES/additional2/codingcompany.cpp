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
    int n, x; cin >> n >> x;
    vector<int> t(n);
    for(auto& v : t) cin >> v;
    sort(t.begin(), t.end());

    // dp[j][p]: ways with j open teams, accumulated penalty p (<=x). gap paid on crossing.
    vector<vector<ll>> dp(n + 2, vector<ll>(x + 1, 0));
    dp[0][0] = 1;
    for(int i = 0; i < n; i++){
        int g = i ? t[i] - t[i-1] : 0;                       // gap crossed entering coder i
        vector<vector<ll>> nd(n + 2, vector<ll>(x + 1, 0));
        for(int j = 0; j <= i; j++){
            for(int p = 0; p <= x; p++){
                ll w = dp[j][p]; if(!w) continue;
                int np = p + j * g;                          // j open teams pay the gap
                if(np > x) continue;                         // exceeds budget, prune
                // role of coder i:
                nd[j+1][np] = (nd[j+1][np] + w) % MOD;        // start new open team
                nd[j][np]   = (nd[j][np]   + w) % MOD;        // singleton (open+close)
                if(j > 0){
                    nd[j][np]   = (nd[j][np]   + w * j) % MOD; // join as middle of an open team
                    nd[j-1][np] = (nd[j-1][np] + w * j) % MOD; // close an open team
                }
            }
        }
        dp = move(nd);
    }

    ll ans = 0;
    for(int p = 0; p <= x; p++) ans = (ans + dp[0][p]) % MOD;   // all teams closed
    cout << ans << "\n";
}