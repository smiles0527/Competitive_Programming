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
	
	//dp[i][j] = {dp[i-1][j-1]+1, max(dp[i-1][j],dp[i][j-1])}

	int n,m; cin >> n >> m;
	vector<int> a(n+1),b(m+1);
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int j=1;j<=m;j++)cin>>b[j];
	
	vector<vector<int>> dp(n+1, vector<int>(m+1,0));

	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i]==b[j]){
				dp[i][j]=dp[i-1][j-1]+1;
			} else{
				dp[i][j]=max(dp[i-1][j], dp[i][j-1]);
			}
		}
	}	

	vector<int> lcs;
	int i=n,j=m;
	while(i>0 && j>0){
		if(a[i]==b[j]){
			lcs.push_back(a[i]);
			i--; j--;
		} else if(dp[i-1][j] >= dp[i][j-1]){
			i--;
		} else{
			j--;
		}
	}
	reverse(lcs.begin(),lcs.end());

	cout<<dp[n][m]<<'\n';
	for(int i=0;i<(int)lcs.size();i++){
		cout<< lcs[i]<<" \n"[i+1==(int)lcs.size()];
	}

	return 0;
}