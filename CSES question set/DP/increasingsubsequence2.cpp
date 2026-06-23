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

int m;
vi bit;
void upd(int i, ll v){ for(; i<=m; i+=i&-i) bit[i]=(bit[i]+v)%MOD; }
ll qry(int i){ ll r=0; for(; i>0; i-=i&-i) r=(r+bit[i])%MOD; return r; }

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n; cin >> n;
	vector<int> x(n); vector<int> co(n);
	for(int i = 0; i < n; i++){
		cin >> x[i]; co[i]=x[i];
	}
	sort(co.begin(),co.end());
	co.erase(unique(co.begin(),co.end()),co.end());
	m=co.size();
	auto id=[&](int v){ return int(lower_bound(co.begin(),co.end(),v)-co.begin())+1; };

	bit.assign(m+1,0);
	ll ans = 0;
	for(int i=0;i<n;i++){
		int r=id(x[i]);	
		ll dp = (qry(r-1) + 1)%MOD; //values < x[i];
		ans = (ans+dp)%MOD;
		upd(r,dp); //accumulate at such valud
	}
	cout << ans;
	return 0;
}