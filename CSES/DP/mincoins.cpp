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
const int MOD = 998244353;
const int INF = 1e9;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	ll n, x; cin >> n >> x;
	vector<int> c(n); for(auto &x : c) cin >> x;
	vector<int> dp(x+1, INF); dp[0] = 0;

	for(int i=1;i<=x;i++){
		for(int v : c){
			if(i - v >= 0){
				dp[i] = min(dp[i], dp[i-v]+1);
			}
		}
	}	
	cout << (dp[x] >= INF ? -1 : dp[x]);
	return 0;
}