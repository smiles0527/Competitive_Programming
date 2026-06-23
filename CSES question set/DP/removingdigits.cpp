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
	vector<int> dp(n+1,0);
	for(int i=1; i<=n; i++){
		int best = INT_MAX;
		for(int j=i; j>0; j/=10){
			int d=j%10; if(d) best=min(best,dp[i-d]+1);
		}
		dp[i]=best;
	}
	cout << dp[n];	

	return 0;
}