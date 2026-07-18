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
	
	ll n; cin >> n;

	vector<int> dp(n+1);
	dp[0] = 1;

	for(int i=1;i<=n;i++){
		for(int j=1;j<=6;j++){
			if(i-j>=0) dp[i] = (dp[i]+dp[i-j])%MOD;
		}
	}
	cout << dp[n];
	return 0;
}