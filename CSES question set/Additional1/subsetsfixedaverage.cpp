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

    int n, a; cin >> n >> a;
    vector<int> y(n);
    for(auto &v : y){ cin >> v; v -= a; }       // sum y = 0  ⇔  avg = a

    int O = n * 500;                            // offset, sums in [-O, O]
    int W = 2*O + 1;
    vector<ll> dp(W, 0);
    dp[O] = 1;                                  // empty subset, sum 0

    for(int yi : y){
        if(yi > 0)                              // descending dest avoids reuse
            for(int s = W-1; s >= yi; s--){
                if(dp[s-yi]) dp[s] = (dp[s] + dp[s-yi]) % MOD;
            }
        else if(yi < 0)                         // ascending for negative
            for(int s = 0; s + (-yi) < W; s++){
                if(dp[s-yi]) dp[s] = (dp[s] + dp[s-yi]) % MOD;
            }
        else {                                  // yi == 0: doubles every count
            for(int s = 0; s < W; s++) dp[s] = dp[s]*2 % MOD;
        }
    }

    cout << ((dp[O] - 1) % MOD + MOD) % MOD << '\n';
}