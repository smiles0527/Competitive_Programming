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
const int MAXN = 1000000;

int ans[MAXN+1];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	ll w=1,n=1;
	ans[1]=2;

	for(int i=2;i<=MAXN;i++){
		ll nw = (2*w+n)%MOD;
		ll nn = (w+4*n)%MOD;
		w=nw; n=nn;
		ans[i]=int((w+n)%MOD);
	}

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
		cout<<ans[n]<<'\n';
	}

	return 0;
}