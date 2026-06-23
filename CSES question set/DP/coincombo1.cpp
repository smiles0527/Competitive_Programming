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
	
	ll n, x; cin >> n >> x;
	vector<int> c(n); for(auto &x : c) cin >> x;
	vector<int> dp(x+1,0); dp[0]=1;

	for(int i=1;i<=x;i++){
		ll ways=0;
		for(int v : c){
			if(i-v>=0) ways += dp[i-v];
		}
		dp[i] = int(ways % MOD);
	}
	cout << dp[x];
	return 0;
}