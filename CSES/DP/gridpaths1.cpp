#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int MOD = 1e9+7;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n; cin >> n;

	vector<string> g(n); for (auto &x : g) cin >> x;

	vector<vi> dp(n, vi(n,0));
	for(int r=0; r<n; r++){
		for(int c=0;c<n;c++){
			if(g[r][c]=='*'){
				dp[r][c]=0; continue;
			}
			if(r==0&&c==0){
				dp[r][c]=1; continue;
			}

			ll up = (r>0)? dp[r-1][c]:0;
			ll left = (c>0)? dp[r][c-1]:0;	
			dp[r][c] = (up+left)%MOD;
		}
	}
	cout << dp[n-1][n-1];
	return 0;
}