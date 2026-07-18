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
	
	int n,x; cin >> n >> x;
	vector<int> w(n); for(auto &x : w) cin >> x;

	int N = 1<<n;
	vector<ii> dp(N, {n+1,0}); dp[0] = {1,0};	
	for(int S = 1;S < N; S++){
		for(int i = 0; i < n; i++){
			ii c = dp[S^(1<<i)]; //{r, wt} without 1
			if(c.s + w[i] <= x) c.s += w[i];
			else{ c.f++; c.s = w[i]; }
			dp[S] = min(dp[S],c);
		}
	}
	cout << dp[N-1].f <<'\n';
	return 0;
}