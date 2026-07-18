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

string s;
ll dp[20][11];

ll dfs(int pos, int prev, bool tight){
	if(pos==(int)s.size()) return 1;
	if(!tight && dp[pos][prev]>=0) return dp[pos][prev];
	int hi = tight ? s[pos]-'0' : 9;
	ll res = 0;
	for(int d=0;d<=hi;d++){
		if(d==prev) continue;
		int np=(prev==10 && d==0) ? 10 : d;
		res+=dfs(pos+1,np,tight && d==hi);
	}
	if(!tight) dp[pos][prev] = res;
	return res;
}

ll f(ll x){
	if(x<0) return 0;
	s = to_string(x);
	memset(dp,-1,sizeof dp);
	return dfs(0,10,true);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	ll a,b; cin >> a >> b;
	cout << f(b) - f(a-1) << '\n';

	return 0;
}