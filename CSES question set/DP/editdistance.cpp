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
	
	string a,b; cin >> a >> b;
	int n=a.size(), m=b.size();

	vector<vector<int>> dp(n+1,vector<int>(m+1,0));

	for(int i=0;i<=n;i++) dp[i][0]=i;
	for(int j=0;j<=m;j++) dp[0][j]=j;

	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int cost = (a[i-1] == b[j-1]) ? 0 : 1;	
			dp[i][j] = min({
				dp[i-1][j]+1,
				dp[i][j-1]+1,
				dp[i-1][j-1]+cost
			});
		}
	}
	
	cout<<dp[n][m]<<'\n';

	return 0;
}