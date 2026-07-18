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
	int T = n*(n+1)/2;
	if(T&1){ cout << 0 << '\n'; return 0;}
	int t = T/2;

	vi dp(t+1,0); dp[0]=1;
	for(int i = 1; i <= n-1; i++){ //n 1 side
		for(int s = t; s >= i; s--){
			dp[s] = (dp[s]+dp[s-i])%MOD;
		}
	}
	cout << dp[t] << '\n';
	return 0;
}	