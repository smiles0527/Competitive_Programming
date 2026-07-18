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
vector<ll> bit;
void upd(int i, ll v){ for(; i<=m; i+=i&-i) bit[i]=max(bit[i],v);}
ll qry(int i){ ll r=0; for(; i>0; i-=i&-i) r=max(r,bit[i]); return r;}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n; cin >> n;	
	vector<array<ll,3>> p(n); // b a w
	vi co;
	for(auto &x: p){
		ll a,b,w; cin>>a>>b>>w;
		x={b,a,w};
		co.push_back(a); co.push_back(b);
	}
	sort(co.begin(), co.end());
	co.erase(unique(co.begin(),co.end()),co.end());
	m=co.size();
	auto id=[&](ll x){ return int(lower_bound(co.begin(),co.end(),x)-co.begin())+1; };
	sort(p.begin(),p.end()); //end day b
	bit.assign(m+1,0);
	ll ans=0;

	for(auto &x : p){
		ll b=x[0],a=x[1],w=x[2];
		ll prev=qry(id(a)-1); //strictly b4 a
		ll cur = prev + w;
		ans = max(ans,cur);
		upd(id(b),cur);
	}

	cout << ans << '\n';
	return 0;
}