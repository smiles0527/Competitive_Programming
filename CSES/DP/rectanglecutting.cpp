#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
// #define f first
#define s second
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int MOD = 1e9+7;

int dp[501][501];

int main(){
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int a, b;
    cin >> a >> b;
    for(int i = 1; i <= a; i++)
        for(int j = 1; j <= b; j++){
            if(i == j){ dp[i][j] = 0; continue; }
            int best = INT_MAX;
            for(int k = 1; k < i; k++)            // horizontal
                best = min(best, dp[k][j] + dp[i-k][j]);
            for(int k = 1; k < j; k++)            // vertical
                best = min(best, dp[i][k] + dp[i][j-k]);
            dp[i][j] = best + 1;
        }
    cout << dp[a][b] << "\n";
}	